#pragma once
#include "../BattleChess.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Chess.generated.h"

class APC_Chess;
class APlayerPawn;
class ABoard;
class ABoardSquare;
class ADeadSlot;
class AChessPiece;

UCLASS()
class BATTLECHESS_API AGM_Chess : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGM_Chess();
protected:
	virtual void BeginPlay() override;

public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UAudioComponent> BeginPlayAudio;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TArray<AChessPiece*> ChessPiecesRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TArray<ADeadSlot*> DeadPoolRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<APC_Chess> PlayerControllerRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<APlayerPawn> PlayerRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<ABoard> BoardRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<AChessPiece> SelectedPieceRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<AChessPiece> WhiteKingRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<AChessPiece> BlackKingRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<AChessPiece> AttackingPieceRef;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<AChessPiece> BlackRookA;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<AChessPiece> BlackRookB;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<AChessPiece> WhiteRookA;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "References", meta = (MultiLine = "true"))
	TObjectPtr<AChessPiece> WhiteRookB;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	TArray<FMoves> Movements;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GamePlay", meta = (MultiLine = "true"))
	int32 ActivePlayer;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	int32 MoveCount;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game Play", meta = (MultiLine = "true"))
	int32 DeadPoolIndex;

private:
	UFUNCTION()
	void DelayChangeActivePlayer();

public:
	UFUNCTION(BlueprintCallable, Category = "Event")
	void ProcessMove();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetPlayerControllerRef();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetPlayerRef();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBoardRef();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetChessPiecesRef();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetupDeadPoolRefs();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void ProcessChessPiece(AChessPiece* ChessPiece);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetPlayerCamera();
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Player")
	void GetActivePlayer(FChessPlayer& Player);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Player")
	void GetActivePlayerColor(EPlayerColor& ActivePlayerColor);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Player")
	void GetPlayerByColor(EPlayerColor PlayerColor, FChessPlayer& Player);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Player")
	void GetPlayerByIndex(int32 PlayerIndex, FChessPlayer& Player);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Player")
	void ChangeActivePlayer();
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Player")
	void GetActivePlayerMoveCount(int32& ActivePlayerMoveCount);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Player")
	void RotatePlayerCamera(float Axis);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void StartGame(FText PlayerAName, FText PlayerBName, int32 PlayerAIndex, 
		int32 PlayerBIndex);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Game Play")
	void GetMoveCount(int32& Count);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void HasLegalMove(bool& HasLegalMove);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Game Play")
	void GetLatestMove(EPlayerColor& Color, FString& LatestMove);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void ActivateExplosionFX(int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void ActivateTeleportFX(int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void GetActiveChessPiecesByColor(EPlayerColor Color, TArray<AChessPiece*>& ChessPieces);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Game Play")
	void GetGameStatus(bool& IsCheckMate, bool& IsStaleMate);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void PersistMove(AChessPiece* ChessPiece, bool IsCapture, 
		bool IsCastle, bool IsQueenSideCastle);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Game Play")
	void CreateNotation(FMoves MoveData, FString& Notation);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void SaveMoveData(FMoves MoveData);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void AddCheckToLastMoveData();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "GameBoard")
	void SelectChessPiece(AChessPiece* ChessPiece, int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Game Board")
	AChessPiece* GetSelectedChessPiece(bool& IsValidPiece);

	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Square")
	void GetSquareLocation(int32 X, int32 Y, FVector& SquareLocation, bool& IsValidLoc);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void ResetSquares();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void HighlightSquare(int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void UnhighlightSquares();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void SelectSquare(int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Square")
	ABoardSquare* GetSelectedSquare(bool& IsValid);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Square")
	void GetHightlightedSquares(TArray<ABoardSquare*>& HightlightedSquares);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupant")
	void SetOccupant(AChessPiece* ChessPiece, int32 X, int32 Y, bool& IsValidSquare);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupant")
	void RemoveOccupant(int32 X, int32 Y, bool& IsValidSquare);
		/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Occupant")
	AChessPiece* GetOccupant(int32 X, int32 Y, EPlayerColor Color,
		bool& IsOccupied, bool& IsOccupiedByFriend, bool& IsValidSquare);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupant")
	void SetOccupants();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupant")
	void RemoveOccupants();

	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "King Evaluations")
	void IsActiveKingCheckStatus(bool& isActiveKingInCheck);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "King Evaluations")
	void EvaluateCheckStatus(bool& IsInCheck);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "King Evaluations")
	AChessPiece* GetActiveKing();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluateDiagonalSquares(int32 X, int32 Y, EPlayerColor Color,
		bool& IsAttackable);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluateHorizontalSquares(int32 X, int32 Y, EPlayerColor Color,
		bool& IsAttackable);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluateVerticalSquares(int32 X, int32 Y, EPlayerColor Color, 
		bool& IsAttackable);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluateForKnights(int32 X, int32 Y, EPlayerColor Color, 
		bool& IsAttackable);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluateKnightSquare(int32 X, int32 Y, int32 XIncr, int32 YIncr, 
		EPlayerColor Color, bool& IsAttackable);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluateSquareForCheckStatus(int32 X, int32 Y, EPlayerColor Color, 
		bool& IsEmpty, bool& IsCheckable);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluationLoop(int32 X, int32 Y, int32 XInc, int32 YInc, 
		EPlayerColor Color, bool& IsCheckablePath);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Capture")
	void CaptureChessPiece(AChessPiece* ChessPiece);
};
