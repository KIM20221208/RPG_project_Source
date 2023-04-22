// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameOverUI.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UGameOverUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	RestartButton->OnClicked.AddDynamic(this, &UGameOverUI::OnRestartButtonClick);
	
}

void UGameOverUI::OnRestartButtonClick()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			// set input mode from "gameOnly" to "UIOnly"
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
			// Open a certain level 
			UGameplayStatics::OpenLevel(World, FName("Minimal_Default"));
			// Remove widget from it's parent, also be removed if bounded with screen 
			UUserWidget::RemoveFromParent();
			// set back input mode to "game"
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			
		}
	}
	
}
