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
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UAudioComponent> BeginPlay;

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

public:
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
	void ProcessChessPiece(AChessPiece* ChessPiece, AChessPiece* TempChessPiece);

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
	void RotatePlayerCamera(double Axis);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void StartGame(FText PlayerAName, FText PlayerBName, int32 PlayerAIndex, int32 PlayerBIndex);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Game Play")
	void GetMoveCount(int32& Count);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void HasLegalMove(bool& HasLegalMove);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Game Play")
	void GetLatestMove(EPlayerColor& Color, FText& LatestMove);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void ActivateExplosionFX(int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void ActivateTeleport(int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void GetActiveChessPiecesByColor(EPlayerColor Color, TArray<AChessPiece*>& ChessPieces,
		TArray<AChessPiece*> ActiveChessPieces);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Game Play")
	void GetGameStatus(bool& IsCheckMate, bool& IsStaleMate, FChessPlayer TempActivePlayer);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void PersistMove(AChessPiece* ChessPiece, bool IsCapture, bool IsCastle,
		bool IsQueenSideCastle, FString ChessPieceNotation, FString CaptureNotation,
		FString SquareNotation, FString CheckNotation, FString FinalNotation,
		bool bIsCapture, bool bIsCastle, bool bIsQueenSideCastle, bool bIsInCheck,
		AChessPiece* lChessPiece);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Game Play")
	void CreateNotation(FMoves MoveData, FString& Notation, FString MoveNotation,
		FString ChessPiece, FString Square, bool bIsCheck, bool bIsCapture,
		bool bIsKingsideCastle, bool bIsQueensideCastle);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void SaveMoveData(int32 Count, EPlayerColor Color, FString ChessPieceNotation,
		FString PreviousSquare, FString NewSquare, bool IsCapture, bool IsKingsideCastle,
		bool IsQueenSideCastle);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Game Play")
	void AddCheckToLastMoveData();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "GameBoard")
	void SelectChessPiece(AChessPiece* ChessPiece, int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Game Board")
	void GetSelectedChessPiece(AChessPiece*& SelectedChessPiece, bool& IsValid);

	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Square")
	void GetSquareLocation(int32 X, int32 Y, FVector& SquareLocation, bool& IsValid);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void ResetSquares();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void HighllightSquare(int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void UnhighlightSquares();
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Square")
	void SelectSquare(int32 X, int32 Y);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Square")
	void GetSelectedSquare(ABoardSquare*& SelectedSquare, bool& IsValid);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Square")
	void GetHightlightedSquares(TArray<ABoardSquare*>& HightlightedSquares);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupant")
	void SetOccupant(AChessPiece* ChessPiece, int32 X, int32 Y, bool& IsValid);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Occupant")
	void RemoveOccupant(int32 X, int32 Y, bool& IsValid);
		/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "Occupant")
	void GetOccupant(int32 X, int32 Y, EPlayerColor Color, AChessPiece*& Occupant,
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
	void EvaluateCheckStatus(bool& IsInCheck, int32 TempX, int32 TempY, EPlayerColor TempColor);
	/** Please add a function description */
	UFUNCTION(BlueprintPure, Category = "King Evaluations")
	void GetActiveKing(AChessPiece*& ActiveKing);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluateDiagonalSquares(int32 X, int32 Y, EPlayerColor Color,
		bool& IsAttackable, int32 TempX, int32 TempY, EPlayerColor TempColor);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluateHorizontalSquares(int32 X, int32 Y, EPlayerColor Color,
		bool& IsAttackable, int32 TempX, int32 TempY, EPlayerColor TempColor);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluateVerticalSquares(int32 X, int32 Y, EPlayerColor Color, 
		bool& IsAttackable, int32 TempX, int32 TempY, EPlayerColor TempColor);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluateForKnights(int32 X, int32 Y, EPlayerColor Color, bool& IsAttackable, 
		int32 TempX, int32 TempY, EPlayerColor TempColor);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluateKnightSquare(int32 X, int32 Y, int32 XIncr, int32 YIncr, EPlayerColor Color, 
		bool& IsAttackable, int32 TempX, int32 TempY, EPlayerColor TempColor);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvalScquareForCheckStatus(int32 X, int32 Y, EPlayerColor Color, bool& IsEmpty, 
		bool& IsCheckable, int32 TempX, int32 TempY, EPlayerColor TempColor, bool IsInCheck);
	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "King Evaluations")
	void EvaluationLoop(int32 X, int32 Y, int32 XInc, int32 YInc, EPlayerColor Color, 
		bool& IsCheckablePath, int32 TempX, int32 TempY, bool CanContinue, bool IsCheckable);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable, Category = "Capture")
	void CaptureChessPiece(AChessPiece* ChessPiece);
};
