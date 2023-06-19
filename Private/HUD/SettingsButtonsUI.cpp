// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SettingsButtonsUI.h"
#include "Animation/MovieSceneUMGComponentTypes.h"
#include "Components/Button.h"

void USettingsButtonsUI::FadeInFX()
{
	PlayAnimation(FadeIn);
	
}

void USettingsButtonsUI::FadeOutFX()
{
	PlayAnimation(FadeIn, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void USettingsButtonsUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	//
	FadeInFX();

	//
	LowButton->OnClicked.AddDynamic(this, &USettingsButtonsUI::OnLowButtonClicked);
	LowButton->OnHovered.AddDynamic(this, &USettingsButtonsUI::OnLowButtonHovered);
	LowButton->OnUnhovered.AddDynamic(this, &USettingsButtonsUI::OnLowButtonUnhovered);

	MediumButton->OnClicked.AddDynamic(this, &USettingsButtonsUI::OnMediumButtonClicked);
	MediumButton->OnHovered.AddDynamic(this, &USettingsButtonsUI::OnMediumButtonHovered);
	MediumButton->OnUnhovered.AddDynamic(this, &USettingsButtonsUI::OnMediumButtonUnhovered);
	
	HighButton->OnClicked.AddDynamic(this, &USettingsButtonsUI::OnHighButtonClicked);
	HighButton->OnHovered.AddDynamic(this, &USettingsButtonsUI::OnHighButtonHovered);
	HighButton->OnUnhovered.AddDynamic(this, &USettingsButtonsUI::OnHighButtonUnhovered);
	
	UltraButton->OnClicked.AddDynamic(this, &USettingsButtonsUI::OnUltraButtonClicked);
	UltraButton->OnHovered.AddDynamic(this, &USettingsButtonsUI::OnUltraButtonHovered);
	UltraButton->OnUnhovered.AddDynamic(this, &USettingsButtonsUI::OnUltraButtonUnhovered);
	

	BackButton->OnClicked.AddDynamic(this, &USettingsButtonsUI::OnBackButtonClicked);
	BackButton->OnHovered.AddDynamic(this, &USettingsButtonsUI::OnBackButtonHovered);
	BackButton->OnUnhovered.AddDynamic(this, &USettingsButtonsUI::OnBackButtonUnhovered);
	
}

void USettingsButtonsUI::OnBackButtonClicked()
{
	DisableButtons();
	FadeOutFX();
	Super::OnBackButtonClicked();
	
}

void USettingsButtonsUI::OnLowButtonHovered()
{
	PlayAnimation(LowButtonHover);
	
}

void USettingsButtonsUI::OnLowButtonUnhovered()
{
	PlayAnimation(LowButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void USettingsButtonsUI::OnMediumButtonHovered()
{
	PlayAnimation(MediumButtonHover);
	
}

void USettingsButtonsUI::OnMediumButtonUnhovered()
{
	PlayAnimation(MediumButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void USettingsButtonsUI::OnHighButtonHovered()
{
	PlayAnimation(HighButtonHover);
	
}

void USettingsButtonsUI::OnHighButtonUnhovered()
{
	PlayAnimation(HighButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void USettingsButtonsUI::OnUltraButtonHovered()
{
	PlayAnimation(UltraButtonHover);
	
}

void USettingsButtonsUI::OnUltraButtonUnhovered()
{
	PlayAnimation(UltraButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void USettingsButtonsUI::OnBackButtonHovered()
{
	PlayAnimation(BackButtonHover);
	
}

void USettingsButtonsUI::OnBackButtonUnhovered()
{
	PlayAnimation(BackButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void USettingsButtonsUI::DisableButtons()
{
	//
	LowButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	MediumButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	HighButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	UltraButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	BackButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	
}
