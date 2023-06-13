// Fill out your copyright notice in the Description page of Project Settings.


#include "Itmes/Weapons/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/HitInterface.h"
#include "NiagaraComponent.h"

AWeapon::AWeapon()
{
	/**
	* Componentの作成及、初期設定
	*/
	// P117
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	WeaponBox->SetupAttachment(GetRootComponent());
	// P119.WeaponBoxのCollision preset、defaultは"No Collision"
	// ただエディタのAnimation Montageより、武器の所有者が攻撃行動をする時だで開放する
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	
	// P119
	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	BoxTraceStart->SetupAttachment(GetRootComponent());
	
	// P119
	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
	
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	// P119.调用原始盒体组件中的“OnComponentBeginOverlap”成员函数的“AddDynamic”函数宏，用来添加函数到“OnBoxOverlap”deligate
	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
	
}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator)
{
	// P106.武器が装備される時、武器の状態を変える
	ItemState = EItemState::EIS_Equipped;
	// P155.武器の所有者を設定する
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
	// P96
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
	
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// P183.エネミークラスのTagを判断する事で、エネミー間で当たり判定の発生を防ぐ。
	if (ActorIsSameType(OtherActor)) return;
	
	// P119.BoxTrace中のBoxTraceSingleがreturnするOutHit、
	//　OnBoxOverlapを使用する時、衝突判定が発生したActorの位置だけわかる。衝突判定が発生した正確な点の位置は得られない。
	FHitResult BoxHit;
	BoxTrace(BoxHit);

	// P125.衝突判定が発生した時。
	if (BoxHit.GetActor())
	{
		// P183.武器所有者のTagが"Enemy"かどうかを検査する事で、エネミー同士の当たり判定を防ぐ。
		if (ActorIsSameType(BoxHit.GetActor())) return;
		// P155.ダメージが発生する、ApplyDamageはTakeDamageをcallする、TakeDamageはキャラのクラスに定義されている。
		UGameplayStatics::ApplyDamage(
			BoxHit.GetActor(),  // この武器がダメージを与える対象（キャラ、ポット等）。
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
	// P125.武器が当たったActorがIHitInterface classかを判断する。
	// IHitInterfaceはAMyCharacter classの親クラスなので、これで当たったActorがキャラかを判断出来る。
	IHitInterface* HitInterface = Cast<IHitInterface>(BoxHit.GetActor());
	// P125.武器が当たったActorがIHitInterface classの時、GetHitメソッドを実行する。
	if (HitInterface)
	{
		// P140.call GetHit_Implementation belong to BoxHit.GetActor()
		HitInterface->Execute_GetHit(BoxHit.GetActor(), BoxHit.ImpactPoint, GetOwner());
		
	}
	
}

void AWeapon::BoxTrace(FHitResult& BoxHit)
{
	// P119.Box Traceの出発点。
	const FVector Start = BoxTraceStart->GetComponentLocation();
	// P119.Box Traceの終点。
	const FVector End = BoxTraceEnd->GetComponentLocation();
	// P119.Box TraceがIgnoreすべきActorを記録用AActor*保存用動的配列。
	TArray<AActor*> ActorsToIgnore;
	// P119.武器自体をIgnoreする。
	ActorsToIgnore.Add(this);
	// P189 Bug：攻撃時、時々自分が先ずダメージを受ける。
	// debug：武器の所有者をIgnoreする。
	ActorsToIgnore.Add(GetOwner());

	// P131.Weapon classのメンバーの動的配列IgnoreActorsの値をActorsToIgnoreに代入する、
	// 毎回の本メソッドがcallされる時に新たに定義されるため、始まりの時はthisしか無い。
	for (AActor* Actor : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actor);
		
	}

	// P119
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		BoxTraceExtent,
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		bShowDebugBox ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,  // P133.EDrawDebugTrace::ForDurationから修正
		BoxHit, // BoxHitはここでcallされる
		true  // 自分自身をIgnoreするか
	);
	IgnoreActors.AddUnique(BoxHit.GetActor());

}
