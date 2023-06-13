#pragma once

/*
* Strongly Typed Enum Header File.
*/

/*
* UENUM: Blueprintに反映するマクロ。
*/

// P97.RPG_projectCharacterの武器装備状態の判断用。
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One-Hand Weapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped Two-Hand Weapon")

};

// P104.RPG_projectCharacterが取っている行動の判断用。
UENUM(BlueprintType)
enum class EActionState : uint8
{
	// P97.プレイヤー：何もしていない状態。
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	// P200.プレイヤー：死亡状態。
	EAS_Dead UMETA(DisplayName = "Dead"),
	// P188.プレイヤー：攻撃を受けて、被ダメージ動画をプレイしている状態。
	EAS_HitReaction UMETA(DisplayName = "HitReaction"),
	// P211.プレイヤー：回避アクションの状態。
	EAS_Dodge UMETA(DisplayName = "Dodge"),
	// P97.プレイヤー：攻撃アクションの状態。
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	// P97.プレイヤー：武器装備アクションの状態。
	EAS_EquippingWeapon UMETA(DisplayName = "_EquippingWeapon")

};

// P159.キャラが死んだあとプレイされる死亡動画（エディタで代入）の判断用。
UENUM(BlueprintType)
enum EDeathPose
{
	// P159.プレイされる死亡動画。
	EDP_Death1 UMETA(DisplayName = "Death1"),
	EDP_Death2 UMETA(DisplayName = "Death2"),
	EDP_Death3 UMETA(DisplayName = "Death3"),
	EDP_Death4 UMETA(DisplayName = "Death4"),
	EDP_Death5 UMETA(DisplayName = "Death5"),

	// P180.本列挙型内のメンバー数。
	EDP_MAX UMETA(DisplayName = "DefaultMax")

};

// P169.敵が取っている行動の判断用。
// P180.LogのWarningより、Strongly Typed EnumからEnumに修正。
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	// P181.敵：何もしていない状態。
	EES_NoState UMETA(DisplayName = "NoState"),
	// P179.敵：死亡状態。
	EES_Dead UMETA(DisplayName = "Dead"),
	// P169.敵：パトロール状態。
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	// P169.敵：プレイヤーを追いかけ状態。
	EES_Chasing UMETA(DisplayName = "Chasing"),
	// P169.敵：戦闘状態。
	EES_Attacking UMETA(DisplayName = "Attacking"),
	// P179.敵：なんかの行動をしている状態。
	EES_Engaged UMETA(DisplayName = "Engaged")

};
