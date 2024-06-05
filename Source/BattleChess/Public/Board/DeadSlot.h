#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeadSlot.generated.h"

UCLASS()
class BATTLECHESS_API ADeadSlot : public AActor
{
	GENERATED_BODY()
public:	
	ADeadSlot();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UBillboardComponent> Billboard;
};
