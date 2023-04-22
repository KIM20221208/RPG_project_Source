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

	// P123.定义 Enemy 类的胶囊组件忽略“摄像机”
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	/*
	* 组件相关初始化
	*/
	// P151.使用模板函数初始化 本地组件 UAttributeComponent
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	// P158.access the attribute to see whether the character is alive, true: Play Hit React Montage, false: Play Death Montage
	if (IsAlive() && Hitter)
	{
		// P189.modified the input-parameter
		DirectionalHitReact(Hitter->GetActorLocation());

	}
	else
	{
		Die();

	}

	// P189 debugged，can't disable the weapon box collision, get hit when attacking：disable the weapon box collision when get hit
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
	return Attributes && Attributes->IsAlive();;
}

void AMyCharacter::DisableCapsule()
{
	// P160.在死亡时设置胶囊体组件为“无碰撞”
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

int32 AMyCharacter::PlayAttackMontage()
{
	return PlayRandomMontageSection(AttackMontage, AttackMontageSections);

}

int32 AMyCharacter::PlayDeathMontage()
{
	const int32 Selection = PlayRandomMontageSection(DeathMontage, DeathMontageSections);
	// P180.模板函数：把枚举类型转换为 byte 类型
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
	// P202.Add a Tag if the character is dead, let Enemy stop attacking if they checked this tag
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
	/*
	* 判断被攻击判定到的点在角色的相对位置，获取与角色正面朝向的相对角度
	*/
	// P128.获取角色朝向前方的向量
	const FVector Forward = GetActorForwardVector();
	// P128.Lower Impact Point to the Enemy's Actor Location Z
	const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	// P128.获取从角色位置到被攻击判定到的点之间的向量，GetSafeNormal() 返回标准化后的单位向量
	const FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();
	// P128.计算两个向量之间的夹角的角度（标量积）。Forard * ToHit = |Forward| * |ToHit| * cos(theta) , |Forward| = 1 & |ToHit| = 1 so Forard * ToHit = cos(theta)
	const double CosTheta = FVector::DotProduct(Forward, ToHit);
	// P128.Take the inverse cosine(arc-cosine) of cos(theta) to get theta
	double Theta = FMath::Acos(CosTheta);
	// P128.Convert radians to degrees
	Theta = FMath::RadiansToDegrees(Theta);
	// P129.计算向量积（虚幻的算法使用的时左手法则，与右手法则相反）。if CrossProduct points down, theta should be negative
	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);

	// P129.用来判断受到攻击的方向（左 / 右），并更新Theta，向上（从右边受到攻击）为正，向下（从左边受到攻击）为负
	if (CrossProduct.Z < 0)
	{
		Theta *= -1.f;
	}

	/*
	* Play Animation Montage
	*/
	// P130.默认播放的动画蒙太奇为 "FromBack"
	FName Section("FromBack");

	// P130.判断 Theta 的值来播放动画蒙太奇
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

	/*
	* 绘制一些debuf stuff
	// P128.调用 UKismetSystemLibrary 中的 DrawDebugArrow 函数，画出与角色朝向的向量与被攻击判定的向量正交的向量
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + CrossProduct * 100.f, 5.f, FColor::Blue, 5.f);


	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("Theta : %f"), Theta));
	}

	// P128.调用 UKismetSystemLibrary 中的 DrawDebugArrow 函数，画出敌人正面朝向的箭头
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + Forward * 60.f, 5.f, FColor::Red, 5.f);
	// P128.调用 UKismetSystemLibrary 中的 DrawDebugArrow 函数，画出从敌人位置到发生攻击判定朝向的箭头
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + ToHit * 60.f, 5.f, FColor::Red, 5.f);
	*/
}

void AMyCharacter::PlayHitSound(const FVector& ImpactPoint)
{
	// P132.在播放遭受攻击的动画蒙太奇后播放音效
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, ImpactPoint);

	}

}

void AMyCharacter::SpawnHitParticles(const FVector& ImpactPoint)
{// P133.在播放被打击音效后播放粒子效果
	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, ImpactPoint);

	}

}

void AMyCharacter::HandleDamage(float DamageAmount)
{
	// P155.调用 UArrtributeComponent 类中的 ReceiveDamage 成员函数更新生命值
	if (Attributes)
	{
		Attributes->ReceiveDamage(DamageAmount);
		/*
		// P154.调用 UHealthBarComponent 类中的 SetHealthPercent 成员函数 设置角色血量，调用GetHealthPercent 成员函数 更新角色血量
		HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
		*/
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
		// P103.跳转到相应蒙太奇片段
		AnimInstance->Montage_JumpToSection(SectionName, Montage);

	}

}

int32 AMyCharacter::PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames)
{
	// P180.随机播放 攻击动画蒙太奇
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
		// P131.在收到“关闭碰撞”通知后把保存本次接触到后忽略的类的动态数组清零
		EquippedWeapon->IgnoreActors.Empty();

	}

}

