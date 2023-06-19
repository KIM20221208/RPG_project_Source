#pragma once

/**
 * ゲームの画質に関するSettingsの判断用。
 */

enum class EOverallScalabilityLevelState : int32
{
	EOSLS_Low,
	EOSLS_Medium,
	EOSLS_High,
	EOSLS_Ultra,
	// Cinematic級の画質Settingsはまだ使用されていない。
	EOSLS_Cinematic
	
};
