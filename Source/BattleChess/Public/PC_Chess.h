#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Chess.generated.h"

class AGM_Chess;
class UUI_Main;
class UUI_Start;

UCLASS()
class BATTLECHESS_API APC_Chess : public APlayerController
{
	GENERATED_BODY()
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<AGM_Chess> GameModeRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (EditInline = "true", MultiLine = "true"))
	TObjectPtr<UUI_Main> UIMainRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (EditInline = "true", MultiLine = "true"))
	TObjectPtr<UUI_Start> UIStartRef;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GamePlay", meta = (MultiLine = "true"))
	FText Message;

public:
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetGameModeRef();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetMainUI();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetStartUI();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void HideStartUI();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void UpdateMainUI();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void SetPlayerInfoInUI(int32 PlayerIndex);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void SetMessage(FText Msg);
};