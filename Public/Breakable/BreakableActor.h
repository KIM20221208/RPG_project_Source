// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

class UGeometryCollectionComponent;
class ATreasure;
class UCapsuleComponent;

/**
 * 破壊可能なオブジェクトのバースクラス。
 */

UCLASS()
class RPG_PROJECT_API ABreakableActor : public AActor, public IHitInterface
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ABreakableActor();
	
	/** <AActor> */
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** </AActor> */

	/** <IHitInterface> */
	// P139
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/** </IHitInterface> */
	
	
protected:
	/** <AActor> */
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** </AActor> */

	// P145.オブジエンドが環境との衝突判定用ボリューム。
	// 破壊された後の破片の為、MeshをPawnクラスをIgnoreするように設定したため、キャラが破壊された以前のMeshとの衝突判定の為設定する。
	// For do not let player penetrate this class, before broken.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Capsule;

	
private:
	// P139.オブジェクトの破壊される形（エディタから作成）、エディタから代入。
	UPROPERTY(VisibleAnywhere)
	UGeometryCollectionComponent* GeometryCollection;
	
	/**
	 *方法1：UClass* 
	 *方法2：TSubclassOf<ClassTypeXXX> Template内のクラスによって継承できた派生クラスまで保存出来る。
	 */
	// P145.破壊された後に生成される宝物の保存用動的配列。
	// P146.元のTSubclassOf<ATreasure>をTArray<TSubclassOf<ATreasure>>に修正、エディタから代入。
	UPROPERTY(EditAnywhere, Category = "Breakable Properties")
	TArray<TSubclassOf<ATreasure>> TreasureClasses;

	// P147.破壊されているかを判断する、一回だけ破壊出来る。
	bool bBroken = false;

};
