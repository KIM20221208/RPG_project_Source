// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Itmes/Weapons/Weapon.h"
#include "Components/AttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	/**
	* Componentの作成及、初期設定
	*/
	// P151
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
	// P123.キャラが環境との衝突判定用ボリュームがプレイヤーが操作しているキャラのカメラを"Ignore"するように設定する
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	// P158.先ずキャラが生きているからどうかを判断する、
	// true: Play Hit React Montage, false: Play Death Montage
	if (IsAlive() && Hitter)
	{
		// P189.当たり判定が発生した位置から被ダメージ動画をプレイする
		DirectionalHitReact(Hitter->GetActorLocation());

	}
	else
	{
		Die();

	}

	// P189 debugged：武器の当たり判定用ボリュームをclose出来ないbug
	// キャラが攻撃時攻撃される時：武器の当たり判定用ボリュームをcloseする
	SetWeaponCollisionEnabled(ECollisionEnabled::NoCollision);
	PlayHitSound(ImpactPoint);
	SpawnHitParticles(ImpactPoint);

}

void AMyCharacter::Attack()
{
	if (CombatTarget && CombatTarget->ActorHasTag(FName("Dead")))
	{
		CombatTarget = nullptr;
		
	}
	
}

bool AMyCharacter::IsAlive()
{
	return Attributes && Attributes->IsAlive();
	
}

void AMyCharacter::DisableCapsule()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

int32 AMyCharacter::PlayAttackMontage()
{
	return PlayRandomMontageSection(AttackMontage, AttackMontageSections);

}

int32 AMyCharacter::PlayDeathMontage()
{
	const int32 Selection = PlayRandomMontageSection(DeathMontage, DeathMontageSections);
	// P180
	TEnumAsByte<EDeathPose> Pose(Selection);
	if (Pose < EDeathPose::EDP_MAX)
	{
		DeathPose = Pose;

	}
	return Selection;
}

void AMyCharacter::PlayDodgeMontage()
{
	PlayMontageSection(DodgeMontage, FName("Default"));
	
}

void AMyCharacter::StopAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Stop(.25f, AttackMontage);
		
	}
	
}

void AMyCharacter::DisableMeshCollision()
{
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

bool AMyCharacter::CanAttack()
{
	return false;
	
}

void AMyCharacter::ActionEnd()
{

}

void AMyCharacter::Die_Implementation()
{
	// P202.キャラが死ぬときにTagを追加する、エネミーがこのTagを検出する時に攻撃を停止する
	Tags.Add("Dead");
	PlayDeathMontage();
	DisableMeshCollision();
	
}

void AMyCharacter::PlayHitReactMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HitReactMontage)
	{
		AnimInstance->Montage_Play(HitReactMontage);
		AnimInstance->Montage_JumpToSection(SectionName, HitReactMontage);
		
	}
	
}

void AMyCharacter::DirectionalHitReact(const FVector& ImpactPoint)
{
	/**
	* 当たり判定が発生した位置がキャラの正面向きとの相対的角度を求める
	*/
	// P128.キャラの向きを得る
	const FVector Forward = GetActorForwardVector();
	// P128.Lower Impact Point to the Enemy's Actor Location Z
	const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	// P128.キャラの位置と当たり判定が発生した位置間のベクトルを得る
	const FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();
	// P128.二つのベクトル間の角度を求める（vector product）
	// Forward * ToHit = |Forward| * |ToHit| * cos(theta) , |Forward| = 1 & |ToHit| = 1 so Forward * ToHit = cos(theta)
	const double CosTheta = FVector::DotProduct(Forward, ToHit);
	// P128.Take the inverse cosine(arc-cosine) of cos(theta) to get theta
	double Theta = FMath::Acos(CosTheta);
	// P128.Convert radians to degrees
	Theta = FMath::RadiansToDegrees(Theta);
	// P129.Calculate vector product（虚幻的算法使用的时左手法则，与右手法则相反）
	// if CrossProduct points down, theta should be negative
	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);

	// P129.攻撃された方向を判断する（左 / 右）、結果によってThetaを更新する
	// from upward(attacked from right): +, from downward(attacked from left)-
	if (CrossProduct.Z < 0)
	{
		Theta *= -1.f;
		
	}

	
	/**
	* Play Animation Montage
	*/
	// P130.defaultでプレイする被ダメージ動画は "FromBack"
	FName Section("FromBack");

	// P130.Thetaの値より、被ダメージ動画をプレイする
	if (Theta >= -45.f && Theta < 45.f)
	{
		Section = FName("FromFront");
		
	}
	else if (Theta >= -135.f && Theta < -45.f)
	{
		Section = FName("FromLeft");
		
	}
	else if (Theta >= 45.f && Theta < 135.f)
	{
		Section = FName("FromRight");
		
	}
	PlayHitReactMontage(Section);
	
}

void AMyCharacter::PlayHitSound(const FVector& ImpactPoint)
{
	// P132
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, ImpactPoint);

	}

}

void AMyCharacter::SpawnHitParticles(const FVector& ImpactPoint)
{
	// P133
	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, ImpactPoint);

	}

}

void AMyCharacter::HandleDamage(float DamageAmount)
{
	// P155.UArrtributeComponentクラスのReceiveDamage methodをcallして体力の値を更新する
	if (Attributes)
	{
		Attributes->ReceiveDamage(DamageAmount);

	}

}

FVector AMyCharacter::GetTranslationWarpTarget()
{
	if (CombatTarget == nullptr) return FVector();
	 
	const FVector CombatTargetLocation = CombatTarget->GetActorLocation();
	const FVector Location = GetActorLocation();

	// P192. return a normalized vector, direction is character to Combat target
	FVector TargetToMe = (Location - CombatTargetLocation).GetSafeNormal();
	TargetToMe *= WarpTargetDistance;

	return CombatTargetLocation + TargetToMe;
	
}

FVector AMyCharacter::GetRotationWarpTarget()
{
	if (CombatTarget)
	{
		return CombatTarget->GetActorLocation();
		
	}
	return FVector();
	
}

void AMyCharacter::PlayMontageSection(UAnimMontage* Montage, const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && Montage)
	{
		AnimInstance->Montage_Play(Montage);
		// P103
		AnimInstance->Montage_JumpToSection(SectionName, Montage);

	}

}

int32 AMyCharacter::PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames)
{
	if (SectionNames.Num() <= 0) return -1;
	const int32 MaxSectionIndex = SectionNames.Num() - 1;
	const int32 Selection = FMath::RandRange(0, MaxSectionIndex);
	PlayMontageSection(Montage, SectionNames[Selection]);
	return Selection;

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (EquippedWeapon && EquippedWeapon->GetWeaponBox())
	{
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		// P131.開放された当たり判定用ボリュームとの衝突判定が発生したオブジェクト保存用配列をemptyさせる
		EquippedWeapon->IgnoreActors.Empty();

	}

}

