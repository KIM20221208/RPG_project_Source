// Fill out your copyright notice in the Description page of Project Settings.
 

#include "Breakable/BreakableActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Itmes/Treasures/Treasure.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABreakableActor::ABreakableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// P139.このクラスはフレームごとにcallされるメンバーがないので、フレームごとにcallされる機能をfalseに設定する。
	PrimaryActorTick.bCanEverTick = false;

	/**
	* Componentの作成及び初期設定。
	*/
	// P139
	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	SetRootComponent(GeometryCollection);
	GeometryCollection->SetGenerateOverlapEvents(true);
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	// P145.破壊された後の破片がプレイヤーの移動を邪魔しないように、PawnクラスをIgnoreするように設定する。
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	// P145
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(GetRootComponent());
	// P145.Collision presetをPawnクラス以外全部Ignoreするように設定する。
	Capsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

}

// Called when the game starts or when spawned
void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakableActor::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	// P147.当たり判定は一回だけ行う。
	if (bBroken) return;
	bBroken = true;

	// オブジェクトが破壊された後、宝物を生成する。
	UWorld* World = GetWorld();
	if (World && TreasureClasses.Num() > 0)
	{
		// P145.オブジェクトのZ軸の+75.fの位置に宝物を生成する。
		FVector Location = GetActorLocation();
		Location.Z += 75.f;
		// P146.TreasureClassesからランダムに一つを選んで生成する。
		const int32 Selection = FMath::RandRange(0, TreasureClasses.Num() - 1);
		// P145.宝物をWorldに生成する。
		World->SpawnActor<ATreasure>(TreasureClasses[Selection], Location, GetActorRotation());
		
	}

}

