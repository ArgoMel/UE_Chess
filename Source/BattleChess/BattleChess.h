#pragma once
#include "CoreMinimal.h"
#include "BattleChess.generated.h"

namespace ChessInfo
{
	constexpr int32 MaxPlayer = 2;
}

#pragma region LoadAsset
/*    Object Asset을 받습니다.
*    RETURN_POINTER : 받을 포인터
*    CLASS_TYPE : 받을 오브젝트의 클래스
*    PATH : 경로 (TEXT를 붙이지 않습니다.)*/
#define GetObjectAsset(RETURN_POINTER, CLASS_TYPE, PATH)\
static ConstructorHelpers::FObjectFinder<CLASS_TYPE> __##RETURN_POINTER(TEXT(PATH));\
if (__##RETURN_POINTER.Succeeded()) \
{\
    RETURN_POINTER = __##RETURN_POINTER.Object;\
}\
else \
{\
	UE_LOG(LogTemp,Warning,TEXT("Failed GetObjectAsset : %d"),TEXT(PATH));\
	RETURN_POINTER = nullptr;\
}

#define AddObjectAsset(RETURN_POINTER, CLASS_TYPE, PATH)\
{\
	static ConstructorHelpers::FObjectFinder<CLASS_TYPE> __##RETURN_POINTER(TEXT(PATH));\
	if (__##RETURN_POINTER.Succeeded()) \
	{\
	    RETURN_POINTER.Add(__##RETURN_POINTER.Object);\
	}\
	else \
	{\
		UE_LOG(LogTemp,Warning,TEXT("Failed GetObjectAsset : %d"),TEXT(PATH));\
		RETURN_POINTER.Add(nullptr);\
	}\
}

/*    Class Asset을 받습니다.
*    RETURN_POINTER : 받을 포인터
*    CLASS_TYPE : 받을 클래스 타입
*    PATH : 경로 (TEXT를 붙이지 않습니다.)*/
#define GetClassAsset(RETURN_POINTER, CLASS_TYPE, PATH)\
static ConstructorHelpers::FClassFinder<CLASS_TYPE> __##RETURN_POINTER(TEXT(PATH));\
if (__##RETURN_POINTER.Succeeded()) \
{\
    RETURN_POINTER = __##RETURN_POINTER.Class;\
}\
else \
{\
	UE_LOG(LogTemp,Warning,TEXT("Failed GetClassAsset : %d"),TEXT(PATH));\
	RETURN_POINTER = nullptr;\
}
#pragma endregion

UENUM(BlueprintType)
enum class EPlayerColor : uint8
{
	White /*UMETA(DisplayName = "TestHit")*/,
	Black,
	Max UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FMoves
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ChessPiece;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString PreviousSquare;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString NewSquare;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPlayerColor Color;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MoveCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsCapture;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsCheck;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsCheckMate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsStaleMate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsKingSideCastle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsQueenSideCastle;

	FMoves()
	{
		Color = EPlayerColor::White;
		MoveCount = 0;
		IsCapture = false;
		IsCheck = false;
		IsCheckMate = false;
		IsStaleMate = false;
		IsKingSideCastle = false;
		IsQueenSideCastle = false;
	}
};

USTRUCT(BlueprintType)
struct FChessPlayer
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPlayerColor Color;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Index;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MoveCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Captures;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsInCheckFlag;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool HasLegalMoves;

	FChessPlayer()
	{
		Color = EPlayerColor::White;
		Index = 0;
		MoveCount = 0;
		Captures = 0;
		IsInCheckFlag = false;
		HasLegalMoves = true;
	}
};