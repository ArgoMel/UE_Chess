#include "Board/BoardSquare.h"

ABoardSquare::ABoardSquare()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABoardSquare::BeginPlay()
{
	Super::BeginPlay();
}

void ABoardSquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoardSquare::Initialize()
{
}

void ABoardSquare::SetPlayerControllerRef()
{
}

void ABoardSquare::SetGameModeRef()
{
}

void ABoardSquare::SetSquareColor()
{
}

void ABoardSquare::SetNotation()
{
}

void ABoardSquare::SetYValue(int32 Selection, FString& YValue)
{
}

void ABoardSquare::SetMarkerColor()
{
}

void ABoardSquare::HightlightMarker()
{
}

void ABoardSquare::UnhightlightMarker()
{
}

void ABoardSquare::SelectMarker()
{
}

void ABoardSquare::UnselectMarker()
{
}

void ABoardSquare::ResetMarker()
{
}

void ABoardSquare::HasOccupant(bool& HasOccupant)
{
}

void ABoardSquare::SetOccupant(AChessPiece* ChessPiece)
{
}

void ABoardSquare::RemoveOccupant()
{
}

void ABoardSquare::GetOccupant(AChessPiece*& Occupant)
{
}

void ABoardSquare::SelectOccupant()
{
}

void ABoardSquare::GetLocation(FVector& WorldLocation)
{
}

void ABoardSquare::ActivateExplodeFX()
{
}

void ABoardSquare::ActivateTeleportFX()
{
}
