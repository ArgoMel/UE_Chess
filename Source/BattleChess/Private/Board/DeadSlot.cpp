#include "Board/DeadSlot.h"

ADeadSlot::ADeadSlot()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADeadSlot::BeginPlay()
{
	Super::BeginPlay();
}

void ADeadSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

