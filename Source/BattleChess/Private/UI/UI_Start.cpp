#include "UI/UI_Start.h"
#include "GM_Chess.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include <Kismet/GameplayStatics.h>

UUI_Start::UUI_Start(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UUI_Start::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	StartButton->OnClicked.AddDynamic(this,&ThisClass::OnStartButtonClicked);
}

void UUI_Start::OnStartButtonClicked()
{
	PlayAnimation(FadeOut,0.f,1,EUMGSequencePlayMode::Forward,1.f,true);
	FTimerHandle tempTimer;
	GetWorld()->GetTimerManager().SetTimer(tempTimer,this,&ThisClass::StartGame,1.f);
}

void UUI_Start::StartGame()
{
	AGM_Chess* gm = Cast<AGM_Chess>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(gm))
	{
		UE_LOG(LogTemp, Log, TEXT("게임모드 형변환 실패"));
		return;
	}
	gm->StartGame(Player1Name->GetText(), Player2Name->GetText());
}
