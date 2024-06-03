#include "PC_Chess.h"
#include "GM_Chess.h"
#include <Kismet/GameplayStatics.h>

APC_Chess::APC_Chess()
{
}

void APC_Chess::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(input))
	{
		return;
	}
	EChessInputAction::BindInput_StartOnly(input, mChessInputAction->mMoveChessPiece, this, &ThisClass::MoveChessPieceStarted);
	EChessInputAction::BindInput_TriggerOnly(input, mChessInputAction->mCameraRotation, this, &ThisClass::CameraRotationTriggered);
}

void APC_Chess::MoveChessPieceStarted()
{
	GameModeRef->ProcessMove();
}

void APC_Chess::CameraRotationTriggered(const FInputActionValue& Value)
{
	GameModeRef->RotatePlayerCamera(Value.Get<float>());
}

void APC_Chess::Initialize()
{
	SetGameModeRef();
}

void APC_Chess::SetGameModeRef()
{
	if (IsValid(GameModeRef))
	{
		return;
	}
	GameModeRef = Cast<AGM_Chess>(UGameplayStatics::GetGameMode(GetWorld()));
}

void APC_Chess::SetMainUI()
{
}

void APC_Chess::SetStartUI()
{
}

void APC_Chess::HideStartUI()
{
}

void APC_Chess::UpdateMainUI()
{
}

void APC_Chess::SetPlayerInfoInUI(int32 PlayerIndex)
{
}

void APC_Chess::SetMessage(FText Msg)
{
}
