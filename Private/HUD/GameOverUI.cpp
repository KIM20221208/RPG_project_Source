// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameOverUI.h"
#include "Components/Button.h"

void UGameOverUI::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	// OnRestartButtonClickメリットは親クラス（UMyUserWidget）に定義されている。
	RestartButton->OnClicked.AddDynamic(this, &UGameOverUI::OnRestartButtonClick);
	
}
