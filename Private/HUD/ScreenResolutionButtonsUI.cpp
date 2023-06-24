// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ScreenResolutionButtonsUI.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"

void UScreenResolutionButtonsUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	Button1280_720->OnClicked.AddDynamic(this, &UScreenResolutionButtonsUI::OnButton1280_720Clicked);
	Button1920_1080->OnClicked.AddDynamic(this, &UScreenResolutionButtonsUI::OnButton1920_1080Clicked);
	Button2560_1440->OnClicked.AddDynamic(this, &UScreenResolutionButtonsUI::OnButton2560_1440Clicked);
	
}

void UScreenResolutionButtonsUI::SwitchScreenResolution(const int XCoordinate, const int YCoordinate)
{
	UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
	if (GameUserSettings)
	{
		FIntPoint Resolution = FIntPoint(XCoordinate, YCoordinate);
		GameUserSettings->SetScreenResolution(Resolution);
		GameUserSettings->ApplyResolutionSettings(false);
		GameUserSettings->ApplySettings(true);
		
	}
	
}

void UScreenResolutionButtonsUI::CloseScreenResolutionButtonsUI()
{
	UUserWidget::RemoveFromParent();
	
}

void UScreenResolutionButtonsUI::OnButton1280_720Clicked()
{
	SwitchScreenResolution(1280, 720);
	CloseScreenResolutionButtonsUI();
	
}

void UScreenResolutionButtonsUI::OnButton1920_1080Clicked()
{
	SwitchScreenResolution(1920, 1080);
	CloseScreenResolutionButtonsUI();
	
}

void UScreenResolutionButtonsUI::OnButton2560_1440Clicked()
{
	SwitchScreenResolution(2560, 1440);
	CloseScreenResolutionButtonsUI();
	
}
