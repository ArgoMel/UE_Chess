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

