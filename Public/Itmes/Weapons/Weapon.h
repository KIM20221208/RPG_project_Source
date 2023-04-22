// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Itmes/Item.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;

/**
 * 继承自Item的子类，武器
 */
UCLASS()
class RPG_PROJECT_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	// P117.声明AWeapon构造函数
	AWeapon();
	// P96.声明 交互 成员函数，InParent 返回自要依附的类，InSocketName 为要依附的插口。P155.NewOwner 为该武器的实例层面的持有者，NewInstigator 为该武器的操作实例（玩家）层面的持有者
	void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator);
	// P149.在装备武器以后关掉附带的Niagara特效提示
	void DeactivateEmbers();
	// P113.
	void DisableSphereCollision();
	// P113.播放装备音效
	void PlayEquipSound();
	// P112.声明把武器类依附到指定插口的成员函数
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);
	// P131.声明一个动态数组，保存攻击判定需要忽略的 AActor* 类对象
	TArray<AActor*> IgnoreActors;

	/*
	* Getter & Setter
	*/
	// P121.返回私有成员变量 WeaponBox
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; };

protected:
	// P119.重写引用自Item的 BeginPlay 函数
	virtual void BeginPlay();
	// P90.重写引用自Item的“当与球体开始重叠”函数，UFUNCTION()具有继承性，如果在父类添加了，就不用再写
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	// P90.重写引用自Item的“当与球体结束重叠”函数，UFUNCTION()具有继承性，如果在父类添加了，就不用再写
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	// P119.声明“当与盒体开始重叠”的函数，如果有被子函数重写的需求，那么就要设为虚函数
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// P183.查看武器发生的攻击判定角色是否为 Enemy 类
	bool ActorIsSameType(AActor* OtherActor);
	// P183.执行GetHit 成员函数
	void ExecuteGetHit(FHitResult& BoxHit);
	
	// P138.声明在攻击判定发生的位置实例化 FieldSystem 的成员函数，对场景组件造成破坏
	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);


private:
	// P183.对盒体追踪进行初始化，并call back BoxHit 用作攻击判定
	void BoxTrace(FHitResult& BoxHit);
	// P183.BoxTrace 成员函数中定义“按通道进行盒体追踪”函数时的 “盒体” 的默认大小
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	FVector BoxTraceExtent = FVector(5.f);
	// P183.BoxTrace 成员函数中定义“按通道进行盒体追踪”函数时的 “显示” 的默认传参
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	bool bShowDebugBox = false;

	// P113.声明武器的装备声音
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	USoundBase* EquipSound;
	// P117.声明武器的攻击判定用的盒体组件
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	UBoxComponent* WeaponBox;
	// P119.声明一个场景组件，确定BoxTrace的起始点
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;
	// P119.声明一个场景组件，确定BoxTrace的终点
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd;

	// P155.声明武器伤害成员变量
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	float Damage = 20.f;

};
