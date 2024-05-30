#include "Board/BoardSquare.h"

ABoardSquare::ABoardSquare()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABoardSquare::BeginPlay()
{
	Super::BeginPlay();
}

void ABoardSquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

