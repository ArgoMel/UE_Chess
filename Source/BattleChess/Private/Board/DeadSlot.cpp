#include "Board/DeadSlot.h"
#include "Components/BillboardComponent.h"

ADeadSlot::ADeadSlot()
{
	PrimaryActorTick.bCanEverTick = false;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	SetRootComponent(Billboard);
}

void ADeadSlot::BeginPlay()
{
	Super::BeginPlay();
}

void ADeadSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

