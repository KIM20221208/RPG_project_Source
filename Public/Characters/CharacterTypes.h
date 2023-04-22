#pragma once

/*
* 强类型枚举头文件
*/

/*
* UENUM: 反射给蓝图的宏
*/

// P97.Identifying if RPG_projectCharacter equipped weapon
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One-Hand Weapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped Two-Hand Weapon")

};

// P104.Identifying what kind of action is RPG_projectCharacter doing
UENUM(BlueprintType)
enum class EActionState : uint8
{
	// P97.Character is in idling state
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	// P200.RPG_Character is in Death state
	EAS_Dead UMETA(DisplayName = "Dead"),
	// P188.Character is in Getting hit state
	EAS_HitReaction UMETA(DisplayName = "HitReaction"),
	// P211.Character is in Dodging state
	EAS_Dodge UMETA(DisplayName = "Dodge"),
	// P97.Character is in attacking state
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	// P97.Character is in equipping weapon state
	EAS_EquippingWeapon UMETA(DisplayName = "_EquippingWeapon")

};

// P159.声明判断角色死亡与否和死亡时播放的动画的强类型枚举，枚举成员类型规定为 unsigned int 8
UENUM(BlueprintType)
enum EDeathPose
{
	// P159.角色死了，播放哪种动画
	EDP_Death1 UMETA(DisplayName = "Death1"),
	EDP_Death2 UMETA(DisplayName = "Death2"),
	EDP_Death3 UMETA(DisplayName = "Death3"),
	EDP_Death4 UMETA(DisplayName = "Death4"),
	EDP_Death5 UMETA(DisplayName = "Death5"),

	// P180.此枚举类型的成员数量
	EDP_MAX UMETA(DisplayName = "DefaultMax")

};

// P169.声明判断敌人行动模式的强类型枚举，枚举成员类型规定为 unsigned int 8。P180.因为日志的warning而进行了类型的更改：由强枚举修改为普通枚举
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	// P181.敌人不处于任何状态
	EES_NoState UMETA(DisplayName = "NoState"),
	// P179.敌人处于死亡状态
	EES_Dead UMETA(DisplayName = "Dead"),
	// P169.敌人处于巡逻状态
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	// P169.敌人处于追逐状态
	EES_Chasing UMETA(DisplayName = "Chasing"),
	// P169.敌人处于攻击状态
	EES_Attacking UMETA(DisplayName = "Attacking"),
	// P179.敌人处于占用状态
	EES_Engaged UMETA(DisplayName = "Engaged")

};