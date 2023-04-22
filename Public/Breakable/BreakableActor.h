// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

class UGeometryCollectionComponent;
class ATreasure;
class UCapsuleComponent;

UCLASS()
class RPG_PROJECT_API ABreakableActor : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// P139.覆盖继承自 IHitInterface 的纯虚函数
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// P145.声明胶囊体组件，由于碎片原因设置了忽略Pawn类，防止角色穿透 BreakableActor 类
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Capsule;

private:
	// P139.声明几何集合组件，由蓝图赋值
	UPROPERTY(VisibleAnywhere)
	UGeometryCollectionComponent* GeometryCollection;

	// P145.从蓝图中赋值，返回在UE5中初始化了 StaticMesh 的子类的类。相当于反向反射？ 
	// P146.把原先的 TSubclassOf<ATreasure> 改成了 TArray<TSubclassOf<ATreasure>> ，在蓝图中可以初始化多个相似类，作为动态数组
	/*
	* 方法1：UClass* 
	* 方法2：TSubclassOf<ClassTypeXXX> 返回所有模板内类的子类，当然包括 蓝图类
	*/
	UPROPERTY(EditAnywhere, Category = "Breakable Properties")
	TArray<TSubclassOf<ATreasure>> TreasureClasses;

	// P147.声明 bool型成员变量，只进行一次被攻击判定
	bool bBroken = false;

};
