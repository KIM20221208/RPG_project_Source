// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

class UProgressBar;

/**
 * HUD class for showing Enemy-class health bar
 */
UCLASS()
class RPG_PROJECT_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	// P153.declare UProgressBar type pointer member param，
	// insure the name of C++ member param and blueprint widget got same name, equal to call back a value from blueprint
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
	
};
