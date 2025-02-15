// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KeeperCharacter.h"

#include "Character/KeeperCharacterController.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Monster/MonsterBase.h"
#include "Animation/AnimInstance.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "DamageField_Base.h"
#include "DrawDebugHelpers.h" // 디버깅
#include "Components/SphereComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//#include "Skill/SkillData.h"
#include "Skill/SkillComponent.h"

// Sets default values
AKeeperCharacter::AKeeperCharacter()
{
	bComboAttackDown = false;
	bComboAttacking = false;
	bComboAttackNext = false;
	ComboAttackNumber = 0;

	bIsDodging = false;
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = 1600.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-30.0f, 45.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	CameraComponent->bUsePawnControlRotation = false;

	CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);

	CameraComponent->SetOrthoWidth(2048.0f);

	// 무기 메시 컴포넌트
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh(), FName("WeaponSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//------------------스탯 초기화------------------
	Level = 1;				// 레벨
	Exp = 0;				// 경험치
	AttackPower = 100;		// 기본 공격력
	Defense = 100;			// 기본 방어력
	MaxHP = 1000;			// 기본 최대 HP
	CurrentHP = MaxHP;		// 시작 시 현재 HP는 최대 HP로 설정
	MaxMadness = 100;		// 기본 최대 광기
	CurrentMadness = 0;		// 시작 시 현재 광기는 0으로 설정
	MovementSpeed = 600;	// 기본 이동 속도
	//------------------------------------------------

	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;

	DamageRadius = 50.0f;  // 기본 데미지 반경 설정
	DamageField = nullptr;

	DodgeDistance = 6000.0f;
	
	//------------------스킬 사용 관련------------------
	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("Skill"));

	SkillCooldownHandle.Add(ESkillKeyMapping::Q);
	SkillCooldownHandle.Add(ESkillKeyMapping::W);
	SkillCooldownHandle.Add(ESkillKeyMapping::E);
	SkillCooldownHandle.Add(ESkillKeyMapping::R);
	//-------------------------------------------------
}

void AKeeperCharacter::BeginPlay()
{
	Super::BeginPlay();

	bIsAttacking = false;
	bIsDodging = false;
	bIsHitReacting = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	//CreateDamageField();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

void AKeeperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKeeperCharacter::TraceWeapon()
{

}

void AKeeperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	check(PlayerInputComponent);
}

bool AKeeperCharacter::CanMove() const
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying()) return false;
	if (bIsAttacking || bIsDodging || bIsHitReacting) return false;
    
	return true;
}

void AKeeperCharacter::CreateDamageField()
{
	if (!DamageField)
	{
		DamageField = GetWorld()->SpawnActor<ADamageField_Base>(ADamageField_Base::StaticClass(), GetActorLocation(), GetActorRotation());
		DamageField->CreateDamageField_Sphere(DamageRadius);
		DamageField->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void AKeeperCharacter::AttackDown()
{
	// 이동 중 캐릭터 공격 제어
	GetCharacterMovement()->StopActiveMovement();
	
	//UE_LOG(LogTemp, Warning, TEXT("AttackDown 함수 실행"));
	bComboAttackDown = true;

	if (bComboAttacking == false)
	{
		Attack(CurrentTarget);
	}
	else if (bComboAttacking == true)
	{
		bComboAttackNext = true;
	}
}

void AKeeperCharacter::AttackUp()
{
	bComboAttackDown = false;
}

void AKeeperCharacter::Attack(ACharacter* Monster)
{
	//UE_LOG(LogTemp, Warning, TEXT("Attack 함수 실행"));
	bComboAttackDown = true;

	UAnimInstance* AnimaInstance = GetMesh()->GetAnimInstance();

	if (!AnimaInstance || !comboMontage) return;

	bComboAttacking = true;
	const char* comboList[] = { "combo1", "combo2", "combo3", "combo4"};

	if (ComboAttackNumber >= 4)
		ComboAttackNumber = 0;
	//UE_LOG(LogTemp, Warning, TEXT("ComboAttack%d 실행"), ComboAttackNumber);

	AnimaInstance->Montage_Play(comboMontage, 1.5f);
	AnimaInstance->Montage_JumpToSection(FName(comboList[ComboAttackNumber]), comboMontage);
	
	if (DamageField)
	{
		DamageField->SetDamageAmount(AttackPower);
		DamageField->ActivateDamage();
	}

}

void AKeeperCharacter::AttackEnd()
{
	//UE_LOG(LogTemp, Warning, TEXT("ComboAttackEnd 함수 실행"));
	bComboAttacking = false;
	ComboAttackNumber = 0;
}

void AKeeperCharacter::AttackCheck()
{
	//UE_LOG(LogTemp, Warning, TEXT("ComboAttackCheck �Լ� ... "));

	if (bComboAttackNext == true)
	{
		ComboAttackNumber += 1;
		bComboAttackNext = false;
		Attack(CurrentTarget);
	}
}

void AKeeperCharacter::Die()
{
    if (bIsDead)
        return;
        
    bIsDead = true;
	GetCharacterMovement()->StopMovementImmediately();

	AttackReset();
	bIsDodging = false;
	bIsHitReacting = false;
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		DisableInput(PlayerController);
	}

	if (DeathMontage && GetMesh()->GetAnimInstance())
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->StopAllMontages(0.1f);
		AnimInstance->Montage_Play(DeathMontage);
	}

	if (DeathWidgetClass)
	{
		UUserWidget* DeathWidget = CreateWidget<UUserWidget>(GetWorld(), DeathWidgetClass);
		if (DeathWidget)
		{
			DeathWidget->AddToViewport();
		}
	}
}

void AKeeperCharacter::OnHitMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == HitMontage)
	{
		bIsHitReacting = false;

		AttackReset();
		
		if (USkeletalMeshComponent* MeshComponent = GetMesh())
		{
			if (UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance())
			{
				AnimInstance->OnMontageEnded.RemoveDynamic(this, &AKeeperCharacter::OnHitMontageEnded);
			}
		}
	}
}

void AKeeperCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == comboMontage)
	{
		bIsAttacking = false;
		
		if (USkeletalMeshComponent* MeshComponent = GetMesh())
		{
			if (UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance())
			{
				AnimInstance->OnMontageEnded.RemoveDynamic(this, &AKeeperCharacter::OnAttackMontageEnded);
			}
		}
	}
}

void AKeeperCharacter::AttackReset()
{
	bComboAttacking = false;
	bComboAttackNext = false;
	bComboAttackDown = false;
	ComboAttackNumber = 0;
	bIsAttacking = false;
}

void AKeeperCharacter::PlayHitAnimation()
{
	if (HitMontage)
	{
		USkeletalMeshComponent* MeshComponent = GetMesh();
		GetCharacterMovement()->StopMovementImmediately();
		
		if (MeshComponent)
		{
			UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance();
			
			if (AnimInstance)
			{
				AnimInstance->OnMontageEnded.RemoveDynamic(this, &AKeeperCharacter::OnAttackMontageEnded);
				AnimInstance->OnMontageEnded.AddDynamic(this, &AKeeperCharacter::OnHitMontageEnded);
                
				// 현재 진행 중인 몽타주 중단
				AnimInstance->StopAllMontages(0.1f);
                
				// 피격 몽타주 재생
				AnimInstance->Montage_Play(HitMontage);
			}
		}
	}
}


void AKeeperCharacter::ExecuteDodge()
{
	if (bIsDodging || bIsAttacking || bIsHitReacting)
		return;

	if (DodgeMontage)
	{
		bIsDodging = true;
		AttackReset();
       
		UCharacterMovementComponent* MovementComp = GetCharacterMovement();
		MovementComp->StopMovementImmediately();
		MovementComp->BrakingFriction = 0.0f;
		MovementComp->GravityScale = 0.0f;
       
		FVector DodgeVector = GetActorForwardVector();
		DodgeVector.Normalize();
		
		FHitResult SurfaceHit;
		FVector Start = GetActorLocation();
		FVector End = Start - FVector::UpVector * 200.0f;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByChannel(SurfaceHit, Start, End, ECC_Visibility, QueryParams))
		{
			FVector SurfaceNormal = SurfaceHit.Normal;
			FVector ProjectedDodge = FVector::VectorPlaneProject(DodgeVector, SurfaceNormal);
			ProjectedDodge.Normalize();
			DodgeVector = ProjectedDodge;
		}
		
		float DodgeTime = DodgeMontage->GetPlayLength();
		FVector RequiredVelocity = (DodgeVector * DodgeDistance) / DodgeTime;

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->OnMontageEnded.AddDynamic(this, &AKeeperCharacter::OnDodgeMontageEnded);
			AnimInstance->Montage_Play(DodgeMontage);
           
			MovementComp->Velocity = RequiredVelocity;
		}
	}
}

void AKeeperCharacter::OnDodgeMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == DodgeMontage)
	{
		bIsDodging = false;
       
		UCharacterMovementComponent* MovementComp = GetCharacterMovement();
		MovementComp->Velocity = FVector::ZeroVector;
		MovementComp->StopMovementImmediately();
		MovementComp->BrakingFriction = MovementComp->BrakingFrictionFactor;
		MovementComp->GravityScale = 1.0f;
       
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->OnMontageEnded.RemoveDynamic(this, &AKeeperCharacter::OnDodgeMontageEnded);
		}
	}
}

void AKeeperCharacter::TakeDamage(float DamageAmount/*, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser*/)
{
	if (bIsDead || bIsDodging)
		return;
	
	float ActualDamage = DamageCalculation(DamageAmount);
	CurrentHP = FMath::Max(0.0f, CurrentHP - ActualDamage);
	OnStatChanged.Execute();

	UE_LOG(LogTemp, Warning, TEXT("Damage %f applied to Hue"), ActualDamage);
	
	if (CurrentHP <= 0.0f)
	{
		//bIsDead = true;
		Die();
		return;
	}

	if (!bIsHitReacting)
	{
		bIsHitReacting = true;
		PlayHitAnimation();
	}
}

float AKeeperCharacter::DamageCalculation(float DamageAmount) const
{
	float ActualDamage = FMath::Max(0.0f, DamageAmount - Defense);
	
	return ActualDamage;
}

void AKeeperCharacter::DealDamage(ACharacter* Monster, float DamageAmount)
{
	AMonsterBase* MonsterTarget = Cast<AMonsterBase>(Monster);
	if (MonsterTarget && DamageAmount > 0.0f)
	{
		MonsterTarget->TakeDamage(DamageAmount);
		//UE_LOG(LogTemp, Warning, TEXT("Dealt %f damage to %s"), DamageAmount, *Monster->GetName());
	}
}

void AKeeperCharacter::IncreasedMadness(float MadnessCost)
{
	CurrentMadness = FMath::Min(MaxMadness, CurrentMadness + MadnessCost);
	OnStatChanged.Execute();
	
	if (CurrentMadness >= MaxMadness)
	{
		Die();
		return;
	}
}

void AKeeperCharacter::ModifyMovementSpeed(float SpeedModifier)
{
	MovementSpeed = FMath::Max(0.0f, MovementSpeed + SpeedModifier);
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

//------------------스킬 사용 관련------------------

FSkillDataStruct AKeeperCharacter::FindSkillDataWithMappingKey(ESkillKeyMapping Key)
{
	return SkillComponent->Skills[Key];
}

void AKeeperCharacter::ActivateSkill(ESkillKeyMapping Key)
{
	if (!SkillComponent->Skills[Key].IsCooldown())
	{
		SkillComponent->Skills[Key].Use(this);
		SkillComponent->Skills[Key].StartCooldown();
		float SkillCooldownRate = SkillComponent->Skills[Key].SecondToCooldown;

		FTimerDelegate CooldownDelegate = FTimerDelegate::CreateUFunction(
			this,
			FName("CooldownSkill"),
			Key
		);
		StartCooldown.Execute(Key);
		GetWorldTimerManager().SetTimer(SkillCooldownHandle[Key], CooldownDelegate, SkillCooldownRate, false);
	}
	else UE_LOG(LogTemp, Warning, TEXT("%d Skill is Cooldown"), Key);
}

void AKeeperCharacter::CooldownSkill(ESkillKeyMapping Key)
{
	if (SkillComponent->Skills[Key].IsCooldown())
	{
		GetWorldTimerManager().ClearTimer(SkillCooldownHandle[Key]);
		SkillComponent->Skills[Key].EndCooldown();
	}
}

