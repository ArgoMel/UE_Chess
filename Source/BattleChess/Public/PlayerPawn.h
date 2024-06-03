#pragma once
#include "../BattleChess.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;

UCLASS()
class BATTLECHESS_API APlayerPawn : public APawn
{
	GENERATED_BODY()
public:
	APlayerPawn();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	EPlayerColor mPlayerColor;

public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UBillboardComponent> Root;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UBillboardComponent> White;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UBillboardComponent> Black;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UBillboardComponent> CameraAzimuth;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UCameraComponent> Camera;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "µðÆúÆ®", meta = (MultiLine = "true"))
	TArray<FChessPlayer> Players;

private:
	UFUNCTION()
	void SetPlayerCameraFinish();

public:
	UFUNCTION(BlueprintCallable, Category = "Event")
	void SetPlayerCamera(EPlayerColor Color);

	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "GamePlay")
	void GetPlayerByIndex(int32 PlayerIndex, FChessPlayer& Player);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "GamePlay")
	void GetPlayerByColor(EPlayerColor PlayerColor, FChessPlayer& Player);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SetPlayerColor(int32 PlayerIndex, EPlayerColor PlayerColor);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SetPlayerName(int32 PlayerIndex, FString PlayerName);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void IncrementPlayerMoveCount(int32 PlayerIndex);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void IncrementPlayerCaptureCount(int32 PlayerIndex);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void SetKingInCheckFlag(int32 PlayerIndex, bool IsInCheck);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void SetHasLegalMovesFlag(int32 PlayerIndex, bool HasLegalMoves);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void RotateCamera(float Axis);
};
