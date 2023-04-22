// Fill out your copyright notice in the Description page of Project Settings.


#include "Itmes/Weapons/Weapon.h"
#include "Characters/RPG_projectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/HitInterface.h"
#include "NiagaraComponent.h"

AWeapon::AWeapon()
{
	// P117.使用 Factory Function 定义默认盒体组件
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	WeaponBox->SetupAttachment(GetRootComponent());
	// P119.为WeaponBox设定碰撞模式，默认为“无碰撞”，只在攻击动画蒙太奇通知为“在攻击”时为“有碰撞”
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// P119.为WeaponBox设定碰撞响应，除了 Pawn 以外重叠所有
	WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	// P119. 使用 Factory Function 初始化 BoxTraceStart 成员函数，并添加到根组件下
	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	BoxTraceStart->SetupAttachment(GetRootComponent());
	// P119. 使用 Factory Function 初始化 BoxTraceEnd 成员函数，并添加到根组件下
	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	// P119. 调用原始盒体组件中的“OnComponentBeginOverlap”成员函数的“AddDynamic”函数宏，用来添加函数到“OnBoxOverlap”deligate
	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
	
}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator)
{
	// P106.当物品被交互，改变它的物品状态
	ItemState = EItemState::EIS_Equipped;
	// P155.设置该武器新的持有者
	SetOwner(NewOwner);
	SetInstigator(NewInstigator);
	AttachMeshToSocket(InParent, InSocketName);
	DisableSphereCollision();
	PlayEquipSound();
	DeactivateEmbers();

}

void AWeapon::DeactivateEmbers()
{
	if (ItemEffect)
	{
		ItemEffect->Deactivate();
	}
}

void AWeapon::DisableSphereCollision()
{
	if (Sphere)
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AWeapon::PlayEquipSound()
{
	if (EquipSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, EquipSound, GetActorLocation());
	}
}

void AWeapon::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	// P96.调用静态网格体组件中的 “依附到组件 (AttachToComponent)”函数
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	/*
	// P95.把与球体重叠时返回的Actor类型转换到 ARPG_projectCharacter ，也就是判断重叠的Actor是否是主角
	*ARPG_projectCharacter* RPG_projectCharacter = Cast<ARPG_projectCharacter>(OtherActor);
	*if (RPG_projectCharacter)
	*{
	*	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	*	ItemMesh->AttachToComponent(RPG_projectCharacter->GetMesh(), TransformRules, TEXT("RightHandSocket"));
	*}
	*/
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// P183.由类的 Tag 检查武器持有者和发生攻击判定的是否同为 “Enemy”，避免敌人之间互相攻击
	if (ActorIsSameType(OtherActor)) return;

	// P119.定义用于接收 BoxTraceSingle 成员函数输出的 OutHit，使用 OnBoxOverlap 函数的 callback 时 无法返回发生判定的精确位置，只会返回被碰撞的 Actor 的位置
	FHitResult BoxHit;
	BoxTrace(BoxHit);

	// P125.如果盒体组件发生了碰撞
	if (BoxHit.GetActor())
	{
		// P183.由类的 Tag 检查武器持有者和发生攻击判定的是否同为 “Enemy”，避免敌人之间互相攻击
		if (ActorIsSameType(BoxHit.GetActor())) return;
		// P155.造成伤害，ApplyDamage 函数会call TakeDamage，TakeDamage 定义在 具体角色类
		UGameplayStatics::ApplyDamage(
			BoxHit.GetActor(),  // 此武器造成伤害的对象， i.e. 敌人，瓶瓶罐罐...
			Damage,
			GetInstigator()->GetController(),
			this,
			UDamageType::StaticClass()
		);
		ExecuteGetHit(BoxHit);
		CreateFields(BoxHit.ImpactPoint);

	}

}

bool AWeapon::ActorIsSameType(AActor* OtherActor)
{
	
	return GetOwner()->ActorHasTag(TEXT("Enemy")) && OtherActor->ActorHasTag(TEXT("Enemy"));
}

void AWeapon::ExecuteGetHit(FHitResult& BoxHit)
{
	// P125.判断攻击判定打到的是否为 IHitInterface 类(的基类之一，所以也算是判定为了Enemy类)
	IHitInterface* HitInterface = Cast<IHitInterface>(BoxHit.GetActor());
	// P125.如果攻击判定为 IHitInterface 类，则对相应成员函数传递向量
	if (HitInterface)
	{
		// P140.call GetHit_Implementation belong to BoxHit.GetActor()
		HitInterface->Execute_GetHit(BoxHit.GetActor(), BoxHit.ImpactPoint, GetOwner());
	}
}

void AWeapon::BoxTrace(FHitResult& BoxHit)
{
	// P119.确定盒体追踪的起始与终点向量
	const FVector Start = BoxTraceStart->GetComponentLocation();
	const FVector End = BoxTraceEnd->GetComponentLocation();
	// P119.定义一个可以存储 AActor* 类的动态数组，保存盒体碰撞要忽略的 Actor。P120.具体机制说明
	TArray<AActor*> ActorsToIgnore;
	// P119.把武器本身设定为忽略对象
	ActorsToIgnore.Add(this);
	// P189 时遇到的bug，在攻击时会有概率打到自己：在进行 BoxTrace 时把武器持有者加入到忽略碰撞名单
	ActorsToIgnore.Add(GetOwner());

	// P131.把本类中的成员变量 IgnoreActors 赋值给局部变量 ActorsToIgnore，用来判断是否要忽略 Actor。因为每次调用此函数时都会重新定义，所以每次开始时都只包含 this
	for (AActor* Actor : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actor);
	}

	// P119.定义“按通道进行盒体追踪”函数
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		BoxTraceExtent,
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		bShowDebugBox ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,  // P133.由 EDrawDebugTrace::ForDuration 修改
		BoxHit, // BoxHit 在这里被 call back
		true  // 是否忽略自身
	);
	IgnoreActors.AddUnique(BoxHit.GetActor());

}
