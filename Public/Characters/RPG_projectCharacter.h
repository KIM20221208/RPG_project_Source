// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterTypes.h"
#include "MyCharacter.h"
#include "Interfaces/PickupInterface.h"
#include "RPG_projectCharacter.generated.h"

/**
* プレイヤー操作キャラクラス。
*/

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;
class URPG_projectOverlay;
class ASoul;
class ATreasure;
class ARPG_projectHUD;

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
	// P194.キャラがダメージを受ける、AWeapon::OnBoxOverlapメソッドからcallされる。
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	/** </AActor> */

	
	/** <ACharacter> */
	// P199
	virtual void Jump() override;
	/** </ACharacter> */

	
	/** <IHitInterface> */
	// P183.IHitInterfaceから継承された純粋仮想関数をoverride、キャラが攻撃された時callされる。
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/** </IHitInterface> *
	
	
	/**
	* Getter & Setter
	*/
	// P97.Getter: キャラの武器装備状況をreturn。
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	// P201.Getter: キャラが取っているモーション状況をreturn。
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
	// Setter: Set ActionState.
	FORCEINLINE void SetActionState(EActionState ToSet) { ActionState = ToSet; }

	/** <IPickupInterface> */
	// P206.Setter: Set Item to OverlappingItem.
	virtual void SetOverlappingItem(AItem* Item) override;
	// P206.Setter: Set amount of souls in attributes.
	virtual void AddSoul(ASoul* Soul) override;
	// P208.Setter: Set amount of Golds in attributes.
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
	// P71.プレイヤー操作：前後移動。
	void MoveForward(float Value);
	// P72.プレイヤー操作：カメラ移動。
	void Turn(float Value);
	void LookUp(float Value);
	// P72.プレイヤー操作：左右移動。
	void MoveRight(float Value);
	// P96.プレイヤー操作：装備。
	void EKeyPressed();
	// P103.プレイヤー操作バインド：攻撃。
	// P175.MyCharacterの仮想関数をoverride。
	virtual void Attack() override;
	// P212.return true if action state is occupied
	bool IsActionOccupied();
	// P211.プレイヤー操作バインド：回避。
	void Dodge();
	// Change view port to "InGamePause" UI
	void ESCKeyPressed();

	
	/** 
	* Combat
	*/
	// P182.武器を装備する。
	void EquipWeapon(AWeapon* Weapon);
	
	/** <AMyCharacter> */
	// P105.ActionStateを"Unoccupied"に割り当てる。
	// エディタのキャラがABPからcallされる。キャラが同時に複数のコマンドを受けた時、前のコマンドを最後まで実行する事を保証する。
	// 元AttackEnd()メソッド。
	virtual void ActionEnd() override;
	// P105.キャラが攻撃可能かどうか（別の動きをしていない、かつ武器を装備している）を判断する。
	// Can: true, Can't: false.
	virtual bool CanAttack() override;
	// P200.override Die function, play GameOver UI after dead.
	virtual void Die_Implementation() override;
	/** </AMyCharacter> */
	
	// P110.武器を装備解除できるかどうか（別の動きをしていない、かつ武器を装備している）を判断する。
	// Can: true, Can't: false.
	bool CanDisarm();
	// P110.武器を装備できるかどうか（別の動きをしていない、かつ武器を装備していない、かつ身に収納している武器がある）を判断する。
	// Can: true, Can't: false.
	bool CanArm();
	// P182.武器の装備解除動画をプレイ、かつキャラの状態を"Unequipped"にする。
	void DisArm();
	// P182.武器の装備動画をプレイ、かつキャラの状態を"EquippedOneHandedWeapon"にする。
	void Arm();
	// P110.EquipMontageの中、プレイすべき動画を選択する。
	void PlayEquipMontage(const FName& SectionName);
	// P212.return true if has stamina.
	bool HasEnoughStamina();
	
	// P112.武器を右手のSocketから背中のSocketに移動する、エディタでcallされる。
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	// P112.武器を背中のSocketから右手のSocketに移動する、エディタでcallされる。
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();


private:
	// P199.Return true if RPG_projectCharacter state is Unoccupied
	bool IsUnoccupied();
	// P198.initialize attributes for RPG_projectCharacter
	void InitializeRPG_projectOverlay();
	// P199.Refresh Health bar when get hit
	void SetHUDHealth();
	
	
	/**
	* Character Components
	*/
	// P72.キャラのカメラ用SpringArm。
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	// P72.キャラのカメラ。
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	// P75.キャラの髪の毛、エディタから代入。
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;

	// P75.キャラの眉毛、エディタから代入。
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	// P96.キャラがoverlappingしているアイテムと。
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;


	// P97.キャラの武の装備状態確認用。
	UPROPERTY(VisibleAnywhere)
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	//P104.キャラが取っている行動確認用。
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	// P110.キャラの武器装備動画、エディタから代入。
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

	// P198.Declare a param that can access the attributes(Health, Stamina, Gold, Souls)
	UPROPERTY()
	URPG_projectOverlay* RPG_projectOverlay;

	// キャラのHUD、エディタのGame Modeからcallされる。
	UPROPERTY()
	ARPG_projectHUD* RPG_projectHUD;
	
};
