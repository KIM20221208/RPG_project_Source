// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HealthBarComponent.h"
#include "HUD/HealthBar.h"
#include "Components/ProgressBar.h"

void UHealthBarComponent::SetHealthPercent(float Percent)
{
	// P154.フレームごとに更新するのが無駄な性能を消耗する、よってnullptrの時だけで体力HUDを更新する。
	if (HealthBarWidget == nullptr)
	{
		// P154.本WidgetかコントロールするcomponentがUHealthBarクラスかを判断する。
		HealthBarWidget = Cast<UHealthBar>(GetUserWidgetObject());
		
	}

	if (HealthBarWidget && HealthBarWidget->HealthBar)
	{
		// P154.キャラの体力のPercentageを更新する。
		HealthBarWidget->HealthBar->SetPercent(Percent);

	}

}
