#include "PC_Input.h"
#include "../BattleChess.h"
#include "EnhancedInputSubsystems.h"

APC_Input::APC_Input()
{
	GetObjectAsset(mChessInputAction, UChessInput, "/Game/BattleChess/Input/DA_ChessInputAction.DA_ChessInputAction");
}

void APC_Input::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputLocalPlayerSubsystem* inputSubSystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(inputSubSystem))
	{
		return;
	}
	inputSubSystem->ClearAllMappings();
	SetInput(mChessInputAction->mDefaultMappingContext);
}

void APC_Input::AddInputMapping(const UInputMappingContext* InputMapping, 
	const int32 MappingPriority) const
{
	UEnhancedInputLocalPlayerSubsystem* inputSubSystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(inputSubSystem))
	{
		return;
	}
	ensure(InputMapping);
	if (!inputSubSystem->HasMappingContext(InputMapping))
	{
		inputSubSystem->AddMappingContext(InputMapping, MappingPriority);
	}
}

void APC_Input::RemoveInputMapping(const UInputMappingContext* InputMapping) const
{
	UEnhancedInputLocalPlayerSubsystem* inputSubSystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(inputSubSystem))
	{
		return;
	}
	ensure(InputMapping);
	inputSubSystem->RemoveMappingContext(InputMapping);
}

void APC_Input::SetInput(const UInputMappingContext* InputMapping, 
	const bool Enabled) const
{
	ensureMsgf(mChessInputAction, TEXT("mChessInputAction is NULL!"));
	ensure(mChessInputAction->mDefaultMappingContext);
	if (Enabled)
	{
		AddInputMapping(mChessInputAction->mDefaultMappingContext, mChessInputAction->mDefaultMapPriority);
	}
	else
	{
		RemoveInputMapping(mChessInputAction->mDefaultMappingContext);
	}
}
