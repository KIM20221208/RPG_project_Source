// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GraphicPresetButtonsUI.h"
#include "Components/Button.h"

void UGraphicPresetButtonsUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	//
	LowButton->OnClicked.AddDynamic(this, &UGraphicPresetButtonsUI::OnLowButtonClicked);
	MediumButton->OnClicked.AddDynamic(this, &UGraphicPresetButtonsUI::OnMediumButtonClicked);
	HighButton->OnClicked.AddDynamic(this, &UGraphicPresetButtonsUI::OnHighButtonClicked);
	UltraButton->OnClicked.AddDynamic(this, &UGraphicPresetButtonsUI::OnUltraButtonClicked);
	
}
