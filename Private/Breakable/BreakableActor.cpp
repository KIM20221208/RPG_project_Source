// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakable/BreakableActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Itmes/Treasures/Treasure.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABreakableActor::ABreakableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;  // P139.由于可破坏类 暂时不需要 逐帧返回值，设置为false
	// P139.使用 Factory Function 定义默认几何集合组件，并设定为根组件
	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	SetRootComponent(GeometryCollection);
	// P139.初始化生成重叠事件为“真” 
	GeometryCollection->SetGenerateOverlapEvents(true);
	// P139.初始化为忽略相机
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	// P145.为了破坏后的碎片不阻挡角色，设置忽略 Pawn类
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	// P145.P139.使用 Factory Function 定义默认胶囊体组件，并依附到根组件
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(GetRootComponent());
	// P145.把碰撞预设设置为，除了 Pawn 类忽略所有
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
	// P147.只进行一次被攻击判定
	if (bBroken) return;
	bBroken = true;

	UWorld* World = GetWorld();
	if (World && TreasureClasses.Num() > 0)
	{
		// P145.把生成地点的z坐标抬高75点
		FVector Location = GetActorLocation();
		Location.Z += 75.f;

		// P146.从 TreasureClasses 里面随机抽取一个
		const int32 Selection = FMath::RandRange(0, TreasureClasses.Num() - 1);

		// P145.在 BreakableActor 类的相应地点生成 BP_Treasure 类
		World->SpawnActor<ATreasure>(TreasureClasses[Selection], Location, GetActorRotation());
		

	}

}

