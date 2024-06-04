#include "Board/Board.h"
#include "Board/BoardSquare.h"
#include "Components/BillboardComponent.h"
#include <Kismet/GameplayStatics.h>

#define STARTLOC FVector(-450.,350.,0.);

constexpr int32 BoardMin = 1;
constexpr int32 BoardMax = 8;

ABoard::ABoard()
{
	PrimaryActorTick.bCanEverTick = false;

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
	for (int32 x=0;x< BoardMax;++x)
	{
		FVector curLoc = STARTLOC;
		curLoc.Y -= x * 100.;
		for (int32 y = 0; y < BoardMax; ++y)
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
				boardSquare->SetSquareColor();
			}
			boardSquare->AttachToComponent(Billboard,
				FAttachmentTransformRules::KeepWorldTransform);
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
		boardSquare->BoardRef = this;
		boardSquare->Initialize();
		int32 index = 0;
		MakeSquareIndex(boardSquare->X, boardSquare->Y, index);
		BoardSquares[index] = boardSquare;
	}
}

void ABoard::HighlightSquare(int32 X, int32 Y)
{
	bool isExist = false;
	SelectedSquare=GetSquare(X,Y, isExist);
	if(isExist)
	{
		SelectedSquare->HightlightMarker();
	}
}

void ABoard::UnhighlightSquares()
{
	for(auto& boardSquare:BoardSquares)
	{
		boardSquare->UnhightlightMarker();
	}
}

void ABoard::GetHightlightedSquares(TArray<ABoardSquare*>& AvailableMoves)
{
	TArray<ABoardSquare*> hightlightedSquares;
	for (auto& boardSquare : BoardSquares)
	{
		if(boardSquare->IsHighlighted)
		{
			hightlightedSquares.Add(boardSquare);
		}
	}
	AvailableMoves = hightlightedSquares;
}

void ABoard::SelectSquare(int32 X, int32 Y)
{
	bool isExist = false;
	ABoardSquare* square= GetSquare(X, Y, isExist);
	if(isExist)
	{
		if (square->IsSquareSelected)
		{
			square->UnselectMarker();
			SelectedSquare = nullptr;
		}
		else
		{
			UnselectAllSquares();
			square->SelectMarker();
			SelectedSquare = square;
		}
	}
}

ABoardSquare* ABoard::GetSelectedSquare(bool& IsExistSquare)
{
	IsExistSquare = IsValid(SelectedSquare);
	return SelectedSquare;
}

void ABoard::UnselectAllSquares()
{
	for (auto& boardSquare : BoardSquares)
	{
		boardSquare->UnselectMarker();
	}
	SelectedSquare = nullptr;
}

ABoardSquare* ABoard::GetSquare(int32 X, int32 Y, bool& IsExistSquare)
{
	IsValidSquare(X,Y, IsExistSquare);
	if(!IsExistSquare)
	{
		return nullptr;
	}
	int32 index = 0;
	MakeSquareIndex(X, Y, index);
	if (!IsValid(BoardSquares[index]))
	{
		IsExistSquare = false;
		return nullptr;
	}
	return BoardSquares[index];
}

void ABoard::GetSquareLocation(int32 X, int32 Y, FVector& SquareLocation, bool& IsExistSquare)
{
	ABoardSquare* square= GetSquare(X,Y, IsExistSquare);
	if(IsExistSquare)
	{
		square->GetLocation(SquareLocation);
	}
}

void ABoard::IsValidSquare(int32 X, int32 Y, bool& IsExistSquare)
{
	IsExistSquare = X >= BoardMin&&X<= BoardMax && Y >= BoardMin && Y <= BoardMax;
}

void ABoard::MakeSquareIndex(int32 X, int32 Y, int32& Index)
{
	Index=(X - 1)* BoardMax+ (Y - 1);
}

void ABoard::ResetSquares()
{
	ResetAllSquares.Broadcast();
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
