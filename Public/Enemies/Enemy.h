// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterTypes.h"
#include "Characters/MyCharacter.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class AAIController;
class UPawnSensingComponent;
class AWeapon;
class ASoul;

/**
* 敵のベースクラス、P182.クラスを整理した。
*/
UCLASS()
class RPG_PROJECT_API AEnemy : public AMyCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	/** <AActor> */
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// P155
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// P177.実例化した本クラスがWorldから削除される。
	virtual void Destroyed() override;
	/** </AActor> */

	/** <IHitInterface> */
	// P125
	// P140
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/** </IHitInterface> */

protected:
	/** <AActor> */
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** </AActor> */
	
	/** <AMyCharacter> */
	// 178.攻撃時、キャラの状態を”Engaged”に設定し、攻撃動画をプレイする。
	virtual void Attack() override;
	// P179.攻撃可能かを判断する。
	// 1.戦闘相手が攻撃範囲内にいる、2."EnemyState"が"Attacking"、又は"Engaged"ではない、3.自分が死んでいない。
	// can: ture, can't: false.
	virtual bool CanAttack() override;
	// P179.攻撃された時に体力の値を更新する。
	virtual void HandleDamage(float DamageAmount) override;
	// P181.色んな行動が終了時、エディタのABP（Animation blueprint）からcallされる。
	// エディタでcallされる。
	virtual void ActionEnd() override;
	// P158.キャラが死亡した後、死亡動画をプレイする。
	// P175
	virtual void Die_Implementation() override;
	/** </AMyCharacter> */
	
	// P209.キャラが死んだ後、Soulを生成する。
	void SpawnSoul();
	
	// P169.キャラの行動パタン、default: Patrolling.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;


private:
	/**
	* AI Behavior
	*/
	// P182.ゲームが始まる時、キャラの初期化。
	void InitializeEnemy();
	// P167.パトロールターゲットに移動する。
	void MoveToTarget(AActor* Target);
	// P167.元P166の改良：パトロールターゲットに到達すると、動的配列PatrolTargets中の新しいパトロールターゲットランダムに選択して移動する。
	void CheckPatrolTarget();
	// P167.元P160でのコードを抽出した物：戦闘相手との距離をcheckする。設定した距離より離れた場合、HealthBarをプレイヤーが見えないように隠す。
	void CheckCombatTarget();
	// P167.パトロール間のIdleが終わった後、次のパトロールターゲットに移動する。
	void PatrolTimerFinished();
	// P179.キャラのHealthBarをプレイヤーが見えないように隠す。
	void HideHealthBar();
	// P179.キャラのHealthBarをプレイヤーが見える様にする。
	void ShowHealthBar();
	// P179.戦闘相手に対する興味（敵扱いしない）を失う。
	void LoseInterest();
	// P179.キャラがパトロール状態に入る。
	void StartPatrolling();
	// P179.キャラが追いかけ状態に入る。
	void ChaseTarget();
	// P179.戦闘相手が追いかけ範囲にいるかどうかを判断する。
	// yes: true, no: false.
	bool IsOutsideCombatRadius();
	// P179.戦闘相手が攻撃範囲外にいるからどうかを判断する。
	// yes: true, no: false.
	bool IsOutsideAttackRadius();
	// P179.戦闘相手が攻撃範囲内にいるからどうかを判断する。
	// yes: true, no: false.
	bool IsInsideAttackRadius();
	// P179.キャラが追いかけ状態にいるからどうかを判断する。
	// yes: true, no: false.
	bool IsChasing();
	// P179.キャラが攻撃状態にいるからどうかを判断する。
	// yes: true, no: false.
	bool IsAttacking();
	// P179.キャラが死んでいるからどうかを判断する。
	// yes: true, no: false.
	bool IsDead();
	// P179.キャラが何かしらの動き（攻撃等）をしているかどうかを判断する。
	// yes: true, no: false.
	bool IsEngaged();
	// P179.パトロール時のIdleタイマーをclearする。
	void ClearPatrolTimer();
	// P179.攻撃時のタイマーをスタートする。
	void StartAttackTimer();
	// P179.攻撃時のタイマーをclearする。
	void ClearAttackTimer();
	// P167.新しいパトロールターゲットを選ぶ。
	AActor* ChoosePatrolTarget();
	// P166.キャラとActorクラス（戦闘相手、パトロールターゲット等）間の距離を判断する。
	// 設定した距離に到達：true、設定した距離に達していない、或はTargetがnullptr：false。
	bool InTargetRange(AActor* Target, double Radius);
	// P182.default武器（エディタから代入）を生成する。
	void SpawnDefaultWeapon();
	
	// P168.USensingComponentクラスのOnSeePawnメソッドが探知出来たAPawnクラスのcallback。
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

	// P165.キャラを制御するAIコントローラー。
	UPROPERTY()
	AAIController* EnemyController;

	// P165.キャラのパトロールターゲット、エディタから代入。
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	// P165.パトロールターゲットが保存されている動的配列、エディタから代入。
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	// P177.AWeaponの派生クラスだけ代入出来る変数、キャラが装備すべき武器を保存している、エディタから代入。
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;

	// P152.キャラのHealthBarエディタから代入。。
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	// P168.戦闘相手を探知するSensing。
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	// P160.戦闘相手に興味を持つ距離、default: 500.f、エディタから修正可能。
	UPROPERTY(EditAnywhere, Category = Combat)
	double CombatRadius = 500.f;

	// P171.キャラが攻撃状態に入る距離，default: 150.f、エディタから修正可能。
	UPROPERTY(EditAnywhere, Category = Combat)
	double AttackRadius = 150.f;

	// P191. キャラがターゲットまでの移動距離、エディタから修正可能。
	UPROPERTY(EditAnywhere, Category = Combat)
	float AcceptanceRadius = 60.f;

	// P167.パトロールターゲットに到達した後のIdleの長さ、default:（5.f, 10,f）、エディタから修正可能。
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 5.f;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 10.f;

	// P179.パトロール時の移動スピード、default: 125.f、エディタから修正可能。
	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrollingSpeed = 125.f;
	
	// P179.戦闘時の攻撃間隔、default:（0.5f, 1.f）、エディタから修正可能。
	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;
	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	// P179.追いかけ時の移動スピード、default: 300.f、エディタから修正可能。
	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingSpeed = 300.f;

	// P180.死亡した後、死体がWorldに残っている時間、default: 8.f、エディタから修正可能。
	UPROPERTY(EditAnywhere, Category = Combat)
	float DeathLifeSpan = 8.f;

	// 209.ASoulクラスの派生クラスだけ代入出来る変数、キャラが死んだ後生成させる経験値を保存、、エディタから代入。
	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<ASoul> SoulClass;
	
	// P167.具体的なパトロールターゲットに到達した後のIdleの長さ。
	FTimerHandle PatrolTimer;
	// P179.具体的な戦闘時の攻撃間隔。
	FTimerHandle AttackTimer;
	
};
