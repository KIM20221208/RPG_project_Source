#pragma once

/**
 * Identifying what kind of player UI to add into viewport when gaming
 */

UENUM(BlueprintType)
enum class EHUDState : uint8
{
	// Viewport HUD is in gaming mode
	EHS_InGaming UMETA(DisplayName = "In Gaming"),
	// Viewport HUD is in item checking mode
	EHS_ItemChecking UMETA(DisplayName = "Item Checking"),
	// Viewport HUD is in game over mode
	EHS_GameOver UMETA(DisplayName = "Game Over")
	
};
