#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ChessPieceInterface.generated.h"

UINTERFACE(MinimalAPI)
class UChessPieceInterface : public UInterface
{
	GENERATED_BODY()
};

class BATTLECHESS_API IChessPieceInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ShowPossibleMoves(bool& IsKing);
};
