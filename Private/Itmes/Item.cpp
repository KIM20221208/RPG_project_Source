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

	// P58.使用 Factory Function 构造默认静态网格体对象
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	// P177.把碰撞预设设置为“无碰撞”，并忽略所有类
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// UE5的反射机制自带垃圾回收功能，会自动关闭没有调用的指针内存空间
	RootComponent = ItemMesh;

	// P87.使用 Factory Function 初始化 Sphere 成员函数
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	// P149.使用 模板函数初始化 Niagara 组件，依附到根节点
	ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers Effect"));
	ItemEffect->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

/*
	// P39.输出 TEXT() 到 输出日志。
	UE_LOG(LogTemp, Warning, TEXT("Begin Play Called!"))

	// P40.判断是否为空指针，并且调用指向的类成员函数，显示字符串到Screen。
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, FString("Item On Screen Message!"));
	}

	//P47.改变Actor的坐标。
	SetActorLocation(FVector(0.f, 0.f, 200.f));

	//P48.旋转Actor。
	SetActorRotation(FRotator(0.f, 45.f, 0.f));

	//P42.画出DebugSphere，可视化没有Mesh的Actor。
	FVector Location = GetActorLocation();
	DRAW_SPHERE(Location)

	//P43.画出DebugLines，可视化Actor的移动方向。
	FVector Forward = GetActorForwardVector();
	DRAW_LINE(Location, Location + Forward * 100)

	//P44.画出DebugPoint, 可视化DebugLine的头尾。
	DRAW_POINT(Location + Forward * 100)


	//P44. 绘制DebugVector。
	FVector Forward = GetActorForwardVector();
	DRAW_VECTOR(Location, Location + Forward * 100)
*/
	// P87.调用原始球体组件中的“OnComponentBeginOverlap”成员函数的“AddDynamic”函数宏，用来添加函数到“OnSphereOverlap”deligate
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	// P88.调用原始球体组件中的“OnComponentEndOverlap”成员函数的“AddDynamic”函数宏，用来添加函数到“OnSphereOverlap”deligate
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
	// const FString OtherActorName = OtherActor->GetName();
	// need check GEngine first before use it
	// GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, OtherActorName);
	// P96.把重叠开始时检测到的 OtherActor 类型转换为 ARPG_projectCharacter 指针
	// P206.check IPickupInterface instead of ARPG_projectCharacter, make this function more general
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		// P96.调用Setter函数赋值检测到的类指针给 RPG_projectCharacter 类的 OverlappingItem 成员变量
		PickupInterface->SetOverlappingItem(this);
	}

}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const FString OtherActorName = OtherActor->GetName();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Blue, OtherActorName);
		// P96.把重叠结束时检测到的 OtherActor 类型转换为 ARPG_projectCharacter 指针
		IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
		if (PickupInterface)
		{
			// P96.调用Setter函数赋值空指针给 RPG_projectCharacter 类的 OverlappingItem 
			PickupInterface->SetOverlappingItem(nullptr);
		}
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
	// DletaTime: 帧数更新频率，单位为秒。即，与帧数成反比。
	Super::Tick(DeltaTime);
	
/*
	// P41.逐帧显示字符串到 输出日志。
	UE_LOG(LogTemp, Warning, TEXT("The DeltaTime is: %f"), DeltaTime);

	// P41.逐帧显示字符串到 输出到Screen。
	if (GEngine)
	{
		FString Name = GetName();
		FString Message = FString::Printf(TEXT("The Itme is: %s"), *Name);
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, Message);
		UE_LOG(LogTemp, Warning, TEXT("The DeltaTime is: %s"),*Name);
	}

	//P49.逐帧更新Actor坐标，并旋转。
	float MovementRate = 50.f;
	float RotationRate = 45.f;

	AddActorWorldOffset(FVector(MovementRate * DeltaTime, 0.f, 0.f));
	AddActorWorldRotation(FRotator(RotationRate * DeltaTime, 0.f, 0.f));

	DRAW_SPHERE_SINGLEFRAME(GetActorLocation())
	DRAW_VECTOR_SINGLEFRAME(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100)

	// P51.正弦移动
	float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);
	AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));

	// P56.调用模板函数
	FVector AvgVector = Avg<FVector>(GetActorLocation(), FVector::ZeroVector);
	DRAW_POINT_SINGLEFRAME(AvgVector)
*/
	
	RunningTime += DeltaTime;

	// P106.
	if (ItemState == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
	}
	
}
