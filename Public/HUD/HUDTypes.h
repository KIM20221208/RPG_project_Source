#pragma once

/**
 * ゲーム中、viewportに表示すべきUIの判断用。
 */

UENUM(BlueprintType)
enum class EHUDState : uint8
{
	// Viewport HUD: Gaming mode.
	EHS_InGaming UMETA(DisplayName = "In Gaming"),
	// Viewport HUD: In game pause mode.
	EHS_InGamePause UMETA(DisplayName = "In Game Pause"),
	// Viewport HUD: Game over mode.
	EHS_GameOver UMETA(DisplayName = "Game Over")
	
};
