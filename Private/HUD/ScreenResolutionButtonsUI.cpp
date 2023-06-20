// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ScreenResolutionButtonsUI.h"

#include "Components/Button.h"

void UScreenResolutionButtonsUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	Button1280_720->OnClicked.AddDynamic(this, &UScreenResolutionButtonsUI::OnButton1280_720Clicked);
	Button1920_1080->OnClicked.AddDynamic(this, &UScreenResolutionButtonsUI::OnButton1920_1080Clicked);
	Button2560_1440->OnClicked.AddDynamic(this, &UScreenResolutionButtonsUI::OnButton2560_1440Clicked);
	
}
