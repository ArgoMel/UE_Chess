#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

UCLASS()
class BATTLECHESS_API AChessPiece : public AActor
{
	GENERATED_BODY()
public:	
	AChessPiece();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
