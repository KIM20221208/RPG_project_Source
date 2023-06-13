// Fill out your copyright notice in the Description page of Project Settings.


#include "Itmes/Treasures/Treasure.h"
#include "Interfaces/PickupInterface.h"

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	// P143.キャラが本クラスと衝突したら、キャラが持っているGold量を更新して本クラスを削除する。
	if (PickupInterface)
	{
		PickupInterface->AddGold(this);
		SpawnPickupSound();
		Destroy();
		
	}

}
