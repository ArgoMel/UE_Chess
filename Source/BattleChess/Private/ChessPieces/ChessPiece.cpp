#include "ChessPieces/ChessPiece.h"

AChessPiece::AChessPiece()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
}

void AChessPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChessPiece::Initialize()
{
}

void AChessPiece::MoveToDefault()
{
}

void AChessPiece::SetChessPieceColor()
{
}

void AChessPiece::SetPlayerControllerRef()
{
}

void AChessPiece::SetGameModeRef()
{
}

void AChessPiece::SelectChessPiece()
{
}

void AChessPiece::IsPlayerPiece(bool& IsPlayerPiece)
{
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
}

void AChessPiece::HasLegalMove(bool& HasLegalMove, TArray<ABoardSquare*> HightlightedSquares)
{
}

void AChessPiece::IsLegalMove(int32 InX, int32 InY, bool& IsLegalMove, bool IsKingInCheck)
{
}
