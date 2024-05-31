#include "PlayerPawn.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn::GetPlayerByIndex(int32 PlayerIndex, FChessPlayer& Player)
{
}

void APlayerPawn::GetPlayerByColor(EPlayerColor PlayerColor, FChessPlayer& Player, 
	FChessPlayer PlayerA, FChessPlayer PlayerB)
{
}

void APlayerPawn::SetPlayerColor(int32 PlayerIndex, EPlayerColor PlayerColor)
{
}

void APlayerPawn::SetPlayerName(int32 PlayerIndex, FString PlayerName)
{
}

void APlayerPawn::IncrementPlayerMoveCount(int32 PlayerIndex)
{
}

void APlayerPawn::IncrementPlayerCaptureCount(int32 PlayerIndex)
{
}

void APlayerPawn::SetKingInCheckFlag(int32 PlayerIndex, bool IsInCheck)
{
}

void APlayerPawn::SetHasLegalMovesFlag(int32 PlayerIndex, bool HasLegalMoves)
{
}

void APlayerPawn::RotateCamera(double Axis)
{
}
