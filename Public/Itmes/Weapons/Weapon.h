// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Itmes/Item.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;

/**
 * 各種武器の親クラス。
 */
UCLASS()
class RPG_PROJECT_API AWeapon : public AItem
{
	GENERATED_BODY()

	
public:
	AWeapon();
	// P96.武器装備のAction Mapping。
	// InParentはattachするモデル、InSocketNameはモデルの中、指定されたattach先のSocket。
	// P155.NewOwnerはインスタンスレベルの所有者、NewInstigatorは実際操作しているプレイヤーレベルの所有者。
	void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator);
	// P149.武器を装備した後、ホバリング時のFXをキャンセルする。
	void DeactivateEmbers();
	// P113.武器を装備した後、Overlapping判定用Sphereを閉じる。
	void DisableSphereCollision();
	// P113.武器を装備時の音声をプレイする。
	void PlayEquipSound();
	// P112.武器を指定されたInParent（武器の所有者）のInSocketNameにAttachする。
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);
	// P131.開放された当たり判定用ボリュームとの衝突判定が発生したオブジェクト保存用配列。
	TArray<AActor*> IgnoreActors;

	
	/**
	* Getter & Setter
	*/
	// P121.Getter: Get private member attribute WeaponBox.
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; };

	
protected:
	/** <AItem> */
	// P119
	virtual void BeginPlay() override;
	// P90
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	// P90
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	/** </AItem> */

	
	// P119.武器の当たり判定用ボリューム。
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// P183.武器の当たり判定が発生した時、対象がエネミーかどうかを判断する。
	// yes: true, no: false.
	bool ActorIsSameType(AActor* OtherActor);
	// P183.GetHitメソッドを実行する。
	void ExecuteGetHit(FHitResult& BoxHit);
	
	// P138.当たり判定が発生した位置にFieldSystemを実例化する事で、scene componentに破壊を与える。
	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);


private:
	// P183.Box Traceを初期化して、Box Hitをcall backし当たり判定に使う。
	void BoxTrace(FHitResult& BoxHit);
	
	// P183.BoxTraceする時、Boxのdefault size.
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	FVector BoxTraceExtent = FVector(5.f);
	
	// P183.BoxTraceする時、DebugBoxを見せるかどうか、default = false.
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	bool bShowDebugBox = false;

	// P113.武器装備時の音声、エディタから代入。
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	USoundBase* EquipSound;
	
	// P117.当たり判定用ボリューム。
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	UBoxComponent* WeaponBox;
	
	// P119.Box Traceの出発点。
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;
	
	// P119.Box Traceの終点。
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd;

	// P155.武器のダメージ。
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	float Damage = 20.f;

};
