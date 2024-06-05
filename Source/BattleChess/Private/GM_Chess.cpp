#include "GM_Chess.h"
#include "PC_Chess.h"
#include "PlayerPawn.h"
#include "Board/Board.h"
#include "Board/BoardSquare.h"
#include "ChessPieces/ChessPiece.h"
#include "Board/DeadSlot.h"
#include <Kismet/GameplayStatics.h>

AGM_Chess::AGM_Chess()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = APC_Chess::StaticClass();

	ActivePlayer = 0;
	MoveCount = 0;
	DeadPoolIndex = 0;
}

void AGM_Chess::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

void AGM_Chess::DelayChangeActivePlayer()
{
	ChangeActivePlayer();
	PlayerControllerRef->SetMessage(TEXT(""));
	PlayerControllerRef->UpdateMainUI();
}

void AGM_Chess::ProcessMove()
{
	bool isValidPiece = false;
	AChessPiece* piece=	GetSelectedChessPiece(isValidPiece);
	if (isValidPiece)
	{
		piece->ProcessMovement(isValidPiece);
		if (isValidPiece)
		{
			FTimerHandle tempTimer;
			GetWorld()->GetTimerManager().SetTimer(tempTimer,this,&ThisClass::DelayChangeActivePlayer,3.f);
		}
		else
		{
			PlayerControllerRef->UpdateMainUI();
		}
	}
}

void AGM_Chess::Initialize()
{
	SetPlayerControllerRef();
	SetPlayerRef();
	SetBoardRef();
	SetChessPiecesRef();
	SetupDeadPoolRefs();

	StartGame(FText::GetEmpty(), FText::GetEmpty(), 0, 0);
}

void AGM_Chess::SetPlayerControllerRef()
{
	if (IsValid(PlayerControllerRef))
	{
		return;
	}
	PlayerControllerRef = Cast<APC_Chess>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerControllerRef->Initialize();
}

void AGM_Chess::SetPlayerRef()
{
	if (IsValid(PlayerRef))
	{
		return;
	}
	PlayerRef = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AGM_Chess::SetBoardRef()
{
	if (IsValid(BoardRef))
	{
		return;
	}
	BoardRef = Cast<ABoard>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoard::StaticClass()));
	BoardRef->Initialize();
}

void AGM_Chess::SetChessPiecesRef()
{
	if (!ChessPiecesRef.IsEmpty())
	{
		return;
	}
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChessPiece::StaticClass(), actors);
	for(auto& actor: actors)
	{
		AChessPiece* chessPiece = Cast<AChessPiece>(actor);
		if(!IsValid(chessPiece))
		{
			continue;
		}
		ChessPiecesRef.Add(chessPiece);
	}
	for (auto& chessPiece : ChessPiecesRef)
	{
		ProcessChessPiece(chessPiece);
	}
}

void AGM_Chess::SetupDeadPoolRefs()
{
	if (!DeadPoolRef.IsEmpty())
	{
		return;
	}
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADeadSlot::StaticClass(), actors);
	for (auto& actor : actors)
	{
		ADeadSlot* deadSlot = Cast<ADeadSlot>(actor);
		if (!IsValid(deadSlot))
		{
			continue;
		}
		DeadPoolRef.Add(deadSlot);
	}
	DeadPoolIndex = 0;
}

void AGM_Chess::ProcessChessPiece(AChessPiece* ChessPiece)
{
	ChessPiece->Initialize();
	if(ChessPiece->IsKing)
	{
		switch (ChessPiece->Color)
		{
		case EPlayerColor::White:
			WhiteKingRef = ChessPiece;
			break;
		case EPlayerColor::Black:
			BlackKingRef = ChessPiece;
			break;
		}
	}
}

void AGM_Chess::SetPlayerCamera()
{
	FChessPlayer chessPlayer;
	PlayerRef->GetPlayerByIndex(ActivePlayer, chessPlayer);
	PlayerRef->SetPlayerCamera(chessPlayer.Color);
}

void AGM_Chess::GetActivePlayer(FChessPlayer& Player)
{
	PlayerRef->GetPlayerByIndex(ActivePlayer, Player);
}

void AGM_Chess::GetActivePlayerColor(EPlayerColor& ActivePlayerColor)
{
	FChessPlayer player;
	GetActivePlayer(player);
	ActivePlayerColor = player.Color;
}

void AGM_Chess::GetPlayerByColor(EPlayerColor PlayerColor, FChessPlayer& Player)
{
	PlayerRef->GetPlayerByColor(PlayerColor, Player);
}

void AGM_Chess::GetPlayerByIndex(int32 PlayerIndex, FChessPlayer& Player)
{
	PlayerRef->GetPlayerByIndex(PlayerIndex, Player);
}

void AGM_Chess::ChangeActivePlayer()
{
	PlayerRef->IncrementPlayerMoveCount(ActivePlayer);
	PlayerRef->SetKingInCheckFlag(ActivePlayer,false);

	ActivePlayer = (ActivePlayer + 1)%(int32)EPlayerColor::Max;
	SetPlayerCamera();
	EPlayerColor color;
	GetActivePlayerColor(color);
	if(color==EPlayerColor::White)
	{
		++MoveCount;
	}

	bool isInCheck=false;
	EvaluateCheckStatus(isInCheck);
	PlayerRef->SetKingInCheckFlag(ActivePlayer, isInCheck);
	AddCheckToLastMoveData();
	bool hasLegalMove = false;
	HasLegalMove(hasLegalMove);
	PlayerRef->SetHasLegalMovesFlag(ActivePlayer, hasLegalMove);
	PlayerControllerRef->UpdateMainUI();
}

void AGM_Chess::GetActivePlayerMoveCount(int32& ActivePlayerMoveCount)
{
	FChessPlayer tempActivePlayer;
	GetActivePlayer(tempActivePlayer);
	ActivePlayerMoveCount = tempActivePlayer.MoveCount;
}

void AGM_Chess::RotatePlayerCamera(float Axis)
{
	PlayerRef->RotateCamera(Axis);
}

void AGM_Chess::StartGame(FText PlayerAName, FText PlayerBName, int32 PlayerAIndex, 
	int32 PlayerBIndex)
{
	PlayerControllerRef->SetMainUI();
	SetPlayerCamera();
}

void AGM_Chess::GetMoveCount(int32& Count)
{
	Count = MoveCount;
}

void AGM_Chess::HasLegalMove(bool& HasLegalMove)
{
	EPlayerColor color = EPlayerColor::White;
	GetActivePlayerColor(color);
	TArray<AChessPiece*> chessPieces;
	GetActiveChessPiecesByColor(color, chessPieces);
	HasLegalMove = false;
	for(auto& chessPiece: chessPieces)
	{
		chessPiece->HasLegalMove(HasLegalMove);
		if(HasLegalMove)
		{
			break;
		}
	}
	UnhighlightSquares();
}

void AGM_Chess::GetLatestMove(EPlayerColor& Color, FString& LatestMove)
{
	if(Movements.IsEmpty())
	{
		return;
	}
	FMoves moves = Movements.Last();
	CreateNotation(moves, LatestMove);
	Color = moves.Color;
}

void AGM_Chess::ActivateExplosionFX(int32 X, int32 Y)
{
	BoardRef->ActivateExplosionFX(X,Y);
}

void AGM_Chess::ActivateTeleportFX(int32 X, int32 Y)
{
	BoardRef->ActivateTeleportFX(X, Y);
}

void AGM_Chess::GetActiveChessPiecesByColor(EPlayerColor Color,
	TArray<AChessPiece*>& ChessPieces)
{
	TArray<AChessPiece*> activeChessPieces;
	for (auto& chessPiece : ChessPiecesRef)
	{
		if (chessPiece->X > 0&&
			chessPiece->Y > 0&&
			chessPiece->Color==Color)
		{
			activeChessPieces.Add(chessPiece);
		}
	}
	ChessPieces = activeChessPieces;
}

void AGM_Chess::GetGameStatus(bool& IsCheckMate, bool& IsStaleMate)
{
	FChessPlayer tempActivePlayer;
	GetActivePlayer(tempActivePlayer);
	IsCheckMate = tempActivePlayer.IsInCheckFlag && !tempActivePlayer.HasLegalMoves;
	IsStaleMate = !tempActivePlayer.HasLegalMoves;
}

void AGM_Chess::PersistMove(AChessPiece* ChessPiece, bool IsCapture, 
	bool IsCastle, bool IsQueenSideCastle)
{
	FMoves moves;
	moves.MoveCount = MoveCount;
	moves.Color = ChessPiece->Color;
	moves.ChessPiece = ChessPiece->Notation;
	bool isExistSquare = false;
	moves.PreviousSquare = BoardRef->GetSquare(ChessPiece->PreviousX, ChessPiece->PreviousY, isExistSquare)->Notation;
	moves.NewSquare = BoardRef->GetSquare(ChessPiece->X, ChessPiece->Y, isExistSquare)->Notation;
	moves.IsCapture= IsCastle;
	moves.IsKingSideCastle = IsCastle && !IsQueenSideCastle;
	moves.IsQueenSideCastle = IsCastle && IsQueenSideCastle;
	SaveMoveData(moves);
}

void AGM_Chess::CreateNotation(FMoves MoveData, FString& Notation)
{
	Notation = FString::Printf(TEXT("%d: "),MoveData.MoveCount);
	if(MoveData.IsKingSideCastle)
	{
		Notation += TEXT("0-0");
		return;
	}
	if (MoveData.IsQueenSideCastle)
	{
		Notation += TEXT("0-0-0");
		return;
	}
	Notation += MoveData.ChessPiece;
	if (MoveData.IsCapture)
	{
		Notation += TEXT("x");
	}
	Notation += MoveData.NewSquare;
	if (MoveData.IsCheck)
	{
		Notation += TEXT("+");
	}
}

void AGM_Chess::SaveMoveData(FMoves MoveData)
{
	MoveData.IsCheck = false;
	MoveData.IsCheckMate = false;
	MoveData.IsStaleMate = false;
	Movements.Add(MoveData);
}

void AGM_Chess::AddCheckToLastMoveData()
{
	if(Movements.IsEmpty())
	{
		return;
	}
	Movements.Last().IsCheck=true;
}

void AGM_Chess::SelectChessPiece(AChessPiece* ChessPiece, int32 X, int32 Y)
{
	ResetSquares();
	SelectedPieceRef=nullptr;

	BoardRef->SelectOccupant(X,Y);
	SelectedPieceRef = ChessPiece;
}

AChessPiece* AGM_Chess::GetSelectedChessPiece(bool& IsValidPiece)
{
	IsValidPiece = IsValid(SelectedPieceRef);
	return SelectedPieceRef;
}

void AGM_Chess::GetSquareLocation(int32 X, int32 Y, FVector& SquareLocation, 
	bool& IsValidLoc)
{
	BoardRef->GetSquareLocation(X,Y,SquareLocation,IsValidLoc);
}

void AGM_Chess::ResetSquares()
{
	BoardRef->ResetSquares();
}

void AGM_Chess::HighlightSquare(int32 X, int32 Y)
{
	BoardRef->HighlightSquare(X,Y);
}

void AGM_Chess::UnhighlightSquares()
{
	BoardRef->UnhighlightSquares();
}

void AGM_Chess::SelectSquare(int32 X, int32 Y)
{
	BoardRef->SelectSquare(X,Y);
}

ABoardSquare* AGM_Chess::GetSelectedSquare(bool& IsValid)
{
	return BoardRef->GetSelectedSquare(IsValid);
}

void AGM_Chess::GetHightlightedSquares(TArray<ABoardSquare*>& HightlightedSquares)
{
	BoardRef->GetHightlightedSquares(HightlightedSquares);
}

void AGM_Chess::SetOccupant(AChessPiece* ChessPiece, int32 X, int32 Y, 
	bool& IsValidSquare)
{
	BoardRef->SetOccupant(ChessPiece,X,Y, IsValidSquare);
}

void AGM_Chess::RemoveOccupant(int32 X, int32 Y, bool& IsValidSquare)
{
	BoardRef->RemoveOccupant(X, Y, IsValidSquare);
}

AChessPiece* AGM_Chess::GetOccupant(int32 X, int32 Y, EPlayerColor Color,
	bool& IsOccupied, bool& IsOccupiedByFriend, bool& IsValidSquare)
{
	return BoardRef->GetOccupant(X, Y, Color, IsOccupied, IsOccupiedByFriend,IsValidSquare);
}

void AGM_Chess::SetOccupants()
{
	RemoveOccupants();
	for(auto& chessPiece :ChessPiecesRef)
	{
		bool isValidSquare=false;
		SetOccupant(chessPiece, chessPiece->X, chessPiece->Y, isValidSquare);
	}
}

void AGM_Chess::RemoveOccupants()
{
	BoardRef->RemoveAllOccupants();
}

void AGM_Chess::IsActiveKingCheckStatus(bool& isActiveKingInCheck)
{
	FChessPlayer player;
	PlayerRef->GetPlayerByIndex(ActivePlayer, player);
	isActiveKingInCheck = player.IsInCheckFlag;
}

void AGM_Chess::EvaluateCheckStatus(bool& IsInCheck)
{
}

AChessPiece* AGM_Chess::GetActiveKing()
{
	EPlayerColor color = EPlayerColor::White;
	GetActivePlayerColor(color);
	if(color==EPlayerColor::White)
	{
		return WhiteKingRef;
	}
	return BlackKingRef;
}

void AGM_Chess::EvaluateDiagonalSquares(int32 X, int32 Y, EPlayerColor Color,
	bool& IsAttackable)
{
	EvaluationLoop(X,Y,1,1,Color,IsAttackable);
	if(IsAttackable)
	{
		return;
	}
	EvaluationLoop(X, Y, -1, -1, Color, IsAttackable);
	if (IsAttackable)
	{
		return;
	}
	EvaluationLoop(X, Y, 1, -1, Color, IsAttackable);
	if (IsAttackable)
	{
		return;
	}
	EvaluationLoop(X, Y, -1, 1, Color, IsAttackable);
}

void AGM_Chess::EvaluateHorizontalSquares(int32 X, int32 Y, EPlayerColor Color, 
	bool& IsAttackable)
{
	EvaluationLoop(X, Y, 0, 1, Color, IsAttackable);
	if (IsAttackable)
	{
		return;
	}
	EvaluationLoop(X, Y, 0, -1, Color, IsAttackable);
}

void AGM_Chess::EvaluateVerticalSquares(int32 X, int32 Y, EPlayerColor Color, 
	bool& IsAttackable)
{
	EvaluationLoop(X, Y, 1, 0, Color, IsAttackable);
	if (IsAttackable)
	{
		return;
	}
	EvaluationLoop(X, Y, -1, 0, Color, IsAttackable);
}

void AGM_Chess::EvaluateForKnights(int32 X, int32 Y, EPlayerColor Color, 
	bool& IsAttackable)
{
}

void AGM_Chess::EvaluateKnightSquare(int32 X, int32 Y, int32 XIncr, int32 YIncr, 
	EPlayerColor Color, bool& IsAttackable)
{
}

void AGM_Chess::EvaluateSquareForCheckStatus(int32 X, int32 Y, EPlayerColor Color, 
	bool& IsEmpty, bool& IsCheckable)
{
	bool isOccupied=false;
	bool isOccupiedByFriend=false;
	bool isValidSquare=false;
	AChessPiece* piece=BoardRef->GetOccupant(X,Y,Color, isOccupied, isOccupiedByFriend, isValidSquare);
	if(isValidSquare)
	{
		if(isOccupied)
		{
			if (isOccupiedByFriend)
			{
				IsEmpty = false;
				IsCheckable = false;
			}
			else if (piece->GetClass()->ImplementsInterface(UChessPieceInterface::StaticClass()))
			{
				bool isKing = false;
				IChessPieceInterface::Execute_ShowPossibleMoves(piece, isKing);
				AChessPiece* king= GetActiveKing();
				bool isExistSquare = false;
				ABoardSquare* square= BoardRef->GetSquare(king->X, king->Y, isExistSquare);
				if (isExistSquare) 
				{
					AttackingPieceRef= piece;
					BoardRef->ResetSquares();
					IsEmpty = false;
					IsCheckable = square->IsAttackable;
				}
				else
				{
					BoardRef->ResetSquares();
					IsEmpty = false;
					IsCheckable = false;
				}
			}
		}
		else
		{
			IsEmpty = true;
			IsCheckable = false;
		}
	}
	else
	{
		IsEmpty = false;
		IsCheckable = false;
	}
}

void AGM_Chess::EvaluationLoop(int32 X, int32 Y, int32 XInc, int32 YInc, 
	EPlayerColor Color, bool& IsCheckablePath)
{
	int32 tempX = X;
	int32 tempY = Y;
	bool canContinue = true;

	while(canContinue)
	{
		tempX+=XInc;
		tempY += YInc;
		bool isEmpty = false;
		EvaluateSquareForCheckStatus(tempX, tempY,Color, canContinue, IsCheckablePath);
		if(IsCheckablePath)
		{
			canContinue = false;
		}
	}
}

void AGM_Chess::CaptureChessPiece(AChessPiece* ChessPiece)
{
	FVector deadPoolLoc=DeadPoolRef[DeadPoolIndex]->GetRootComponent()->GetComponentLocation();
	ChessPiece->GetRootComponent()->SetWorldLocation(deadPoolLoc,false,nullptr,ETeleportType::TeleportPhysics);
	ChessPiece->X = 0;
	ChessPiece->Y = 0;
	++DeadPoolIndex;
}
