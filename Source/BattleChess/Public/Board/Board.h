#pragma once
#include "../BattleChess.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

class ABoardSquare;
class AChessPiece;

UCLASS()
class BATTLECHESS_API ABoard : public AActor
{
	GENERATED_BODY()	
public:	
	ABoard();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UBillboardComponent> Billboard;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UStaticMeshComponent> Board;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Reference", meta = (MultiLine = "true"))
	TArray<ABoardSquare*> BoardSquares;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Reference", meta = (MultiLine = "true"))
	TObjectPtr<ABoardSquare> SelectedSquare;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Setup", meta = (MultiLine = "true"))
	int32 BoardWidth;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Setup", meta = (MultiLine = "true"))
	int32 Min;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Setup", meta = (MultiLine = "true"))
	int32 Max;

	/** Please add a variable description */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResetAllSquares);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category = "Delegate", meta = (MultiLine = "true"))
	FResetAllSquares ResetAllSquares;

public:
	UFUNCTION(CallInEditor, Category = "Editor")
	void CreateBoard();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetSquaresRef();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void HighlightSquare(int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void UnhightlightSquares();
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Square")
	void GetHightlightedSquares(TArray<ABoardSquare*>& AvailableMoves, 
		TArray<ABoardSquare*> HightlightedSquares);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void SelectSquare(int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Square")
	void GetSelectedSquare(bool& IsValid, ABoardSquare*& Square);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void UnselectAllSquares();
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Square")
	void GetSquare(int32 X, int32 Y, ABoardSquare*& Square, bool& IsValid);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void GetSquareLocation(int32 X, int32 Y, FVector& SquareLocation, bool& IsValid);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Square")
	void IsValidSquare(int32 X, int32 Y, bool& IsValidSquare);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Square")
	void MakeSquareIndex(int32 X, int32 Y, int32& Index);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void ResetSquares();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupant")
	void SelectOccupant(int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupant")
	void SetOccupant(AChessPiece* ChessPiece, int32 X, int32 Y, bool& IsValid);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Occupant")
	void GetOccupant(int32 X, int32 Y, EPlayerColor Color, AChessPiece*& Occupant, 
		bool& IsOccupied, bool& IsOccupiedByFriend, bool& IsValidSquare);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupant")
	void RemoveOccupant(int32 X, int32 Y, bool& IsValid);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupant")
	void RemoveAllOccupants();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void ActivateExplosionFX(int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void ActivateTeleportFX(int32 X, int32 Y);
};
