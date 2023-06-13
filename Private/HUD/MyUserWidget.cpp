// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MyUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMyUserWidget::OnRestartButtonClick()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			// Input modeを"gameOnly"から"UIOnly"に変更する。
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
			// 特定のLevelを開く。
			UGameplayStatics::OpenLevel(World, FName("Minimal_Default"));
			// UIをParentから削除する。同時にスクリーンから削除される。つまり、今は表示されているUIをスクリーンから削除する。
			UUserWidget::RemoveFromParent();
			// Input modeを"game"に戻す。
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			
		}
		
	}
	
}
