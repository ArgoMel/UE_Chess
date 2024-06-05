#include "ChessPieces/ChessPiece.h"
#include "GM_Chess.h"
#include "PC_Chess.h"
#include "Board/BoardSquare.h"
#include "Components/BillboardComponent.h"
#include "Components/AudioComponent.h"
#include "Components/TimelineComponent.h"
#include <Kismet/GameplayStatics.h>

AChessPiece::AChessPiece()
{
	PrimaryActorTick.bCanEverTick = false;

	GetObjectAsset(NewLocAlphaCurve, UCurveFloat, "/Game/BattleChess/Curve/NewLocationAlpha.NewLocationAlpha");

	Color = EPlayerColor::White;
	InitialX = 0;
	InitialY = 0;
	IsKing = false;
	IsTeleportable = false;

	X = 0;
	Y = 0;
	PreviousX = 0;
	PreviousY = 0;
	ChessPieceMoveCount = 0;
	PlayerMoveCount = 0;
	IsEnPassant = false;
	IsInitialMove = false;
	IsValidMove = false;
	CanCaptureOpponent = false;
	IsSuccessfulMove = false;
	KingIsCastling = false;
	KingHasCastled = false;
	KingCanCastle = false;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	SetRootComponent(Billboard);
	Billboard->SetVisibility(false);

	ChessPiece = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChessPiece"));
	ChessPiece->SetupAttachment(Billboard);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Pawn(TEXT(
		"/Game/BattleChess/Assets/SM_Pawn.SM_Pawn"));
	if (SM_Pawn.Succeeded())
	{
		ChessPiece->SetStaticMesh(SM_Pawn.Object);
	}

	SlideAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Slide"));
	SlideAudio->SetupAttachment(Billboard);
	SlideAudio->bAutoActivate=false;
	static ConstructorHelpers::FObjectFinder<USoundBase> Teleport_Mode_Entered(TEXT(
		"/Game/BattleChess/Audio/Teleport_Mode_Entered.Teleport_Mode_Entered"));
	if (Teleport_Mode_Entered.Succeeded())
	{
		SlideAudio->SetSound(Teleport_Mode_Entered.Object);
	}

	TeleportAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Teleport"));
	TeleportAudio->SetupAttachment(Billboard);
	TeleportAudio->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> Teleport(TEXT(
		"/Game/BattleChess/Audio/Teleport.Teleport"));
	if (Teleport.Succeeded())
	{
		TeleportAudio->SetSound(Teleport.Object);
	}

	ButtonClickAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ButtonClick"));
	ButtonClickAudio->SetupAttachment(Billboard);
	ButtonClickAudio->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> Flashlight_Switch(TEXT(
		"/Engine/VREditor/Sounds/UI/Flashlight_Switch.Flashlight_Switch"));
	if (Flashlight_Switch.Succeeded())
	{
		ButtonClickAudio->SetSound(Flashlight_Switch.Object);
	}

	ChessPieceMovement = CreateDefaultSubobject<UTimelineComponent>(TEXT("ChessPieceMovement"));
}

void AChessPiece::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetChessPieceColor();
}

void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddDynamic(this,&ThisClass::OnChessPieceClicked);
	FOnTimelineFloat newLocAlpha;
	newLocAlpha.BindDynamic(this, &ThisClass::UpdateNewLocAlpha);
	if (IsValid(NewLocAlphaCurve))
	{
		ChessPieceMovement->AddInterpFloat(NewLocAlphaCurve, newLocAlpha);
	}
}

void AChessPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChessPiece::OnChessPieceClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	bool isPlayerPiece = false;
	IsPlayerPiece(isPlayerPiece);
	if(!isPlayerPiece)
	{
		return;
	}
	SelectChessPiece();
	if (GetClass()->ImplementsInterface(UChessPieceInterface::StaticClass()))
	{
		bool isKing = false;
		IChessPieceInterface::Execute_ShowPossibleMoves(this, isKing);
	}
}

void AChessPiece::UpdateNewLocAlpha(float Alpha)
{
	FVector newLoc=FMath::Lerp(Billboard->GetComponentLocation(), mNewLoc,Alpha);
	Billboard->SetWorldLocation(newLoc);
}

void AChessPiece::MoveChessPiece(FVector NewLoc)
{
	mNewLoc = NewLoc;
	SlideAudio->Play();
	ChessPieceMovement->PlayFromStart();
}

void AChessPiece::Initialize()
{
	SetGameModeRef();
	SetPlayerControllerRef();

	MoveToDefault();
}

void AChessPiece::MoveToDefault()
{
	FVector squreLoc;
	bool isValidSomething = false;
	GameModeRef->GetSquareLocation(InitialX,InitialY, squreLoc, isValidSomething);
	if(!isValidSomething)
	{
		return;
	}
	Billboard->SetWorldLocation(squreLoc, false, nullptr, ETeleportType::TeleportPhysics);
	X = InitialX;
	Y = InitialY;
	GameModeRef->SetOccupant(this, X, Y, isValidSomething);
}

void AChessPiece::SetChessPieceColor()
{
	FLinearColor color;
	switch (Color)
	{
	case EPlayerColor::White:
		color = FLinearColor(0.286458, 0.206944, 0.159641);
		break;
	case EPlayerColor::Black:
		color = FLinearColor::Black;
		break;
	}
	ChessPiece->SetVectorParameterValueOnMaterials(TEXT("BaseColor"), FVector(color));
}

void AChessPiece::SetPlayerControllerRef()
{
	if (IsValid(PlayerControllerRef))
	{
		return;
	}
	PlayerControllerRef = Cast<APC_Chess>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AChessPiece::SetGameModeRef()
{
	if (IsValid(GameModeRef))
	{
		return;
	}
	GameModeRef = Cast<AGM_Chess>(UGameplayStatics::GetGameMode(GetWorld()));
}

void AChessPiece::SelectChessPiece()
{
	GameModeRef->SelectChessPiece(this,X,Y);
}

void AChessPiece::IsPlayerPiece(bool& IsPlayerPiece)
{
	EPlayerColor color=EPlayerColor::White;
	GameModeRef->GetActivePlayerColor(color);
	IsPlayerPiece = color == Color;
}

void AChessPiece::ProcessMovement(bool& Success)
{
	CanCaptureOpponent = false;
	IsValidMove = false;
	IsSuccessfulMove = false;
	KingHasCastled = false;

	ProcessOpponentToCapture(CanCaptureOpponent);
	ProcessTemporaryMove();

	ProcessKingCheckStatus(IsValidMove);

	if(IsValidMove)
	{
		if (!IsKing)
		{
			if (IsTeleportable)
			{
				ProcessTeleport(IsSuccessfulMove);
			}
			else
			{
				ProcessMove(IsSuccessfulMove);
			}
			ProcessOpponentCapture();
			ProcessPostMove();
		}
		else
		{
			ProcessCastle(IsSuccessfulMove);
			if(KingIsCastling)
			{
				bool tempB = false;
				ProcessPostCastle(tempB);
			}
			else
			{
				ProcessOpponentCapture();
				ProcessPostMove();
			}
		}
		GameModeRef->PersistMove(this, CanCaptureOpponent, KingHasCastled, Y < 5);
		PlayerControllerRef->UpdateMainUI();
		KingHasCastled = false;
	}
	else if(!IsKing)
	{
		ProcessMovementReset();
	}
	else
	{
		ProcessCastleReset();
	}
	Success = IsSuccessfulMove;
}

void AChessPiece::ProcessTemporaryMove()
{
	bool isValidSquare = false;
	ABoardSquare* square = GameModeRef->GetSelectedSquare(isValidSquare);
	if (!isValidSquare)
	{
		return;
	}

	PreviousX = X;
	PreviousY = Y;
	X = square->X;
	Y = square->Y;

	GameModeRef->RemoveOccupant(PreviousX, PreviousY, isValidSquare);
	if (!isValidSquare)
	{
		return;
	}
	GameModeRef->SetOccupant(this,X,Y, isValidSquare);
}

void AChessPiece::ProcessOpponentToCapture(bool& CanCapture)
{
	CanCapture = false;
	int32 tempX = 0;
	int32 tempY=0;
	bool isValidSquare = false;
	ABoardSquare* square = GameModeRef->GetSelectedSquare(isValidSquare);
	if(isValidSquare)
	{
		tempX=square->X;
		tempY=square->Y;
		bool isOccupied = false;
		bool isOccupiedByFriend = false;
		AChessPiece* piece=
			GameModeRef->GetOccupant(tempX, tempY,Color, isOccupied, isOccupiedByFriend,isValidSquare);
		if(isValidSquare)
		{
			if (isOccupied&&
				!isOccupiedByFriend)
			{
				OpponentRef = piece;
				CanCapture = true;
			}
			else if(IsEnPassant)
			{
				OpponentRef = nullptr;
			}
		}
	}
}

void AChessPiece::ProcessKingCheckStatus(bool& IsValidKing)
{
	bool isInCheck = false;
	GameModeRef->EvaluateCheckStatus(isInCheck);
	if(isInCheck)
	{
		PlayerControllerRef->SetMessage(TEXT("유효하지않은 움직임"));
		IsValidKing = false;
	}
	else
	{
		PlayerControllerRef->SetMessage(TEXT(""));
		if(IsEnPassant)
		{
			PlayerControllerRef->SetMessage(TEXT("En Passant"));
			IsValidKing = false;
		}
		else
		{
			IsValidKing = true;
		}
	}
}

void AChessPiece::ProcessMove(bool& Success)
{
	FVector squareLoc;
	GameModeRef->GetSquareLocation(X,Y, squareLoc, Success);
	if(Success)
	{
		MoveChessPiece(squareLoc);
	}
}

void AChessPiece::ProcessCastle(bool& Success)
{
	KingIsCastling = false;
	if((Y == 3||Y == 7)&&
		KingCanCastle)
	{ 
		KingIsCastling = true;
		ProcessTeleport(Success);
		int32 occupantY = 1;
		int32 offset = 1;
		if(Y>5)
		{
			offset = -1;
			occupantY = 8;
		}
		bool isOccupied = false;
		bool isOccupiedByFriend = false;
		bool isValidSquare = false;
		AChessPiece* piece =
			GameModeRef->GetOccupant(X, occupantY, Color, isOccupied, isOccupiedByFriend, isValidSquare);
		piece->PreviousY = piece->Y;
		piece->Y = Y+offset;
		piece->PreviousX = piece->X;
		PlayerControllerRef->SetMessage(TEXT("Castling"));
		piece->ProcessTeleport(Success);
		KingHasCastled = true;
	}
	else
	{
		ProcessMove(Success);
		KingIsCastling = false;
	}
}

void AChessPiece::ProcessTeleport(bool& Success)
{
	TeleportAudio->Play();
	FVector squareLoc;
	GameModeRef->GetSquareLocation(X,Y, squareLoc, Success);
	if(Success)
	{
		Billboard->SetWorldLocation(squareLoc,false,nullptr,ETeleportType::TeleportPhysics);
		GameModeRef->ActivateTeleportFX(X,Y);
	}
}

void AChessPiece::ProcessPostMove()
{
	GameModeRef->SetOccupants();
	GameModeRef->ResetSquares();
	IsInitialMove = false;
}

void AChessPiece::ProcessPostCastle(bool HasCastled)
{
	ProcessPostMove();
	IsInitialMove = false;
}

void AChessPiece::ProcessOpponentCapture()
{
	if(CanCaptureOpponent)
	{
		GameModeRef->ActivateExplosionFX(OpponentRef->X, OpponentRef->Y);
		GameModeRef->CaptureChessPiece(OpponentRef);
	}
}

void AChessPiece::ProcessMovementReset()
{
	X = PreviousX;
	Y = PreviousY;
	OpponentRef = nullptr;
	ProcessPostMove();
}

void AChessPiece::ProcessCastleReset()
{
	ProcessMovementReset();
	if(KingIsCastling)
	{
		bool isOccupied = false;
		bool isOccupiedByFriend = false;
		bool isValidSquare = false;
		AChessPiece* piece = nullptr;
		if (Y>5)
		{
			piece= GameModeRef->GetOccupant(
				X,8,Color, isOccupied, isOccupiedByFriend, isValidSquare);
		}
		else
		{
			piece = GameModeRef->GetOccupant(
				X, 1, Color, isOccupied, isOccupiedByFriend, isValidSquare);
		}
		piece->ProcessMovementReset();
	}
}

void AChessPiece::ProcessVirtualMovement(int32 InX, int32 InY, EPlayerColor InColor)
{
	int32 tempX = InX;
	int32 tempY = InY;

	PreviousX= InX;
	PreviousY= InY;

	bool isOccupied = false;
	bool isOccupiedByFriend = false;
	bool isValidSquare = false;
	AChessPiece* piece=
		GameModeRef->GetOccupant(InX, InY,Color, isOccupied, isOccupiedByFriend, isValidSquare);
	if(isValidSquare)
	{
		OpponentRef = nullptr;
		if(isOccupied&&
			!isOccupiedByFriend)
		{
			OpponentRef = piece;
			X = InX;
			Y = InY;
			GameModeRef->RemoveOccupant(PreviousX, PreviousY, isValidSquare);
			GameModeRef->SetOccupant(this,X,Y, isValidSquare);
		}
	}
}

void AChessPiece::HighlightLoopSequence(int32 InX, int32 InY, EPlayerColor InColor,
	int32 XIncr, int32 YIncr, EPlayerColor TempColor, int32 TempX, int32 TempY, 
	bool CanContinue)
{
}

void AChessPiece::HighlightHorizontalSquares(EPlayerColor InColor, EPlayerColor TempColor,
	int32 TempX, int32 TempY)
{
}

void AChessPiece::HighlightVerticalSquares(EPlayerColor InColor, EPlayerColor TempColor,
	int32 TempX, int32 TempY)
{
}

void AChessPiece::HighlightDiagonalSquares(EPlayerColor InColor, EPlayerColor TempColor,
	int32 TempX, int32 TempY)
{
}

void AChessPiece::HighlightPotentialSquare(int32 InX, int32 InY, EPlayerColor InColor,
	bool& CanContinueLoop)
{
	bool canHighlightSquare = false;
	CanHighlightSquare(InX, InY,InColor, canHighlightSquare, CanContinueLoop);
	if(canHighlightSquare)
	{
		GameModeRef->HighlightSquare(InX,InY);
	}
}

void AChessPiece::CanHighlightSquare(int32 InX, int32 InY, EPlayerColor InColor,
	bool& CanHightlightSquare, bool& IsEmptySquare)
{
	bool isOccupied = false;
	bool isOccupiedByFriend = false;
	bool isValidSquare = false;
	GameModeRef->GetOccupant(InX,InY,Color, isOccupied, isOccupiedByFriend, isValidSquare);
	if(isValidSquare)
	{
		if (isOccupied)
		{
			if (isOccupiedByFriend)
			{
				CanHightlightSquare = false;
				IsEmptySquare = false;
			}
			else
			{
				CanHightlightSquare = true;
				IsEmptySquare = false;
			}
		}
		else
		{
			CanHightlightSquare = true;
			IsEmptySquare = true;
		}
	}
	else
	{
		CanHightlightSquare = false;
		IsEmptySquare = false;
	}
}

void AChessPiece::HasLegalMove(bool& HasLegalMove)
{
	GameModeRef->UnhighlightSquares();
	if (GetClass()->ImplementsInterface(UChessPieceInterface::StaticClass()))
	{
		bool isKing = false;
		IChessPieceInterface::Execute_ShowPossibleMoves(this, isKing);
	}
	TArray<ABoardSquare*> hightlightedSquares;
	GameModeRef->GetHightlightedSquares(hightlightedSquares);
	GameModeRef->UnhighlightSquares();
	HasLegalMove = false;
	for(auto& hightlightedSquare:hightlightedSquares)
	{
		IsLegalMove(hightlightedSquare->X, hightlightedSquare->Y, HasLegalMove);
		if(HasLegalMove)
		{
			break;
		}
	}
}

void AChessPiece::IsLegalMove(int32 InX, int32 InY, bool& IsLegalMove)
{
	ProcessVirtualMovement(InX, InY,Color);
	bool IsKingInCheck = false;
	GameModeRef->EvaluateCheckStatus(IsKingInCheck);
	ProcessMovementReset();
	IsLegalMove = !IsKingInCheck;
}
