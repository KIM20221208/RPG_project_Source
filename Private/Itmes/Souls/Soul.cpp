 // Fill out your copyright notice in the Description page of Project Settings.


#include "Itmes/Souls/Soul.h"
#include "Interfaces/PickupInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void ASoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const double LocationZ = GetActorLocation().Z;
	if (LocationZ > DesiredZ)
	{
		const FVector DeltaLocation = FVector(0.f, 0.f, DriftRate * DeltaTime);
		AddActorWorldOffset(DeltaLocation);
	}
 	
}

void ASoul::BeginPlay()
{
	Super::BeginPlay();

	// P221.Start and End location of line trace, for spawning soul
	const FVector Start = GetActorLocation();
	const FVector End = Start - FVector(0.f, 0.f, 2000.f);
	// P221.
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Add(EObjectTypeQuery::ObjectTypeQuery1);
	// P221.
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	FHitResult HitResult;

	// P221.Start line trace for soul
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
	if (PickupInterface)
	{
		// P96.调用Setter函数赋值检测到的类指针给 RPG_projectCharacter 类的 OverlappingItem 成员变量
		PickupInterface->AddSoul(this);

		SpawnPickupSystem();
		SpawnPickupSound();
	
		// P206.Destroy soul actor after pickup
		Destroy();
		
	}
	
}
