#include "GM_Chess.h"

void AGM_Chess::Initialize()
{
}

void AGM_Chess::SetPlayerControllerRef()
{
}

void AGM_Chess::SetPlayerRef()
{
}

void AGM_Chess::SetBoardRef()
{
}

void AGM_Chess::SetChessPiecesRef()
{
}

void AGM_Chess::SetupDeadPoolRefs()
{
}

void AGM_Chess::ProcessChessPiece(AChessPiece* ChessPiece, AChessPiece* TempChessPiece)
{
}

void AGM_Chess::SetPlayerCamera()
{
}

void AGM_Chess::GetActivePlayer(FChessPlayer& Player)
{
}

void AGM_Chess::GetActivePlayerColor(EPlayerColor& ActivePlayerColor)
{
}

void AGM_Chess::GetPlayerByColor(EPlayerColor PlayerColor, FChessPlayer& Player)
{
}

void AGM_Chess::GetPlayerByIndex(int32 PlayerIndex, FChessPlayer& Player)
{
}

void AGM_Chess::ChangeActivePlayer()
{
}

void AGM_Chess::GetActivePlayerMoveCount(int32& ActivePlayerMoveCount)
{
}

void AGM_Chess::RotatePlayerCamera(double Axis)
{
}

void AGM_Chess::StartGame(FText PlayerAName, FText PlayerBName, int32 PlayerAIndex, int32 PlayerBIndex)
{
}

void AGM_Chess::GetMoveCount(int32& Count)
{
}

void AGM_Chess::HasLegalMove(bool& HasLegalMove)
{
}

void AGM_Chess::GetLatestMove(EPlayerColor& Color, FText& LatestMove)
{
}

void AGM_Chess::ActivateExplosionFX(int32 X, int32 Y)
{
}

void AGM_Chess::ActivateTeleport(int32 X, int32 Y)
{
}

void AGM_Chess::GetActiveChessPiecesByColor(EPlayerColor Color, TArray<AChessPiece*>& ChessPieces, TArray<AChessPiece*> ActiveChessPieces)
{
}

void AGM_Chess::GetGameStatus(bool& IsCheckMate, bool& IsStaleMate, FChessPlayer TempActivePlayer)
{
}

void AGM_Chess::PersistMove(AChessPiece* ChessPiece, bool IsCapture, bool IsCastle, bool IsQueenSideCastle, FString ChessPieceNotation, FString CaptureNotation, FString SquareNotation, FString CheckNotation, FString FinalNotation, bool bIsCapture, bool bIsCastle, bool bIsQueenSideCastle, bool bIsInCheck, AChessPiece* lChessPiece)
{
}

void AGM_Chess::CreateNotation(FMoves MoveData, FString& Notation, FString MoveNotation, FString ChessPiece, FString Square, bool bIsCheck, bool bIsCapture, bool bIsKingsideCastle, bool bIsQueensideCastle)
{
}

void AGM_Chess::SaveMoveData(int32 Count, EPlayerColor Color, FString ChessPieceNotation, FString PreviousSquare, FString NewSquare, bool IsCapture, bool IsKingsideCastle, bool IsQueenSideCastle)
{
}

void AGM_Chess::AddCheckToLastMoveData()
{
}

void AGM_Chess::SelectChessPiece(AChessPiece* ChessPiece, int32 X, int32 Y)
{
}

void AGM_Chess::GetSelectedChessPiece(AChessPiece*& SelectedChessPiece, bool& IsValid)
{
}

void AGM_Chess::GetSquareLocation(int32 X, int32 Y, FVector& SquareLocation, bool& IsValid)
{
}

void AGM_Chess::ResetSquares()
{
}

void AGM_Chess::HighllightSquare(int32 X, int32 Y)
{
}

void AGM_Chess::UnhighlightSquares()
{
}

void AGM_Chess::SelectSquare(int32 X, int32 Y)
{
}

void AGM_Chess::GetSelectedSquare(ABoardSquare*& SelectedSquare, bool& IsValid)
{
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

void AGM_Chess::GetOccupant(int32 X, int32 Y, EPlayerColor Color, AChessPiece*& Occupant, bool& IsOccupied, bool& IsOccupiedByFriend, bool& IsValidSquare)
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

void AGM_Chess::EvaluateDiagonalSquares(int32 X, int32 Y, EPlayerColor Color, bool& IsAttackable, int32 TempX, int32 TempY, EPlayerColor TempColor)
{
}

void AGM_Chess::EvaluateHorizontalSquares(int32 X, int32 Y, EPlayerColor Color, bool& IsAttackable, int32 TempX, int32 TempY, EPlayerColor TempColor)
{
}

void AGM_Chess::EvaluateVerticalSquares(int32 X, int32 Y, EPlayerColor Color, bool& IsAttackable, int32 TempX, int32 TempY, EPlayerColor TempColor)
{
}

void AGM_Chess::EvaluateForKnights(int32 X, int32 Y, EPlayerColor Color, bool& IsAttackable, int32 TempX, int32 TempY, EPlayerColor TempColor)
{
}

void AGM_Chess::EvaluateKnightSquare(int32 X, int32 Y, int32 XIncr, int32 YIncr, EPlayerColor Color, bool& IsAttackable, int32 TempX, int32 TempY, EPlayerColor TempColor)
{
}

void AGM_Chess::EvalScquareForCheckStatus(int32 X, int32 Y, EPlayerColor Color, bool& IsEmpty, bool& IsCheckable, int32 TempX, int32 TempY, EPlayerColor TempColor, bool IsInCheck)
{
}

void AGM_Chess::EvaluationLoop(int32 X, int32 Y, int32 XInc, int32 YInc, EPlayerColor Color, bool& IsCheckablePath, int32 TempX, int32 TempY, bool CanContinue, bool IsCheckable)
{
}

void AGM_Chess::CaptureChessPiece(AChessPiece* ChessPiece)
{
}
