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
* 各種キャラクラスの親クラス、P175.PRPG_projectCharacterクラスとEnemyクラスから整理して作られている
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
	// P201.Getter: プレイされる死亡動画のserial numberをreturn
	FORCEINLINE TEnumAsByte<EDeathPose> GetDeathPose() const { return  DeathPose; }
	

protected:
	/** <AActor> */ 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** </AActor> */

	/** <IHitInterface> */
	// P187.ダメージを受けた時callされる：キャラが生きているなら、被ダメージ動画、FX、音声等をプレイする
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/** </IHitInterface> */

	// P131.キャラが攻撃された時発生した衝突判定の相対的位置（前後左右）より被ダメージ動画をプレイする
	void DirectionalHitReact(const FVector& ImpactPoint);
	// P175.仮想関数宣言：死亡動画をプレイする、キャラのHPが0になるときにcallされる
	// P220.仮想関数宣言より修正：Make Die function blueprint Native Event
	UFUNCTION(BlueprintNativeEvent)
	void Die();
	// 175.仮想関数宣言：攻撃
	// P202.戦闘相手が死んだとき、CombatTargetをnullptrに設定する、死体に対しての攻撃する事を防ぐ
	virtual void Attack();
	// P179.攻撃された時にプレイされる音声
	void PlayHitSound(const FVector& ImpactPoint);
	// P179.攻撃された時にプレイされる粒子FX（血等）
	void SpawnHitParticles(const FVector& ImpactPoint);
	// P179.攻撃された時にダメージを受ける
	virtual void HandleDamage(float DamageAmount);
	// P180.環境との物理的衝突判定用ボリューム設定を"No Collision"にする
	// P160.キャラが死ぬときにcallされる
	void DisableCapsule();
	// P179.キャラが生きているからどうかを判断する：
	// Alive: true, Dead: false
	bool IsAlive();
	// P175.仮想関数宣言: キャラが攻撃可能かどうかを判断する
	// Can: true, Can't: false
	virtual bool CanAttack();
	// P104.SectionNameより被ダメージ動画をプレイする
	void PlayHitReactMontage(const FName& SectionName);
	// P175.攻撃動画をプレイする
	virtual int32 PlayAttackMontage();
	// P180.死亡動画をプレイする
	virtual int32 PlayDeathMontage();
	// P211.SectionNameより回避動画をプレイする、SectionName is hard coded
	virtual void PlayDodgeMontage();
	// P191.攻撃された時、キャラの攻撃動画をストップする
	void StopAttackMontage();
	// P201.キャラが死んだ後、モデルの物理的衝突設定を"No Collision"にする、死体がプレイヤーの移動を邪魔する事を防ぐ
	void DisableMeshCollision();

	// P175.仮想関数宣言：キャラのメンバー変数ActionStateをUnoccupiedに設定する
	// 色んな行動が終了時、エディタのABP（Animation blueprint）からcallされる
	// エディタでcallされる
	// former AttackEnd() method
	UFUNCTION(BlueprintCallable)
	virtual void ActionEnd();

	// P121.Attack Animation MontageからreturnされるNotifyから武器の当たり判定ボリュームを開放する
	// エディタでcallされる
	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	
	// P160.キャラの戦闘相手
	UPROPERTY(BlueprintReadOnly, Category = Combat)
	AActor* CombatTarget;
	
	// P110.キャラが装備している武器
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;

	// P151.キャラの属性（体力、スタミナ等）に関するComponent
	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attributes;

	// P192.キャラが攻撃行動をとる時、warpする位置をreturnする
	// エネミー攻撃がプレイヤーに回避し易い事に対する最適化：エネミーが攻撃時、プレイヤーの隣に強制的移動する
	// エディタでcallされる
	UFUNCTION(BlueprintCallable)
	FVector GetTranslationWarpTarget();

	// P192.キャラが攻撃行動をとる時、warpした後の向きをreturnする
	// エネミー攻撃がプレイヤーに回避し易い事に対する最適化：warp後、向きを戦闘相手にする
	// エディタでcallされる
	UFUNCTION(BlueprintCallable)
	FVector GetRotationWarpTarget();

	// P192.キャラが攻撃行動をとる時、戦闘相手にwarpする距離、
	// default: 75.f、エディタで修正可能
	UPROPERTY(EditAnywhere, Category = Combat)
	float WarpTargetDistance = 75.f;

	// P159.キャラの死亡動画
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TEnumAsByte<EDeathPose> DeathPose;

	
private:
	// P180.SectionNameよりMontageの動画をプレイする
	void PlayMontageSection(UAnimMontage* Montage, const FName& SectionName);
	// P180.Montageの動画をランダムにプレイする、プレイした動画のSerial numberをreturnする
	// 攻撃動画と死亡動画はランダムにプレイされる
	int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames);
	
	// P103.キャラの攻撃動画、エディタから代入
	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* AttackMontage;

	// P103.キャラの被ダメージ動画、エディタから代入
	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* HitReactMontage;

	// P158.キャラの死亡動画、エディタから代入
	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* DeathMontage;
	
	// P211.キャラの回避動画、エディタから代入
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* DodgeMontage;
	
	// P180.Attack Montage中の動画のSection Name保存用配列、エディタから代入
	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> AttackMontageSections;

	// P180.Death Montage中の動画のSection Name保存用配列、エディタから代入
	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> DeathMontageSections;

	// P132.被ダメージにプレイされる音声、エディタから代入
	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* HitSound;

	// P133.被ダメージにプレイされるFX、エディタから代入
	UPROPERTY(EditAnywhere, Category = Combat)
	UParticleSystem* HitParticles;

};
