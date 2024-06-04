#include "GM_Chess.h"
#include "PC_Chess.h"
#include "PlayerPawn.h"
#include "Board/Board.h"
#include "ChessPieces/ChessPiece.h"
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

void AGM_Chess::ProcessMove()
{
	ChangeActivePlayer();
}

void AGM_Chess::Initialize()
{
	SetPlayerControllerRef();
	SetPlayerRef();
	SetBoardRef();
	SetChessPiecesRef();

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
}

void AGM_Chess::ProcessChessPiece(AChessPiece* ChessPiece)
{
	AChessPiece* tempChessPiece = ChessPiece;
	tempChessPiece->Initialize();
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
	ActivePlayer = (ActivePlayer + 1)%(int32)EPlayerColor::Max;
	SetPlayerCamera();
	EPlayerColor color;
	GetActivePlayerColor(color);
	if(color==EPlayerColor::White)
	{
		++MoveCount;
	}
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

void AGM_Chess::StartGame(FText PlayerAName, FText PlayerBName, int32 PlayerAIndex, int32 PlayerBIndex)
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
}

void AGM_Chess::ActivateTeleport(int32 X, int32 Y)
{
}

void AGM_Chess::GetActiveChessPiecesByColor(EPlayerColor Color, TArray<AChessPiece*>& ChessPieces, 
	TArray<AChessPiece*> ActiveChessPieces)
{
}

void AGM_Chess::GetGameStatus(bool& IsCheckMate, bool& IsStaleMate)
{
	FChessPlayer tempActivePlayer;
	GetActivePlayer(tempActivePlayer);
	IsCheckMate = tempActivePlayer.IsInCheckFlag && !tempActivePlayer.HasLegalMoves;
	IsStaleMate = !tempActivePlayer.HasLegalMoves;
}

void AGM_Chess::PersistMove(AChessPiece* ChessPiece, bool IsCapture, bool IsCastle, 
	bool IsQueenSideCastle, FString ChessPieceNotation, FString CaptureNotation, 
	FString SquareNotation, FString CheckNotation, FString FinalNotation, 
	bool bIsCapture, bool bIsCastle, bool bIsQueenSideCastle, bool bIsInCheck, 
	AChessPiece* lChessPiece)
{
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
}

void AGM_Chess::SelectChessPiece(AChessPiece* ChessPiece, int32 X, int32 Y)
{
}

void AGM_Chess::GetSelectedChessPiece(AChessPiece*& SelectedChessPiece, bool& IsValidPiece)
{
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
}

void AGM_Chess::SetOccupant(AChessPiece* ChessPiece, int32 X, int32 Y, bool& IsValid)
{
}

void AGM_Chess::RemoveOccupant(int32 X, int32 Y, bool& IsValid)
{
}

void AGM_Chess::GetOccupant(int32 X, int32 Y, EPlayerColor Color, AChessPiece*& Occupant, 
	bool& IsOccupied, bool& IsOccupiedByFriend, bool& IsValidSquare)
{
}

void AGM_Chess::SetOccupants()
{
}

void AGM_Chess::RemoveOccupants()
{
}

void AGM_Chess::IsActiveKingCheckStatus(bool& isActiveKingInCheck)
{
}

void AGM_Chess::EvaluateCheckStatus(bool& IsInCheck, int32 TempX, int32 TempY, EPlayerColor TempColor)
{
}

void AGM_Chess::GetActiveKing(AChessPiece*& ActiveKing)
{
}

void AGM_Chess::EvaluateDiagonalSquares(int32 X, int32 Y, EPlayerColor Color, bool& IsAttackable, 
	int32 TempX, int32 TempY, EPlayerColor TempColor)
{
}

void AGM_Chess::EvaluateHorizontalSquares(int32 X, int32 Y, EPlayerColor Color, bool& IsAttackable, 
	int32 TempX, int32 TempY, EPlayerColor TempColor)
{
}

void AGM_Chess::EvaluateVerticalSquares(int32 X, int32 Y, EPlayerColor Color, bool& IsAttackable, 
	int32 TempX, int32 TempY, EPlayerColor TempColor)
{
}

void AGM_Chess::EvaluateForKnights(int32 X, int32 Y, EPlayerColor Color, bool& IsAttackable, 
	int32 TempX, int32 TempY, EPlayerColor TempColor)
{
}

void AGM_Chess::EvaluateKnightSquare(int32 X, int32 Y, int32 XIncr, int32 YIncr, EPlayerColor Color, 
	bool& IsAttackable, int32 TempX, int32 TempY, EPlayerColor TempColor)
{
}

void AGM_Chess::EvalScquareForCheckStatus(int32 X, int32 Y, EPlayerColor Color, bool& IsEmpty, 
	bool& IsCheckable, int32 TempX, int32 TempY, EPlayerColor TempColor, bool IsInCheck)
{
}

void AGM_Chess::EvaluationLoop(int32 X, int32 Y, int32 XInc, int32 YInc, EPlayerColor Color, 
	bool& IsCheckablePath, int32 TempX, int32 TempY, bool CanContinue, bool IsCheckable)
{
}

void AGM_Chess::CaptureChessPiece(AChessPiece* ChessPiece)
{
}
