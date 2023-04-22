// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

/**
* RPG_project中物品的基类
*/
// P87.前向声明
class USphereComponent;
class UNiagaraComponent;
class UNiagaraSystem;

// P106.声明判断物体状态的强类型枚举，枚举成员类型规定为 unsigned int 8
enum class EItemState : uint8
{
	EIS_Hovering,
	EIS_Equipped
};

UCLASS()
class RPG_PROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	/**
	* 物体按照三角函数来浮动
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// P51.正弦移动，振幅
	float Amplitude;
	// P51.正弦移动，移动频率
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeConstant;
	// P55.反射成员函数到UE5
	UFUNCTION(BlueprintPure)
	// 纯函数，返回Value * TimeConstant 的Sin值 * Amplitude
	float TransformedSin();
	// 纯函数，返回Value * TimeConstant 的Cosin值 * Amplitude
	UFUNCTION(BlueprintPure)
	float TransformedCos();

	// P56.创建模板函数，调用时必须指定数据类型
	template <typename T>
	T Avg(T First, T Second);

	
	/**
	* 体积碰撞
	*/
	// P87.声明与球体组件碰撞开始时的事件delegate，此处必须有 UFUNCTION() 才可以被绑定，因为函数的回调为 dynamic multicast delegate
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// P88.声明与球体组件碰撞结束时的事件delegate，此处必须有 UFUNCTION() 才可以被绑定，因为函数的回调为 dynamic multicast delegate
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// P207.Spawn a niagara system after on sphere overlap
	virtual void SpawnPickupSystem();
	// P207.
	virtual void SpawnPickupSound();
	
	/**
	* 其他
	*/
	// P58.声明静态网格体指针变量
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh;

	// P106.声明Item类默认的 ItemState 为悬浮
	EItemState ItemState = EItemState::EIS_Hovering;

	// P87.声明球体原始组件（Primitive Component）指针变量
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	// P149.声明 Niagara组件
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ItemEffect;

	// P207.Make a sound after pickup a soul
	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;

private:
	// P51.正弦移动，DeltaTime的累计值
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;
	
	// P206.Niagara system after pickup a soul
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* PickupFX;
	// P52 & P53 & P54.UPROPERTY(): 反射变量给UE5
		/* 
		* 可以传递多个参数
		* EditDefaultsOnly		: 只能在蓝图的Details pannel中编辑
		* EditInstanceOnly		: 只能在世界的实例中编辑
		* EditAnywhere			: 在蓝图的Details pannel与世界的实例中都可以编辑
		* VisibleDefaultOnly	: 仅在蓝图Details pannel中可见
		* VisibleInstanceOnly	: 仅在世界的实例中可见
		* VisibleAnywhere		: 在蓝图的Details pannel与世界的实例中都可见
		* BlueprintReadOnly		: 可以在蓝图中以只读的形式调用，但不能用在private成员
		* BlueprintReadWrite	: 可以在蓝图中以读写的形式调用，但不能用在private成员
		* Category = ""			: 可以自己新增在蓝图的Details pannel中显示的类型
		* BlueprintReadOnly / BlueprintReadWrite, meta = (AllowPrivateAccess = "true")	: 让private中的成员在蓝图中可见
		*/
	// P55 UFUNCTION(): 反射函数给UE5
		/*
		* BlueprintCallable		: 可以在蓝图中调用该函数
		* BlueprintPure			: 以纯函数（无传参，不会改变类中的成员变量）的形式调用该函数
		*/

};

template<typename T>
inline T AItem::Avg(T First, T Second)
{
	return (First + Second) / 2;

}
