#pragma once
#include "CoreMinimal.h"
#include "Input/ChessInput.h"
#include "GameFramework/PlayerController.h"
#include "PC_Input.generated.h"

UCLASS()
class BATTLECHESS_API APC_Input : public APlayerController
{
	GENERATED_BODY()
public:
	APC_Input();
protected:
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UChessInput> mChessInputAction;

private:
	UFUNCTION()
	void AddInputMapping(const UInputMappingContext* InputMapping, const int32 MappingPriority = 0) const;
	UFUNCTION()
	void RemoveInputMapping(const UInputMappingContext* InputMapping) const;

public:
	UFUNCTION()
	void SetInput(const UInputMappingContext* InputMapping, const bool Enabled = true) const;

	UFUNCTION()
	UChessInput* GetChessInputAction() const
	{
		return mChessInputAction;
	}
};
