#include "Board/BoardSquare.h"
#include "Board/Board.h"
#include "PC_Chess.h"
#include "GM_Chess.h"
#include "ChessPieces/ChessPiece.h"
#include "Components/BillboardComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include <Kismet/GameplayStatics.h>

ABoardSquare::ABoardSquare()
{
	PrimaryActorTick.bCanEverTick = false;

	SquareColor = EPlayerColor::White;
	X = 0;
	Y = 0;

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
	Marker->SetRelativeLocation(FVector(0., 0., 2.));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MarkerMesh(TEXT(
		"/Engine/BasicShapes/Plane.Plane"));
	if (MarkerMesh.Succeeded())
	{
		Marker->SetStaticMesh(MarkerMesh.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ML_MarkerHighlight(TEXT(
		"/Game/BattleChess/Materials/MI_MarkerHighlight.MI_MarkerHighlight"));
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

	ExplodeFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplodeFX"));
	ExplodeFX->SetupAttachment(Billboard);
	ExplodeFX->bAutoActivate=false;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_Skill_Telecharge_Shock_Impact_02(TEXT(
		"/Game/InfinityBladeEffects/Effects/FX_Skill_TeleCharge/P_Skill_Telecharge_Shock_Impact_02.P_Skill_Telecharge_Shock_Impact_02"));
	if (P_Skill_Telecharge_Shock_Impact_02.Succeeded())
	{
		ExplodeFX->SetTemplate(P_Skill_Telecharge_Shock_Impact_02.Object);
	}

	TeleportFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TeleportFX"));
	TeleportFX->SetupAttachment(Billboard);
	TeleportFX->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_Whirlwind_Lightning_Start_01(TEXT(
		"/Game/InfinityBladeEffects/Effects/FX_Skill_Whirlwind/P_Whirlwind_Lightning_Start_01.P_Whirlwind_Lightning_Start_01"));
	if (P_Whirlwind_Lightning_Start_01.Succeeded())
	{
		TeleportFX->SetTemplate(P_Whirlwind_Lightning_Start_01.Object);
	}

	Explosion = CreateDefaultSubobject<UAudioComponent>(TEXT("Explosion"));
	Explosion->SetupAttachment(Billboard);
	Explosion->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> Explosion01(TEXT(
		"/Game/StarterContent/Audio/Explosion01.Explosion01"));
	if (Explosion01.Succeeded())
	{
		Explosion->SetSound(Explosion01.Object);
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
	OnClicked.AddDynamic(this, &ThisClass::OnBoardSquareClicked);
}

void ABoardSquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoardSquare::OnBoardSquareClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	GameModeRef->SelectSquare(X,Y);
}

void ABoardSquare::InitEvent()
{
	if(!IsValid(BoardRef))
	{
		return;
	}
	BoardRef->ResetAllSquares.AddDynamic(this,&ThisClass::ResetSquare);
}

void ABoardSquare::ResetSquare()
{
	ResetMarker();
}

void ABoardSquare::Initialize()
{
	SetPlayerControllerRef();
	SetGameModeRef();
	SetNotation();
	InitEvent();
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
	if(!IsValid(Square))
	{
		return;
	}
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

void ABoardSquare::SetMarkerColor()
{
	if(IsHighlighted)
	{
		IsVisible = true;
		if (IsSquareSelected)
		{		
			Marker->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(FLinearColor::Red));
		}
		else if(IsAttackable)
		{
			Marker->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(FLinearColor::Green));
		}
		else
		{
			Marker->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(FLinearColor::Blue));
		}
	}
	else if(IsChessPieceSelected)
	{
		IsVisible = true;
		Marker->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(FColor::Purple.ReinterpretAsLinear()));
	}
	else
	{
		IsVisible = false;
		Marker->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(FLinearColor::Blue));
	}
	Marker->SetVisibility(IsVisible);
}

void ABoardSquare::HightlightMarker()
{
	IsHighlighted = true;
	IsSquareSelected = false;
	IsAttackable = false;
	IsChessPieceSelected = false;

	bool hasOccupant = false;
	HasOccupant(hasOccupant);
	if(hasOccupant)
	{
		IsAttackable = true;
	}
	SetMarkerColor();
}

void ABoardSquare::UnhightlightMarker()
{
	IsHighlighted = false;
	IsSquareSelected = false;
	IsAttackable = false;

	SetMarkerColor();
}

void ABoardSquare::SelectMarker()
{
	if(IsHighlighted)
	{
		IsSquareSelected = true;
		SetMarkerColor();
	}
}

void ABoardSquare::UnselectMarker()
{
	IsSquareSelected = false;
	SetMarkerColor();
}

void ABoardSquare::ResetMarker()
{
	IsHighlighted = false;
	IsSquareSelected = false;
	IsAttackable = false;
	IsVisible = false;
	IsChessPieceSelected = false;

	SetMarkerColor();
}

void ABoardSquare::HasOccupant(bool& HasOccupant)
{
	HasOccupant=IsValid(OccupantRef);
}

void ABoardSquare::SetOccupant(AChessPiece* ChessPiece)
{
	OccupantRef = ChessPiece;
}

void ABoardSquare::RemoveOccupant()
{
	OccupantRef = nullptr;
}

AChessPiece* ABoardSquare::GetOccupant()
{
	return OccupantRef;
}

void ABoardSquare::SelectOccupant()
{
	IsAttackable = false;
	IsHighlighted = false;
	IsSquareSelected = false;

	bool hasOccupant=false;
	HasOccupant(hasOccupant);
	if(hasOccupant)
	{
		IsChessPieceSelected = true;
		SetMarkerColor();
	}
}

void ABoardSquare::GetLocation(FVector& WorldLocation)
{
	WorldLocation = Billboard->GetComponentLocation();
}

void ABoardSquare::ActivateExplodeFX()
{
	ExplodeFX->Activate(true);
	Explosion->Play();
}

void ABoardSquare::ActivateTeleportFX()
{
	TeleportFX->Activate(true);
}
