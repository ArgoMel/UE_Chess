#include "PC_Chess.h"
#include "GM_Chess.h"
#include "UI/UI_Main.h"
#include "UI/UI_Start.h"
#include "../BattleChess.h"
#include <Kismet/GameplayStatics.h>

APC_Chess::APC_Chess()
{
	GetClassAsset(UIMainClass, UUserWidget, "/Game/BattleChess/UI/WP_Main.WP_Main_C");
	GetClassAsset(UIStartClass, UUserWidget, "/Game/BattleChess/UI/WP_Start.WP_Start_C");
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
	if (IsValid(UIMainRef))
	{
		return;
	}
	if (!IsValid(UIMainClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("APC_Chess::UIMainClass 클래스 없음"));
		return;
	}
	UIMainRef = CreateWidget<UUI_Main>(this, UIMainClass);
	if (!IsValid(UIMainRef))
	{
		UE_LOG(LogTemp, Warning, TEXT("APC_Chess::UIMainRef 생성 실패"));
		return;
	}
	UIMainRef->AddToViewport();
	UIMainRef->OpenUI();
	UpdateMainUI();
}

void APC_Chess::SetStartUI()
{
	if (IsValid(UIStartRef))
	{
		return;
	}
	if (!IsValid(UIStartClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("APC_Chess::UIStartClass 클래스 없음"));
		return;
	}
	UIStartRef = CreateWidget<UUI_Start>(this, UIStartClass);
	if (!IsValid(UIStartRef))
	{
		UE_LOG(LogTemp, Warning, TEXT("APC_Chess::UIStartRef 생성 실패"));
		return;
	}
	UIStartRef->AddToViewport();
}

void APC_Chess::HideStartUI()
{
}

void APC_Chess::UpdateMainUI()
{
	EPlayerColor color;
	GameModeRef->GetActivePlayerColor(color);
	UIMainRef->SetActivePlayer(color);

	for (int32 i = 0; i < (int32)EPlayerColor::Max;++i) 
	{
		SetPlayerInfoInUI(i);
	}

	int32 count = 0;
	GameModeRef->GetMoveCount(count);
	UIMainRef->SetMoveCount(count);
	FString notation;
	GameModeRef->GetLatestMove(color, notation);
	UIMainRef->SetLatestMove(color, notation);
	UIMainRef->SetMessage(Message);
	bool isCheckMate = false;
	bool isStaleMate = false;
	GameModeRef->GetGameStatus(isCheckMate, isStaleMate);
	if(isCheckMate)
	{
		UIMainRef->SetMessage2(TEXT("Check Mate! Game Over"));
	}
	else if (isStaleMate)
	{
		UIMainRef->SetMessage2(TEXT("Stale Mate! Game Over"));
	}
	else
	{
		UIMainRef->SetMessage2(TEXT(""));
	}
}

void APC_Chess::SetPlayerInfoInUI(int32 PlayerIndex)
{
	FChessPlayer player;
	GameModeRef->GetPlayerByIndex(PlayerIndex, player);
	UIMainRef->SetPlayerName(player.Color, player.Name);
	UIMainRef->SetCheckStatus(player.Color, player.IsInCheckFlag);
	switch (player.Color)
	{
	case EPlayerColor::White:
		UIMainRef->SetCheckWhiteCaptureCount(player.Captures);
		break;
	case EPlayerColor::Black:
		UIMainRef->SetCheckBlackCaptureCount(player.Captures);
		break;
	}
}

void APC_Chess::SetMessage(FString Msg)
{
	Message = Msg;
}
