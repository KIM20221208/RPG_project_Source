// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBarComponent.generated.h"

class UHealthBar;

/**
 * キャラの体力を表示するクラス。
 */

UCLASS()
class RPG_PROJECT_API UHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()

	
public:
	/**
	 * Getter & Setter:
	 */
	// P154.Setter: キャラの体力HUDを表示されてないとセット（表示）、ダメージを受けたら更新する。
	void SetHealthPercent(float Percent);

	
private:
	// P154.声明 UHealthBar* 的成员变量，接收此组件控制的部件组件。UPROPERTY() 可以默认初始化变量为 空指针，因为反射给蓝图的行为中，不在蓝图中初始化就会默认赋值为空指针
	UPROPERTY()
	UHealthBar* HealthBarWidget;

};
