#include "Board/Board.h"
#include "Components/BillboardComponent.h"

ABoard::ABoard()
{
	PrimaryActorTick.bCanEverTick = false;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	SetRootComponent(Billboard);
	Billboard->SetVisibility(false);
}

void ABoard::BeginPlay()
{
	Super::BeginPlay();
}

void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoard::Initialize()
{
}

void ABoard::SetSquaresRef()
{
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
