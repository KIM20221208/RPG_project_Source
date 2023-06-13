// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

// P87.前方宣言。
class USphereComponent;
class UNiagaraComponent;
class UNiagaraSystem;

/**
 * 各種アイテムの親クラス。
 */

// P106.enumeration：アイテム状態判断用。
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
	
	/** <AActor> */
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** </AActor> */

	
protected:
	/** <AActor> */
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** </AActor> */
	
	/**
	 * 三角関数によるアイテムのホバリング。
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// P51.三角関数による移動、振幅。
	float Amplitude;
	// P51.三角関数による移動、頻度。
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeConstant;
	
	UFUNCTION(BlueprintPure)
	// アイテムがホバリング時、sin型で運動。
	float TransformedSin();
	
	// アイテムがホバリング時、cos型で運動。
	UFUNCTION(BlueprintPure)
	float TransformedCos();

	// P56.Template function: 使用時はデータタイプを指定する必要がある。
	template <typename T>
	T Avg(T First, T Second);

	
	/**
	 * Overlapping event
	 */
	// P87.オブジェクトがアイテムとOverlappingし始まった時（初めてアイテムを触る時）callされる。
	// UFUNCTION()が必要、UE5 APIのdynamic multicast delegateとバインドしてcallされる。
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// P88.オブジェクトがアイテムとOverlappingが終わる時（Overlapping状態からその前の状態に戻る時）callされる。
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// P207.niagara system：アイテムを拾うときプレイされるFX。
	virtual void SpawnPickupSystem();
	// P207.アイテムを拾うときプレイされる音声。
	virtual void SpawnPickupSound();
	

	// P106.アイテムの状態：デフォルトでホバリングと定義。
	EItemState ItemState = EItemState::EIS_Hovering;
	
	// P87.Overlapping判定用Sphere。
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;
	
	// P58.アイテムのモデル、エディタから代入。
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh;
	
	// P149.アイテムがホバリング状態時のFX、エディタから代入。
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ItemEffect;

	// P207.アイテムが拾われた時の音声、エディタから代入。
	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;

	
private:
	// P51.DeltaTimeを加算した変数、ホバリング時の振幅がフレーム数に影響させない為、動作環境によるDeltaTimeで計算する。
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;
	
	// P206.アイテムが拾われた時にプレイされるFX。
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* PickupFX;

};

template<typename T>
inline T AItem::Avg(T First, T Second)
{
	return (First + Second) / 2;

}
