#include "UI/UI_Main.h"
#include "../BattleChess.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

UUI_Main::UUI_Main(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GetObjectAsset(CompileFailedSound, USoundBase, "/Engine/EditorSounds/Notifications/CompileFailed_Cue.CompileFailed_Cue");
}

void UUI_Main::OpenUI()
{
	PlayAnimation(FadeIn);
}

void UUI_Main::SetMoveCount(int32 MoveCount)
{
	MoveCountValue->SetText(FText::AsNumber(MoveCount));
}

void UUI_Main::SetMessage(FString Text)
{
	Message->SetText(FText::FromString(Text));
	if(!Text.IsEmpty())
	{
		PlaySound(CompileFailedSound);
	}
}

void UUI_Main::SetMessage2(FString Text)
{
	Message2->SetText(FText::FromString(Text));
}

void UUI_Main::SetActivePlayer(EPlayerColor PlayerColor)
{
	switch (PlayerColor)
	{
	case EPlayerColor::White:
		WhiteMarker->SetBrushColor(FLinearColor::Yellow);
		BlackMarker->SetBrushColor(FLinearColor::Black);
		break;
	case EPlayerColor::Black:
		WhiteMarker->SetBrushColor(FLinearColor::Black);
		BlackMarker->SetBrushColor(FLinearColor::Yellow);
		break;
	}
}

void UUI_Main::SetPlayerName(EPlayerColor PlayerColor, FString PlayerName)
{
	switch (PlayerColor)
	{
	case EPlayerColor::White:
		WhiteName->SetText(FText::FromString(PlayerName));
		break;
	case EPlayerColor::Black:
		BlackName->SetText(FText::FromString(PlayerName));
		break;
	}
}

void UUI_Main::SetLatestMove(EPlayerColor PlayerColor, FString MoveNotation)
{
	switch (PlayerColor)
	{
	case EPlayerColor::White:
		WhiteMove->SetText(FText::FromString(MoveNotation));
		break;
	case EPlayerColor::Black:
		BlackMove->SetText(FText::FromString(MoveNotation));
		break;
	}
}

void UUI_Main::SetCheckWhiteCaptureCount(int32 CaptureCount)
{
	WhiteCaptureCount->SetText(FText::AsNumber(CaptureCount));
}

void UUI_Main::SetCheckBlackCaptureCount(int32 CaptureCount)
{
	BlackCaptureCount->SetText(FText::AsNumber(CaptureCount));
}

void UUI_Main::SetCheckStatus(EPlayerColor PlayerColor, bool IsInCheck)
{
	FText statusMsg = FText::GetEmpty();
	if(IsInCheck)
	{
		statusMsg = FText::FromString(TEXT("Check"));
		PlaySound(CompileFailedSound);
	}
	switch (PlayerColor)
	{
	case EPlayerColor::White:
		WhiteStatus->SetText(statusMsg);
		BlackStatus->SetText(FText::GetEmpty());
		break;
	case EPlayerColor::Black:
		WhiteStatus->SetText(FText::GetEmpty());
		BlackStatus->SetText(statusMsg);
		break;
	}
}
