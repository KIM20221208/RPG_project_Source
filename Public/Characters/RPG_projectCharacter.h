// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterTypes.h"
#include "MyCharacter.h"
#include "Interfaces/PickupInterface.h"
#include "RPG_projectCharacter.generated.h"

// P72.前向声明
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;
class URPG_projectOverlay;
class ASoul;
class ATreasure;
class ARPG_projectHUD;

/**
* Player control character class
*/
UCLASS()
class RPG_PROJECT_API ARPG_projectCharacter : public AMyCharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPG_projectCharacter();
	

	/** <AActor> */
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// P194.Will be called by AWeapon::OnBoxOverlap function
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	/** </AActor> */

	
	/** <ACharacter> */
	// P199.
	virtual void Jump() override;
	/** </ACharacter> */

	
	/** <IHitInterface> */
	// P183.覆盖继承自 IHitInterface 的纯虚函数
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/** </IHitInterface> *
	
	
	/**
	* Getter & Setter
	*/
	// P97.强制内联函数，返回 private 成员中的 CharacterState 变量
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	// P201.
	FORCEINLINE EActionState GetActionState() const { return ActionState; }

	/** <IPickupInterface> */
	// P206.Setter: Set Item to OverlappingItem
	virtual void SetOverlappingItem(AItem* Item) override;
	// P206.Setter: Set amount of souls in attributes
	virtual void AddSoul(ASoul* Soul) override;
	// P208.Setter: Set amount of Golds in attributes
	virtual void AddGold(ATreasure* Treasure) override;
	/** </IPickupInterface> */
	

protected:
	/** <AActor> */
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** </AActor> */
	

	/**
	* Callback for input
	*/
	// P71.声明前后移动组件函数
	void MoveForward(float Value);
	// P72.声明视角组件函数
	void Turn(float Value);
	void LookUp(float Value);
	// P72.声明左右移动组件函数
	void MoveRight(float Value);
	// P96.声明装备组件函数
	void EKeyPressed();
	// P103.声明成员函数: 攻击。P175.覆盖 MyCharacter 中的虚函数
	virtual void Attack() override;
	// P212.return true if action state is occupied
	bool IsActionOccupied();
	// P211.Declare input
	void Dodge();
	

	/** 
	* Combat
	*/
	// P182.装备武器
	void EquipWeapon(AWeapon* Weapon);
	// P105.把 ActionState 赋值为 Unoccupied ，可以与动画蒙太奇中的通知一起调用来防止角色在播放动画时平移在角色的ABP事件图标中调用。原 AttackEnd() 成员函数。P175.覆盖 MyCharacter 中的虚函数
	virtual void ActionEnd() override;
	// P105.判断是否在播放攻击动作。P175.覆盖 MyCharacter 中的虚函数
	virtual bool CanAttack() override;
	// P110.判断是否可以解除武器
	bool CanDisarm();
	// P110.判断是否可以装备武器
	bool CanArm();
	// P182.播放卸下装备动画 动画蒙太奇，并设置角色的相应状态
	void DisArm();
	// P182.播放装备动画 动画蒙太奇，并设置角色的相应状态
	void Arm();
	// P110.选择播放 EquipMontage 中的段落
	void PlayEquipMontage(const FName& SectionName);
	// P200.override Die function derived from AMyCharacter
	virtual void Die_Implementation() override;
	// P212.return true if has stamina
	bool HasEnoughStamina();
	
	// P112.把武器从右手的插口依附到后背的插口，在蓝图调用
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	// P112.把武器从后背的插口依附到右手的插口，在蓝图调用
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	// P188.在播放完受到攻击的动画蒙太奇后把角色状态设置为 “Unoccupied”
	UFUNCTION(BlueprintCallable)
	void HitReactEnd();


private:
	// P199.Return true if RPG_projectCharacter state is Unoccupied
	bool IsUnoccupied();
	// P198. initialize attributes for RPG_projectCharacter
	void InitializeRPG_projectOverlay();
	// P199.Refresh Health bar when get hit
	void SetHUDHealth();
	
	
	/**
	* Character Components
	*/
	// P72.声明弹簧组件指针
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	// P72.声明相机组件指针
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	// P75.声明Groom组件指针，头发
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;

	// P75.声明Groom组件指针，眉毛
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	// P96.声明AItem类指针变量，检测与AItem类派生物体的碰撞
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;


	// P97.声明判断是否装备武器的强类型枚举成员变量
	UPROPERTY(VisibleAnywhere)
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	//P104.声明判断人物是否在播放动画
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	// P110.声明动画蒙太奇成员变量: 装备
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

	// P198.Declare a param that can access the attributes(Health, Stamina, Gold, Souls)
	UPROPERTY()
	URPG_projectOverlay* RPG_projectOverlay;

	//
	UPROPERTY()
	ARPG_projectHUD* RPG_projectHUD;
	
};
