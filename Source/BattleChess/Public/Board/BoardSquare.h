#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardSquare.generated.h"

UCLASS()
class BATTLECHESS_API ABoardSquare : public AActor
{
	GENERATED_BODY()
public:	
	ABoardSquare();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
