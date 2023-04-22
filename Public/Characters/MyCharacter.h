// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Characters/CharacterTypes.h"
#include "MyCharacter.generated.h"

class AWeapon;
class UAnimMontage;
class UAttributeComponent;

/*
* Parent class of characters，P175.organized from PRPG_projectCharacter class and  Enemy class
*/
UCLASS()
class RPG_PROJECT_API AMyCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();


	/** <AActor> */ 
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/** </AActor> */


	/**
	 * Getter & Setter
	 */
	// P201.
	FORCEINLINE TEnumAsByte<EDeathPose> GetDeathPose() const { return  DeathPose; }
	

protected:
	/** <AActor> */ 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** </AActor> */


	/** <IHitInterface> */
	// P187.如果角色活着，则播放被攻击动画蒙太奇，音效，粒子
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/** </IHitInterface> */


	// P131.计算发生攻击判定的点相对于Enemy类的位置，播放相应的被攻击动画蒙太奇
	void DirectionalHitReact(const FVector& ImpactPoint);
	// P175.声明虚函数: 角色死亡成员函数,并播放死亡动画蒙太奇
	// P220.Make Die function blueprint Native Event
	UFUNCTION(BlueprintNativeEvent)
	void Die();
	// 175.声明虚函数: 攻击
	// P202.if combat target is dead, set combat target to nullptr
	virtual void Attack();
	// P179.被攻击时播放音效
	void PlayHitSound(const FVector& ImpactPoint);
	// P179.被攻击时播放粒子效果
	void SpawnHitParticles(const FVector& ImpactPoint);
	// P179.被攻击时扣血
	virtual void HandleDamage(float DamageAmount);
	// P180.设置胶囊体组件为“无碰撞”
	void DisableCapsule();
	// P179.检查角色是否活着
	bool IsAlive();
	// P175.声明虚函数: 判断是否在播放攻击动作
	virtual bool CanAttack();
	// P104.播放由四个方向遭受攻击时的被击中动作组成的动画蒙太奇
	void PlayHitReactMontage(const FName& SectionName);
	// P175.播放攻击动画蒙太奇
	virtual int32 PlayAttackMontage();
	// P180.播放死亡动画蒙太奇
	virtual int32 PlayDeathMontage();
	// P211.Play DodgeMontage by section name in DodgeMontage
	virtual void PlayDodgeMontage();
	// P191.Stop attack montage when get hit
	void StopAttackMontage();
	// P201.Set Mesh Collision To No Collision
	void DisableMeshCollision();


	// P175.声明虚函数: 把 ActionState 赋值为 Unoccupied ，可以与动画蒙太奇中的通知一起调用来防止角色在播放动画时平移在角色的ABP事件图标中调用。原 AttackEnd() 成员函数。
	UFUNCTION(BlueprintCallable)
	virtual void ActionEnd();

	// P121.根据攻击动画蒙太奇返回的通知开放武器的盒体攻击判定，传参由蓝图完成
	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	
	// P160.角色的战斗对象
	UPROPERTY(BlueprintReadOnly, Category = Combat)
	AActor* CombatTarget;
	
	// P110.声明识别装备在身上的武器的 AWeapon类指针成员变量
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;

	// P151.声明本地变量组件
	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attributes;

	// P192.
	UFUNCTION(BlueprintCallable)
	FVector GetTranslationWarpTarget();

	// P192.let character face to the combat target
	UFUNCTION(BlueprintCallable)
	FVector GetRotationWarpTarget();

	// P192.Warp Distance between character and CombatTarget
	UPROPERTY(EditAnywhere, Category = Combat)
	float WarpTargetDistance = 75.f;

	// P159.声明角色死亡姿势的强枚举类型的成员变量
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TEnumAsByte<EDeathPose> DeathPose;

	
private:
	// P180.按照 SectionName 播放特定动画蒙太奇
	void PlayMontageSection(UAnimMontage* Montage, const FName& SectionName);
	// P180.随机播放 动画蒙太奇中的某一段，返回播放的动画编号
	int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames);


	// P103.声明动画蒙太奇成员变量: 攻击
	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* AttackMontage;

	// P103.声明动画蒙太奇成员变量: 收到攻击。将从蓝图中赋值
	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* HitReactMontage;

	// P158.声明动画蒙太奇成员变量: 死亡。将从蓝图中赋值
	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* DeathMontage;
	
	// P211.Declare a pointer to store montage from Blue print
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* DodgeMontage;
	
	// P180.保存攻击动画蒙太奇中 蒙太奇片段的名称的动态数组
	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> AttackMontageSections;

	// P180.保存攻击死亡蒙太奇中 蒙太奇片段的名称的动态数组
	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> DeathMontageSections;

	// P132.声明一个从蓝图赋值 MetaSounds的 USoundBase* 类成员变量
	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* HitSound;

	// P133.声明一个从蓝图赋值 被攻击时触发的粒子效果的 UParticleSystem* 类成员变量
	UPROPERTY(EditAnywhere, Category = Combat)
	UParticleSystem* HitParticles;

};
