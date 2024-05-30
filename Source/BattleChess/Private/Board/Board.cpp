#include "Board/Board.h"

ABoard::ABoard()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABoard::BeginPlay()
{
	Super::BeginPlay();
}

void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

