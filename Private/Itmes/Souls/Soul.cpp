 // Fill out your copyright notice in the Description page of Project Settings.


#include "Itmes/Souls/Soul.h"
#include "Interfaces/PickupInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void ASoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	// Soulsが生成される位置のZ軸の値。
	const double LocationZ = GetActorLocation().Z;
	// Soulsが生成される位置より徐々に特定なスピードで地面まで落ちる。
	if (LocationZ > DesiredZ)
	{
		const FVector DeltaLocation = FVector(0.f, 0.f, DriftRate * DeltaTime);
		AddActorWorldOffset(DeltaLocation);
		
	}
 	
}

void ASoul::BeginPlay()
{
	Super::BeginPlay();

	// P221.Soulを生成する為、line traceの始まりの点と終点。
	const FVector Start = GetActorLocation();
	const FVector End = Start - FVector(0.f, 0.f, 2000.f);
	// P221
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Add(EObjectTypeQuery::ObjectTypeQuery1);
	// P221.Soulsのline traceはSoulsを生成した敵の死体をIgnoreする。
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	FHitResult HitResult;
	// P221.Start line trace for Soul.
	UKismetSystemLibrary::LineTraceSingleForObjects(
		this,
		Start,
		End,
		ObjectType,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true
		);
	DesiredZ = HitResult.ImpactPoint.Z + StopDriftFromLand;
	
}

void ASoul::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	// P206.キャラが本クラスと衝突したら、キャラが持っているSouls量を更新して本クラスを削除する。
	if (PickupInterface)
	{
		PickupInterface->AddSoul(this);
		SpawnPickupSystem();
		SpawnPickupSound();
		Destroy();
		
	}
	
}
