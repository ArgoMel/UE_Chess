#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

UCLASS()
class BATTLECHESS_API ABoard : public AActor
{
	GENERATED_BODY()	
public:	
	ABoard();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
