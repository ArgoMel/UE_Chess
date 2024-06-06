#pragma once
#include "../BattleChess.h"
#include "GameFramework/Actor.h"
#include "BoardSquare.generated.h"

class APC_Chess;
class AGM_Chess;
class AChessPiece;
class ABoard;

UCLASS()
class BATTLECHESS_API ABoardSquare : public AActor
{
	GENERATED_BODY()
public:	
	ABoardSquare();
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UBillboardComponent> Billboard;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UStaticMeshComponent> Marker;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UStaticMeshComponent> Square;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UParticleSystemComponent> ExplodeFX;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UParticleSystemComponent> TeleportFX;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UAudioComponent> Explosion;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<APC_Chess> PlayerControllerRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<AGM_Chess> GameModeRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<AChessPiece> OccupantRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<ABoard> BoardRef;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Setup", meta = (MultiLine = "true"))
	FString Notation;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setup", meta = (MultiLine = "true"))
	EPlayerColor SquareColor;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setup", meta = (MultiLine = "true"))
	int32 X;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setup", meta = (MultiLine = "true"))
	int32 Y;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GamePlay", meta = (MultiLine = "true"))
	bool IsAttackable;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GamePlay", meta = (MultiLine = "true"))
	bool IsSquareSelected;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GamePlay", meta = (MultiLine = "true"))
	bool IsHighlighted;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GamePlay", meta = (MultiLine = "true"))
	bool IsChessPieceSelected;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GamePlay", meta = (MultiLine = "true"))
	bool IsVisible;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GamePlay", meta = (MultiLine = "true"))
	bool IsCastling;

private:
	UFUNCTION()
	void OnBoardSquareClicked(AActor* TouchedActor, FKey ButtonPressed);

public:
	UFUNCTION(BlueprintCallable, Category = "Event")
	void InitEvent();
	UFUNCTION(BlueprintCallable, Category = "Event")
	void ResetSquare();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetPlayerControllerRef();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetGameModeRef();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetSquareColor();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetNotation();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Hightlight")
	void SetMarkerColor();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Hightlight")
	void HightlightMarker();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Hightlight")
	void UnhightlightMarker();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Hightlight")
	void SelectMarker();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Hightlight")
	void UnselectMarker();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Hightlight")
	void ResetMarker();

	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Occupants")
	void HasOccupant(bool& HasOccupant);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupants")
	void SetOccupant(AChessPiece* ChessPiece);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupants")
	void RemoveOccupant();
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Occupants")
	AChessPiece* GetOccupant();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupants")
	void SelectOccupant();

	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "GamePlay")
	void GetLocation(FVector& WorldLocation);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void ActivateExplodeFX();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void ActivateTeleportFX();
};
