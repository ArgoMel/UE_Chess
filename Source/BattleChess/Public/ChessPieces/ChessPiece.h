#pragma once
#include "../BattleChess.h"
#include "GameFramework/Actor.h"
#include "ChessPieces/ChessPieceInterface.h"
#include "ChessPiece.generated.h"

class UTimelineComponent;
class AGM_Chess;
class APC_Chess;
class ABoardSquare;

UCLASS()
class BATTLECHESS_API AChessPiece : public AActor
	,public IChessPieceInterface
{
	GENERATED_BODY()
public:	
	AChessPiece();
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Timeline")
	TObjectPtr<UCurveFloat> NewLocAlphaCurve;
	FVector mNewLoc;

public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UBillboardComponent> Billboard;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UStaticMeshComponent> ChessPiece;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UAudioComponent> SlideAudio;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UAudioComponent> TeleportAudio;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UAudioComponent> ButtonClickAudio;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UTimelineComponent> ChessPieceMovement;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Setup", meta = (MultiLine = "true"))
	FString Notation;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setup", meta = (MultiLine = "true"))
	EPlayerColor Color;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setup", meta = (MultiLine = "true"))
	int32 InitialX;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setup", meta = (MultiLine = "true"))
	int32 InitialY;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Setup", meta = (MultiLine = "true"))
	bool IsKing;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Setup", meta = (MultiLine = "true"))
	bool IsTeleportable;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GamePlay", meta = (MultiLine = "true"))
	int32 X;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GamePlay", meta = (MultiLine = "true"))
	int32 Y;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	int32 PreviousX;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	int32 PreviousY;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	int32 ChessPieceMoveCount;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	int32 PlayerMoveCount;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	bool IsEnPassant;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	bool IsInitialMove;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	bool IsValidMove;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	bool CanCaptureOpponent;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	bool IsSuccessfulMove;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	bool KingIsCastling;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	bool KingHasCastled;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	bool KindCanCastle;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Reference", meta = (MultiLine = "true"))
	TObjectPtr<AGM_Chess> GameModeRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Reference", meta = (MultiLine = "true"))
	TObjectPtr<APC_Chess> PlayerControllerRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Reference", meta = (MultiLine = "true"))
	TObjectPtr<AChessPiece> OpponentRef;

private:
	UFUNCTION()
	void OnChessPieceClicked(AActor* TouchedActor, FKey ButtonPressed);
	UFUNCTION()
	void UpdateNewLocAlpha(float Alpha);

public:
	UFUNCTION(BlueprintCallable, Category = "Event")
	void MoveChessPiece(FVector NewLoc);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void MoveToDefault();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetChessPieceColor();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetPlayerControllerRef();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetGameModeRef();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SelectChessPiece();
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "GamePlay")
	void IsPlayerPiece(bool& IsPlayerPiece);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessMovement(bool& Success);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessTemporaryMove();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessOpponentToCapture(bool& CanCapture, int32 TempX, int32 TempY);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessKingCheckStatus(bool& IsValid);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessMove(bool& Success);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessCastle(bool& Success);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessTeleport(bool& Success);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessPostMove();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessPostCastle(bool HasCastled);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessOpponentCapture();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessMovementReset();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessCastleReset();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ProcessVirtualMovement(int32 InX, int32 InY, EPlayerColor InColor);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void HighlightLoopSequence(int32 InX, int32 InY, EPlayerColor InColor, int32 XIncr, int32 YIncr,
		EPlayerColor TempColor, int32 TempX, int32 TempY, bool CanContinue);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void HighlightHorizontalSquares(EPlayerColor InColor, EPlayerColor TempColor, int32 TempX, int32 TempY);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void HighlightVerticalSquares(EPlayerColor InColor, EPlayerColor TempColor, int32 TempX, int32 TempY);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void HighlightDiagonalSquares(EPlayerColor InColor, EPlayerColor TempColor, int32 TempX, int32 TempY);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void HighlightPotentialSquare(int32 InX, int32 InY, EPlayerColor InColor, bool& CanContinueLoop);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Square")
	void CanHighlightSquare(int32 InX, int32 InY, EPlayerColor InColor, bool& CanHightlightSquare,
		bool& IsEmptySquare);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void HasLegalMove(bool& HasLegalMove);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void IsLegalMove(int32 InX, int32 InY, bool& IsLegalMove);
};
