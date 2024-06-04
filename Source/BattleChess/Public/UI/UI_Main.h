#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Main.generated.h"

class UBorder;
class UTextBlock;

UCLASS(Abstract)
class BATTLECHESS_API UUI_Main : public UUserWidget
{
	GENERATED_BODY()
public:
	UUI_Main(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> MoveCountValue;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Message;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Message2;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBorder> WhiteMarker;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> WhiteName;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> WhiteMove;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> WhiteCaptureCount;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> WhiteStatus;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBorder> BlackMarker;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> BlackName;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> BlackMove;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> BlackCaptureCount;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> BlackStatus;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> FadeIn;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> CompileFailedSound;

public:
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void OpenUI();
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SetMoveCount(int32 MoveCount);
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SetMessage(FString Text);
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SetMessage2(FString Text);
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SetActivePlayer(EPlayerColor PlayerColor);
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SetPlayerName(EPlayerColor PlayerColor, FString PlayerName);
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SetLatestMove(EPlayerColor PlayerColor, FString MoveNotation);
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SetCheckWhiteCaptureCount(int32 CaptureCount);
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SetCheckBlackCaptureCount(int32 CaptureCount);
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SetCheckStatus(EPlayerColor PlayerColor, bool IsInCheck);
};
