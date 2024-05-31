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

public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UCameraComponent> Camera;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UBillboardComponent> CameraAzimuth;
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
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "디폴트", meta = (MultiLine = "true"))
	FChessPlayer Player0;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "디폴트", meta = (MultiLine = "true"))
	FChessPlayer Player1;

public:
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "GamePlay")
	void GetPlayerByIndex(int32 PlayerIndex, FChessPlayer& Player);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "GamePlay")
	void GetPlayerByColor(EPlayerColor PlayerColor, FChessPlayer& Player, 
		FChessPlayer PlayerA, FChessPlayer PlayerB);
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
	void RotateCamera(double Axis);
};
