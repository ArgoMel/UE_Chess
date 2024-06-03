#include "PlayerPawn.h"
#include "Components/BillboardComponent.h"
#include "Camera/CameraComponent.h"
#include <Kismet/KismetSystemLibrary.h>

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	mPlayerColor = EPlayerColor::White;

	for (int32 i = 0; i < (int32)EPlayerColor::Max;++i) 
	{
		FChessPlayer player;
		player.Name = FString::Printf(TEXT("플레이어%d"),i);
		player.Color = (EPlayerColor)i;
		player.Index = i;
		Players.Add(player);
	}

	Root = CreateDefaultSubobject<UBillboardComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Root->SetVisibility(false);

	White = CreateDefaultSubobject<UBillboardComponent>(TEXT("White"));
	White->SetupAttachment(Root);
	White->SetVisibility(false);
	White->SetRelativeLocation(FVector(0., 751., -530.));
	White->SetRelativeRotation(FRotator(-30.,-90.,0.));

	Black = CreateDefaultSubobject<UBillboardComponent>(TEXT("Black"));
	Black->SetupAttachment(Root);
	Black->SetVisibility(false);
	Black->SetRelativeLocation(FVector(0., -751., -530.));
	Black->SetRelativeRotation(FRotator(-30., 90., 0.));

	CameraAzimuth = CreateDefaultSubobject<UBillboardComponent>(TEXT("CameraAzimuth"));
	CameraAzimuth->SetupAttachment(Root);
	CameraAzimuth->SetVisibility(false);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraAzimuth);
	Camera->SetRelativeRotation(FRotator(-90., 180., 0.));
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn::SetPlayerCameraFinish()
{
	FTransform newTransform;
	switch (mPlayerColor)
	{
	case EPlayerColor::White:
		newTransform=White->GetRelativeTransform();
		break;
	case EPlayerColor::Black:
		newTransform = Black->GetRelativeTransform();
		break;
	}
	FLatentActionInfo latentActionInfo(INDEX_NONE, 0,nullptr, this);
	UKismetSystemLibrary::MoveComponentTo(Camera, newTransform.GetLocation(), newTransform.Rotator(),
		true, true, 3.f, true, EMoveComponentAction::Move, latentActionInfo);
}

void APlayerPawn::SetPlayerCamera(EPlayerColor Color)
{
	mPlayerColor = Color;
	FLatentActionInfo latentActionInfo(0, 0, TEXT("SetPlayerCameraFinish"), this);
	UKismetSystemLibrary::MoveComponentTo(CameraAzimuth,FVector::ZeroVector,FRotator::ZeroRotator,
		true,true,1.f,true, EMoveComponentAction::Move, latentActionInfo);
}

void APlayerPawn::GetPlayerByIndex(int32 PlayerIndex, FChessPlayer& Player)
{
	if(PlayerIndex<0|| PlayerIndex>= Players.Num())
	{
		return;
	}
	Player = Players[PlayerIndex];
}

void APlayerPawn::GetPlayerByColor(EPlayerColor PlayerColor, FChessPlayer& Player)
{
	GetPlayerByIndex((int32)PlayerColor, Player);
}

void APlayerPawn::SetPlayerColor(int32 PlayerIndex, EPlayerColor PlayerColor)
{
	if (PlayerIndex < 0 || PlayerIndex >= Players.Num())
	{
		return;
	}
	Players[PlayerIndex].Color = PlayerColor;
}

void APlayerPawn::SetPlayerName(int32 PlayerIndex, FString PlayerName)
{
	if (PlayerIndex < 0 || PlayerIndex >= Players.Num())
	{
		return;
	}
	Players[PlayerIndex].Name = PlayerName;
}

void APlayerPawn::IncrementPlayerMoveCount(int32 PlayerIndex)
{
	if (PlayerIndex < 0 || PlayerIndex >= Players.Num())
	{
		return;
	}
	++Players[PlayerIndex].MoveCount;
}

void APlayerPawn::IncrementPlayerCaptureCount(int32 PlayerIndex)
{
	if (PlayerIndex < 0 || PlayerIndex >= Players.Num())
	{
		return;
	}
	++Players[PlayerIndex].Captures;
}

void APlayerPawn::SetKingInCheckFlag(int32 PlayerIndex, bool IsInCheck)
{
	if (PlayerIndex < 0 || PlayerIndex >= Players.Num())
	{
		return;
	}
	Players[PlayerIndex].IsInCheckFlag = IsInCheck;
}

void APlayerPawn::SetHasLegalMovesFlag(int32 PlayerIndex, bool HasLegalMoves)
{
	if (PlayerIndex < 0 || PlayerIndex >= Players.Num())
	{
		return;
	}
	Players[PlayerIndex].HasLegalMoves = HasLegalMoves;
}

void APlayerPawn::RotateCamera(float Axis)
{
	if(Axis==0)
	{
		return;
	}
	CameraAzimuth->AddRelativeRotation(FRotator(0., Axis,0.));
}
