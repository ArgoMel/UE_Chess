#include "Board/BoardSquare.h"
#include "PC_Chess.h"
#include "GM_Chess.h"
#include "Components/BillboardComponent.h"
#include <Kismet/GameplayStatics.h>

ABoardSquare::ABoardSquare()
{
	PrimaryActorTick.bCanEverTick = false;

	SquareColor = EPlayerColor::White;
	X = 0;
	Y = 0;

	GetObjectAsset(HighlightMaterial, UMaterialInterface,"/Game/BattleChess/Materials/ML_MarkerHighlight.ML_MarkerHighlight");
	GetObjectAsset(AttackMaterial, UMaterialInterface,"/Game/BattleChess/Materials/ML_MarkerAttack.ML_MarkerAttack");
	GetObjectAsset(SelectMaterial, UMaterialInterface,"/Game/BattleChess/Materials/ML_MarkerSelect.ML_MarkerSelect");
	GetObjectAsset(ChessPieceMaterial, UMaterialInterface,"/Game/BattleChess/Materials/MI_MarkerChessPiece.MI_MarkerChessPiece");
	GetObjectAsset(ActiveMaterial, UMaterialInterface,"/Game/BattleChess/Materials/MI_MarkerChessPiece.MI_MarkerChessPiece");
	IsAttackable = false;
	IsSquareSelected = false;
	IsHighlighted = false;
	IsChessPieceSelected = false;
	IsVisible = false;
	IsCastling = false;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	SetRootComponent(Billboard);
	Billboard->SetVisibility(false);

	Marker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Marker"));
	Marker->SetupAttachment(Billboard);
	Marker->SetVisibility(false);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MarkerMesh(TEXT(
		"/Engine/BasicShapes/Plane.Plane"));
	if (MarkerMesh.Succeeded())
	{
		Marker->SetStaticMesh(MarkerMesh.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ML_MarkerHighlight(TEXT(
		"/Game/BattleChess/Materials/ML_MarkerHighlight.ML_MarkerHighlight"));
	if (ML_MarkerHighlight.Succeeded())
	{
		Marker->SetMaterial(0, ML_MarkerHighlight.Object);
	}

	Square = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Square"));
	Square->SetupAttachment(Billboard);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_ChessBoardSquare(TEXT(
		"/Game/BattleChess/Assets/SM_ChessBoardSquare.SM_ChessBoardSquare"));
	if (SM_ChessBoardSquare.Succeeded())
	{
		Square->SetStaticMesh(SM_ChessBoardSquare.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MI_WhiteSquare(TEXT(
		"/Game/BattleChess/Materials/MI_WhiteSquare.MI_WhiteSquare"));
	if (MI_WhiteSquare.Succeeded())
	{
		Square->SetMaterial(0, MI_WhiteSquare.Object);
	}
}

void ABoardSquare::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetSquareColor();
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
	SetPlayerControllerRef();
	SetGameModeRef();
	SetNotation();
}

void ABoardSquare::SetPlayerControllerRef()
{
	if(IsValid(PlayerControllerRef))
	{
		return;
	}
	PlayerControllerRef = Cast<APC_Chess>(UGameplayStatics::GetPlayerController(GetWorld(),0));
}

void ABoardSquare::SetGameModeRef()
{
	if (IsValid(GameModeRef))
	{
		return;
	}
	GameModeRef = Cast<AGM_Chess>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ABoardSquare::SetSquareColor()
{
	FLinearColor color;
	switch (SquareColor)
	{
	case EPlayerColor::White:
		color = FLinearColor(0.621071, 0.677083, 0.497268);
		break;
	case EPlayerColor::Black:
		color = FLinearColor(0.008928, 0.010417, 0.004991);
		break;
	}
	Square->SetVectorParameterValueOnMaterials(TEXT("BaseColor"), FVector(color));
}

void ABoardSquare::SetNotation()
{
	Notation = FString::Chr(Y + 65)+FString::FormatAsNumber(X);
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
	WorldLocation = Billboard->GetComponentLocation();
}

void ABoardSquare::ActivateExplodeFX()
{
}

void ABoardSquare::ActivateTeleportFX()
{
}
