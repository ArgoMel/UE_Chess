#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Start.generated.h"

class UButton;
class UEditableText;

UCLASS(Abstract)
class BATTLECHESS_API UUI_Start : public UUserWidget
{
	GENERATED_BODY()
public:
	UUI_Start(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> StartButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UEditableText> Player1Name;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UEditableText> Player2Name;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> FadeOut;

protected:
	UFUNCTION()
	void OnStartButtonClicked();
	UFUNCTION()
	void StartGame();
};
