// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HealthBarComponent.h"
#include "HUD/HealthBar.h"
#include "Components/ProgressBar.h"

void UHealthBarComponent::SetHealthPercent(float Percent)
{
	// P154.每次检查进行转换非常耗费资源，所以只在空指针时进行转换赋值
	if (HealthBarWidget == nullptr)
	{
		// P154.检查此组件控制的部件组件是否为 UHealthBar 类
		HealthBarWidget = Cast<UHealthBar>(GetUserWidgetObject());
	}

	if (HealthBarWidget && HealthBarWidget->HealthBar)
	{
		// P154.设置进度条（血条）的百分比
		HealthBarWidget->HealthBar->SetPercent(Percent);

	}

}
