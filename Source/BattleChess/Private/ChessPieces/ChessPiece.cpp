#include "ChessPieces/ChessPiece.h"
#include "GM_Chess.h"
#include "PC_Chess.h"
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
	KindCanCastle = false;

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
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MI_WhiteSquare(TEXT(
		"/Game/BattleChess/Materials/MI_WhitePiece.MI_WhitePiece"));
	if (MI_WhiteSquare.Succeeded())
	{
		ChessPiece->SetMaterial(0, MI_WhiteSquare.Object);
	}

	SlideAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Slide"));
	SlideAudio->SetupAttachment(Billboard);
	static ConstructorHelpers::FObjectFinder<USoundBase> Teleport_Mode_Entered(TEXT(
		"/Game/BattleChess/Audio/Teleport_Mode_Entered.Teleport_Mode_Entered"));
	if (Teleport_Mode_Entered.Succeeded())
	{
		SlideAudio->SetSound(Teleport_Mode_Entered.Object);
	}

	TeleportAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Teleport"));
	TeleportAudio->SetupAttachment(Billboard);
	static ConstructorHelpers::FObjectFinder<USoundBase> Teleport(TEXT(
		"/Game/BattleChess/Audio/Teleport.Teleport"));
	if (Teleport.Succeeded())
	{
		TeleportAudio->SetSound(Teleport.Object);
	}

	ButtonClickAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ButtonClick"));
	ButtonClickAudio->SetupAttachment(Billboard);
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
}

void AChessPiece::ProcessTemporaryMove()
{
}

void AChessPiece::ProcessOpponentToCapture(bool& CanCapture, int32 TempX, int32 TempY)
{
}

void AChessPiece::ProcessKingCheckStatus(bool& IsValid)
{
}

void AChessPiece::ProcessMove(bool& Success)
{
}

void AChessPiece::ProcessCastle(bool& Success)
{
}

void AChessPiece::ProcessTeleport(bool& Success)
{
}

void AChessPiece::ProcessPostMove()
{
}

void AChessPiece::ProcessPostCastle(bool HasCastled)
{
}

void AChessPiece::ProcessOpponentCapture()
{
}

void AChessPiece::ProcessMovementReset()
{
}

void AChessPiece::ProcessCastleReset()
{
}

void AChessPiece::ProcessVirtualMovement(int32 InX, int32 InY, EPlayerColor InColor, 
	int32 TempX, int32 TempY)
{
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
	bool& CanContinueLoop, int32 TempX, int32 TempY)
{
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

void AChessPiece::HasLegalMove(bool& HasLegalMove, TArray<ABoardSquare*> HightlightedSquares)
{
}

void AChessPiece::IsLegalMove(int32 InX, int32 InY, bool& IsLegalMove, bool IsKingInCheck)
{
}
