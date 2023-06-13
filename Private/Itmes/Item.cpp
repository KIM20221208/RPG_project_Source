// Fill out your copyright notice in the Description page of Project Settings.


#include "Itmes/Item.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "Interfaces/PickupInterface.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AItem::AItem() : Amplitude(0.25f), TimeConstant(5.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	/**
	 * Componentの作成及び初期設定。
	 */
	// P58
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	// P177
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// UE5's reflection mechanism has its own garbage collection function,
	// which will automatically close the pointer memory space that has not been called
	RootComponent = ItemMesh;
	
	// P87
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
	
	// P149
	ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers Effect"));
	ItemEffect->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	// P87."OnSphereOverlap"を"OnComponentBeginOverlap"にバインドする。
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	// P88.Bind "OnSphereEndOverlap"を"OnComponentEndOverlap"にバインドする。
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);

}

float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);

}

float AItem::TransformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);

}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// P96.アイテムとOverlappingし始めたオブジェクトがプレイヤーが否かを判断：
	// true: ARPG_projectCharacter.OverlappingItemに代入される。
	// false: nullptr。
	// P206.汎用性の為、ARPG_projectCharacterの代わりにIPickupInterfaceで判断する。
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(this);
	}

}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const FString OtherActorName = OtherActor->GetName();
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(nullptr);
	}

}

void AItem::SpawnPickupSystem()
{
	if (PickupFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, PickupFX, GetActorLocation());
	}
	
}

void AItem::SpawnPickupSound()
{
	if (PickupSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, PickupSound, GetActorLocation());
		
	}
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	// DletaTime: フレーム数の更新率、単位は秒。
	Super::Tick(DeltaTime);
	
	RunningTime += DeltaTime;

	// P106.アイテムをフレームごとにZ軸の値を偏移する事で、sin型にホバリングさせる。
	if (ItemState == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
	}
	
}
