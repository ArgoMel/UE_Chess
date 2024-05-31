#include "Board/Board.h"
#include "Board/BoardSquare.h"
#include "Components/BillboardComponent.h"
#include <Kismet/GameplayStatics.h>

#define STARTLOC FVector(-450.,350.,0.);

ABoard::ABoard()
{
	PrimaryActorTick.bCanEverTick = false;

	BoardWidth = 8;
	Min = 1;
	Max = 8;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	SetRootComponent(Billboard);
	Billboard->SetVisibility(false);

	Board = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Board"));
	Board->SetupAttachment(Billboard);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Chess_Board_Frame(TEXT(
		"/Game/BattleChess/Assets/SM_Chess_Board_Frame.SM_Chess_Board_Frame"));
	if (SM_Chess_Board_Frame.Succeeded())
	{
		Board->SetStaticMesh(SM_Chess_Board_Frame.Object);
	}
}

void ABoard::BeginPlay()
{
	Super::BeginPlay();
}

void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoard::CreateBoard()
{
	for (int32 x=0;x< BoardWidth;++x)
	{
		FVector curLoc = STARTLOC;
		curLoc.Y -= x * 100.;
		for (int32 y = 0; y < BoardWidth; ++y)
		{
			curLoc.X += 100.;
			FActorSpawnParameters spawnParams;
			spawnParams.bDeferConstruction = true;
			ABoardSquare* boardSquare = 
				GetWorld()->SpawnActor<ABoardSquare>(curLoc, FRotator::ZeroRotator,spawnParams);
			if(!IsValid(boardSquare))
			{
				continue;
			}
			boardSquare->X = x + 1;
			boardSquare->Y = y+1;
			if((x%2==0&&y%2==0)||
				(x % 2 == 1 && y % 2 == 1))
			{
				boardSquare->SquareColor = EPlayerColor::Black;
			}
		}
	}
}

void ABoard::Initialize()
{
	SetSquaresRef();
}

void ABoard::SetSquaresRef()
{
	if(!BoardSquares.IsEmpty())
	{
		return;
	}
	BoardSquares.Init(nullptr, 64);
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoardSquare::StaticClass(), actors);
	for (auto& actor : actors)
	{
		ABoardSquare* boardSquare = Cast<ABoardSquare>(actor);
		if (!IsValid(boardSquare))
		{
			continue;
		}
		boardSquare->Initialize();
		int32 index = 0;
		MakeSquareIndex(boardSquare->X, boardSquare->Y, index);
		BoardSquares[index] = boardSquare;
	}
}

void ABoard::HighlightSquare(int32 X, int32 Y)
{
}

void ABoard::UnhightlightSquares()
{
}

void ABoard::GetHightlightedSquares(TArray<ABoardSquare*>& AvailableMoves, 
	TArray<ABoardSquare*> HightlightedSquares)
{
}

void ABoard::SelectSquare(int32 X, int32 Y)
{
}

void ABoard::GetSelectedSquare(bool& IsValid, ABoardSquare*& Square)
{
}

void ABoard::UnselectAllSquares()
{
}

void ABoard::GetSquare(int32 X, int32 Y, ABoardSquare*& Square, bool& IsValid)
{
}

void ABoard::GetSquareLocation(int32 X, int32 Y, FVector& SquareLocation, bool& IsValid)
{
}

void ABoard::IsValidSquare(int32 X, int32 Y, bool& IsValidSquare)
{
}

void ABoard::MakeSquareIndex(int32 X, int32 Y, int32& Index)
{
	Index=(X - 1)* BoardWidth+ (Y - 1);
}

void ABoard::ResetSquares()
{
}

void ABoard::SelectOccupant(int32 X, int32 Y)
{
}

void ABoard::SetOccupant(AChessPiece* ChessPiece, int32 X, int32 Y, bool& IsValid)
{
}

void ABoard::GetOccupant(int32 X, int32 Y, EPlayerColor Color, AChessPiece*& Occupant, bool& IsOccupied, bool& IsOccupiedByFriend, bool& IsValidSquare)
{
}

void ABoard::RemoveOccupant(int32 X, int32 Y, bool& IsValid)
{
}

void ABoard::RemoveAllOccupants()
{
}

void ABoard::ActivateExplosionFX(int32 X, int32 Y)
{
}

void ABoard::ActivateTeleportFX(int32 X, int32 Y)
{
}
