// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

class UProgressBar;

/**
 * 敵の体力を表示するHUDクラス、エディタのwidget blueprintとbind用。
 */

UCLASS()
class RPG_PROJECT_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	// P153.UProgressBar typeのポインターを宣言する。
	// C++でのメンバー変数とwidget blueprintでのcomponentと同じ名前でネーミングする必要がある。或はbind出来ない。
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
	
};
