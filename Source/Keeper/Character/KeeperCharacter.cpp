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

#include "Animation/AnimBlueprint.h"
#include "Animation/AnimMontage.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"

#include "Skill/SkillComponent.h"

// Sets default values
AKeeperCharacter::AKeeperCharacter()
{
	bComboAttackDown = false;
	bComboAttacking = false;
	bComboAttackNext = false;
	ComboAttackNumber = 0;

	bIsDodging = false;
	bIsHitting = false;
	
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
	
    CommonAnimBlueprintListBySkillSet.Add(ESkillSetType::Defalut, nullptr);
    CommonAnimBlueprintListBySkillSet.Add(ESkillSetType::Beast, nullptr);
    CommonAnimBlueprintListBySkillSet.Add(ESkillSetType::Mirror, nullptr);
    CommonAnimBlueprintListBySkillSet.Add(ESkillSetType::Puppet, nullptr);
    CommonAnimBlueprintListBySkillSet.Add(ESkillSetType::Dream, nullptr);

    ComboMontageListBySkillSet.Add(ESkillSetType::Defalut, nullptr);
    ComboMontageListBySkillSet.Add(ESkillSetType::Beast, nullptr);
    ComboMontageListBySkillSet.Add(ESkillSetType::Mirror, nullptr);
    ComboMontageListBySkillSet.Add(ESkillSetType::Puppet, nullptr);
    ComboMontageListBySkillSet.Add(ESkillSetType::Dream, nullptr);

    HitMontageListBySkillSet.Add(ESkillSetType::Defalut, nullptr);
    HitMontageListBySkillSet.Add(ESkillSetType::Beast, nullptr);
    HitMontageListBySkillSet.Add(ESkillSetType::Mirror, nullptr);
    HitMontageListBySkillSet.Add(ESkillSetType::Puppet, nullptr);
    HitMontageListBySkillSet.Add(ESkillSetType::Dream, nullptr);

    DodgeMontageListBySkillSet.Add(ESkillSetType::Defalut, nullptr);
    DodgeMontageListBySkillSet.Add(ESkillSetType::Beast, nullptr);
    DodgeMontageListBySkillSet.Add(ESkillSetType::Mirror, nullptr);
    DodgeMontageListBySkillSet.Add(ESkillSetType::Puppet, nullptr);
    DodgeMontageListBySkillSet.Add(ESkillSetType::Dream, nullptr);

    DeathMontageListBySkillSet.Add(ESkillSetType::Defalut, nullptr);
    DeathMontageListBySkillSet.Add(ESkillSetType::Beast, nullptr);
    DeathMontageListBySkillSet.Add(ESkillSetType::Mirror, nullptr);
    DeathMontageListBySkillSet.Add(ESkillSetType::Puppet, nullptr);
    DeathMontageListBySkillSet.Add(ESkillSetType::Dream, nullptr);

    WeaponMeshListBySkillSet.Add(ESkillSetType::Defalut, nullptr);
    WeaponMeshListBySkillSet.Add(ESkillSetType::Beast, nullptr);
    WeaponMeshListBySkillSet.Add(ESkillSetType::Mirror, nullptr);
    WeaponMeshListBySkillSet.Add(ESkillSetType::Puppet, nullptr);
    WeaponMeshListBySkillSet.Add(ESkillSetType::Dream, nullptr);
	
    
	// 애니메이션 관련 요소 초기화
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> DefaultABPRef(TEXT("/Script/Engine.AnimBlueprint'/Game/Asset/CharacterHue/HueAnim/Blueprint/ABP_Hue.ABP_Hue'"));
	if(DefaultABPRef.Succeeded()) CommonAnimBlueprintListBySkillSet[ESkillSetType::Defalut] = DefaultABPRef.Object;
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> BeastABPRef(TEXT("/Script/Engine.AnimBlueprint'/Game/Asset/CharacterHue/HueAnim/Blueprint/ABP_Hue_Beast.ABP_Hue_Beast'"));
	if(BeastABPRef.Succeeded()) CommonAnimBlueprintListBySkillSet[ESkillSetType::Beast] = BeastABPRef.Object;

	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboDefaultAMRef(TEXT("/Script/Engine.AnimMontage'/Game/Asset/CharacterHue/HueAnim/HueAnimMontage/AM_Hue_Combo.AM_Hue_Combo'"));
	if (ComboDefaultAMRef.Succeeded()) ComboMontageListBySkillSet.Add(ESkillSetType::Defalut, ComboDefaultAMRef.Object);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboBeastAMRef(TEXT("/Script/Engine.AnimMontage'/Game/Asset/CharacterHue/HueAnim/HueAnimMontage/AM_Hue_Combo_Beast.AM_Hue_Combo_Beast'"));
	if (ComboBeastAMRef.Succeeded()) ComboMontageListBySkillSet.Add(ESkillSetType::Beast, ComboBeastAMRef.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitDefaultAMRef(TEXT("/Script/Engine.AnimMontage'/Game/Asset/CharacterHue/HueAnim/HueAnimMontage/AM_Hue_Hit.AM_Hue_Hit'"));
	if (HitDefaultAMRef.Succeeded()) HitMontageListBySkillSet.Add(ESkillSetType::Defalut, HitDefaultAMRef.Object);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitBeastAMRef(TEXT("/Script/Engine.AnimMontage'/Game/Asset/CharacterHue/HueAnim/HueAnimMontage/AM_Hue_Hit_Beast.AM_Hue_Hit_Beast'"));
	if (HitBeastAMRef.Succeeded()) HitMontageListBySkillSet.Add(ESkillSetType::Beast, HitBeastAMRef.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DodgeDefaultAMRef(TEXT("/Script/Engine.AnimMontage'/Game/Asset/CharacterHue/HueAnim/HueAnimMontage/AM_Hue_Dodge2.AM_Hue_Dodge2'"));
	if (DodgeDefaultAMRef.Succeeded()) DodgeMontageListBySkillSet.Add(ESkillSetType::Defalut, DodgeDefaultAMRef.Object);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DodgeBeastAMRef(TEXT("/Script/Engine.AnimMontage'/Game/Asset/CharacterHue/HueAnim/HueAnimMontage/AM_Hue_Dodge_Beast.AM_Hue_Dodge_Beast'"));
	if (DodgeBeastAMRef.Succeeded()) DodgeMontageListBySkillSet.Add(ESkillSetType::Beast, DodgeBeastAMRef.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathDefaultAMRef(TEXT("/Script/Engine.AnimMontage'/Game/Asset/CharacterHue/HueAnim/HueAnimMontage/AM_Hue_Die.AM_Hue_Die'"));
	if (DeathDefaultAMRef.Succeeded()) DeathMontageListBySkillSet.Add(ESkillSetType::Defalut, DeathDefaultAMRef.Object);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathBeastAMRef(TEXT("/Script/Engine.AnimMontage'/Game/Asset/CharacterHue/HueAnim/HueAnimMontage/AM_Hue_Die_Beast.AM_Hue_Die_Beast'"));
	if (DeathBeastAMRef.Succeeded()) DeathMontageListBySkillSet.Add(ESkillSetType::Beast, DeathBeastAMRef.Object);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultWeaponMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/CharacterHue/Resource/SK_Weapon_Default.SK_Weapon_Default'"));
	if (DefaultWeaponMeshRef.Succeeded()) WeaponMeshListBySkillSet.Add(ESkillSetType::Defalut, DefaultWeaponMeshRef.Object);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BeastWeaponMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/CharacterHue/Resource/SK_Weapon_Beast.SK_Weapon_Beast'"));
	if (BeastWeaponMeshRef.Succeeded()) WeaponMeshListBySkillSet.Add(ESkillSetType::Beast, BeastWeaponMeshRef.Object);

	// 무기 메시 컴포넌트
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMeshComponent->SetupAttachment(GetMesh(), FName("WeaponSocket"));
	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (CommonAnimBlueprintListBySkillSet[ESkillSetType::Defalut] != nullptr)
	{
		SetupAnimationBySkillSet(ESkillSetType::Defalut);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load default animation blueprint"));
	}
	
	// 애니메이션 관련 요소 최초 초기화(DefaultSet)
	SetupAnimationBySkillSet(ESkillSetType::Defalut);

	//------------------스탯 초기화------------------
	Level = 1;				// 레벨
	Exp = 0;				// 경험치
	AttackPower = 200;		// 기본 공격력
	CurrentAttackPower = AttackPower; // 현재 공격력
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

	UnlockedSkillInfo.Add(ESkillSetType::Defalut, true);
	UnlockedSkillInfo.Add(ESkillSetType::Beast, true);
	UnlockedSkillInfo.Add(ESkillSetType::Mirror, false);
	UnlockedSkillInfo.Add(ESkillSetType::Puppet, false);
	UnlockedSkillInfo.Add(ESkillSetType::Dream, false);
	//-------------------------------------------------
}

void AKeeperCharacter::BeginPlay()
{
	Super::BeginPlay();

	bIsAttacking = false;
	bIsDodging = false;
	bIsHitReacting = false;

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	if (CommonAnimBlueprintListBySkillSet.Contains(ESkillSetType::Defalut) && 
		CommonAnimBlueprintListBySkillSet[ESkillSetType::Defalut] != nullptr)
	{
		UAnimBlueprint* DefaultAnimBP = CommonAnimBlueprintListBySkillSet[ESkillSetType::Defalut];
		if (DefaultAnimBP && DefaultAnimBP->GeneratedClass)
		{
			GetMesh()->SetAnimInstanceClass(DefaultAnimBP->GeneratedClass);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load default animation blueprint"));
	}

	if (DefaultAnimBlueprint)
	{
		GetMesh()->SetAnimInstanceClass(DefaultAnimBlueprint);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AnimInstance is NULL in packaged build!"));
	}
	
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
	
	// 광기 몬스터 스폰 타이머

	GetWorldTimerManager().SetTimer(
	TargetSpawnTimer,
	this,
	&AKeeperCharacter::HandleTargetSpawning,
	1.0f,
	true
);

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

void AKeeperCharacter::StartMadnessDecayDelay()
{
	GetWorldTimerManager().ClearTimer(MadnessDecayTimer);
	GetWorldTimerManager().ClearTimer(MadnessDecayDelayTimer);
	
	GetWorldTimerManager().SetTimer(
		MadnessDecayDelayTimer,
		this,
		&AKeeperCharacter::StartMadnessDrain,
		MADNESS_DECAY_DELAY,
		false
	);
}

void AKeeperCharacter::ResetHitState()
{
	bIsHitting = false;
	GetWorldTimerManager().ClearTimer(HitStateTimer);
}

void AKeeperCharacter::StartMadnessDrain()
{
	GetWorldTimerManager().SetTimer(
	MadnessDecayTimer,
	this,
	&AKeeperCharacter::DecreaseMadness,
	MADNESS_DECAY_INTERVAL,
	true
	);
}

void AKeeperCharacter::DecreaseMadness()
{
	if (CurrentMadness > 0)
	{
		CurrentMadness = FMath::Max(0, CurrentMadness - MADNESS_DECAY_RATE);
		OnStatChanged.Execute();
		IncreasedAttack();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(MadnessDecayTimer);
	}
}

void AKeeperCharacter::SpawnTargets()
{
	if (!MadnessMonsterBlueprintClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target Blueprint class not set!"));
		return;
	}
	
	FVector CharacterLocation = GetActorLocation();
	FRotator CharacterRotation = GetActorRotation();
	
	TArray<FVector> SpawnOffsets = {
		FVector(MADNESS_SPAWN_DISTANCE, 0.0f, 0.0f),
		FVector(-MADNESS_SPAWN_DISTANCE, 0.0f, 0.0f),
		FVector(0.0f, MADNESS_SPAWN_DISTANCE, 0.0f),
		FVector(0.0f, -MADNESS_SPAWN_DISTANCE, 0.0f)
	};
	
	for (const FVector& Offset : SpawnOffsets)
	{
		FVector SpawnLocation = CharacterLocation + CharacterRotation.RotateVector(Offset);
		FRotator SpawnRotation = CharacterRotation;
        
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor* SpawnedTarget = GetWorld()->SpawnActor<AActor>(
			MadnessMonsterBlueprintClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParams
		);
	}
}

void AKeeperCharacter::HandleTargetSpawning()
{
	if (CurrentMadness >= 80 && !bIsTargetSpawnOnCooldown)
	{
		SpawnTargets();
		
		bIsTargetSpawnOnCooldown = true;
		
		FTimerHandle CooldownTimer;
		GetWorldTimerManager().SetTimer(
			CooldownTimer,
			[this]()
			{
				bIsTargetSpawnOnCooldown = false;
				UE_LOG(LogTemp, Warning, TEXT("Target spawn cooldown finished"));
			},
			MADNESS_MONSTER_INTERVAL,
			false
		);
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
	bComboAttackDown = true;

	UAnimInstance* AnimaInstance = GetMesh()->GetAnimInstance();

	if (!AnimaInstance || !CurrentComboMontage) return;

	AKeeperCharacterController* KeeperController = Cast<AKeeperCharacterController>(GetController());
	if (KeeperController)
	{
		FVector ClickedLocation = KeeperController->GetLastClickedLocation();
		FVector Direction = ClickedLocation - GetActorLocation();
		Direction.Z = 0;
        
		if (Direction.SizeSquared() > 0.01f)
		{
			Direction.Normalize();
			FRotator NewRotation = Direction.Rotation();
			SetActorRotation(FRotator(0, NewRotation.Yaw, 0));
		}
	}
	
	bComboAttacking = true;
	const char* comboList[] = { "combo1", "combo2", "combo3", "combo4"};

	if (ComboAttackNumber >= 4)
		ComboAttackNumber = 0;

	AnimaInstance->Montage_Play(CurrentComboMontage, 1.5f);
	AnimaInstance->Montage_JumpToSection(FName(comboList[ComboAttackNumber]), CurrentComboMontage);
	
	if (DamageField)
	{
		DamageField->SetDamageAmount(CurrentAttackPower);
		DamageField->ActivateDamage();
	}

	if (SubShooterDelegate.IsBound())
	{
		SubShooterDelegate.Broadcast();
	}

	StartMadnessDecayDelay();
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

	if (CurrentDeathMontage && GetMesh()->GetAnimInstance())
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->StopAllMontages(0.1f);
		AnimInstance->Montage_Play(CurrentDeathMontage);
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
	if (Montage == CurrentHitMontage)
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
	if (Montage == CurrentComboMontage)
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
	if (CurrentHitMontage)
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
				AnimInstance->Montage_Play(CurrentHitMontage);
			}
		}
	}
}


void AKeeperCharacter::ExecuteDodge()
{
	if (bIsDodging || bIsAttacking || bIsHitReacting)
		return;

	if (CurrentDodgeMontage)
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
		
		float DodgeTime = CurrentDodgeMontage->GetPlayLength();
		FVector RequiredVelocity = (DodgeVector * DodgeDistance) / DodgeTime;

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->OnMontageEnded.AddDynamic(this, &AKeeperCharacter::OnDodgeMontageEnded);
			AnimInstance->Montage_Play(CurrentDodgeMontage);
           
			MovementComp->Velocity = RequiredVelocity;
		}
	}
}

void AKeeperCharacter::OnDodgeMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == CurrentDodgeMontage)
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

void AKeeperCharacter::TakeDamage_C(float DamageAmount/*, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser*/)
{
	if (bIsDead || bIsDodging || bIsHitting)
		return;
	
	float ActualDamage = DamageCalculation(DamageAmount);
	CurrentHP = FMath::Max(0.0f, CurrentHP - ActualDamage);
	OnStatChanged.Execute();

	bIsHitting = true;

	if (GetWorldTimerManager().IsTimerActive(HitStateTimer))
	{
		GetWorldTimerManager().ClearTimer(HitStateTimer);
	}
	
	GetWorldTimerManager().SetTimer(
		HitStateTimer,
		this,
		&AKeeperCharacter::ResetHitState,
		HIT_STATE_DURATION,
		false
	);
	
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
	ActualDamage *= FMath::RandRange(0.85f, 1.15f);

	return ActualDamage;
}

void AKeeperCharacter::IncreasedMadness(float MadnessCost)
{
	CurrentMadness = FMath::Min(MaxMadness, CurrentMadness + MadnessCost);
	OnStatChanged.Execute();

	IncreasedAttack();
	
	if (CurrentMadness >= 80)
	{
		HandleTargetSpawning();
	}
	
	if (CurrentMadness >= MaxMadness)
	{
		Die();
		return;
	}
}

void AKeeperCharacter::IncreasedAttack()
{
	if (CurrentMadness < 20)
	{
		CurrentAttackPower = AttackPower * 1.0f;
	}
	else if (CurrentMadness >= 20 && CurrentMadness < 50)
	{
		CurrentAttackPower = AttackPower * 1.2f;
	}
	else if (CurrentMadness >= 50 && CurrentMadness < 80)
	{
		CurrentAttackPower = AttackPower * 1.5f;
	}
	else if (CurrentMadness >= 80)
	{
		CurrentAttackPower = AttackPower * 2.0f;
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
		SkillComponent->PrevSkillSetData = SkillComponent->Skills[Key].SkillSet;
		SetupAnimationBySkillSet(SkillComponent->PrevSkillSetData);

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

	AttackReset();
	StartMadnessDecayDelay();
}

void AKeeperCharacter::CooldownSkill(ESkillKeyMapping Key)
{
	if (SkillComponent->Skills[Key].IsCooldown())
	{
		GetWorldTimerManager().ClearTimer(SkillCooldownHandle[Key]);
		SkillComponent->Skills[Key].EndCooldown();
	}
}

void AKeeperCharacter::SetupAnimationBySkillSet(ESkillSetType InSkillSet)
{
	if (!CommonAnimBlueprintListBySkillSet.Contains(InSkillSet) || 
		!ComboMontageListBySkillSet.Contains(InSkillSet) ||
		!HitMontageListBySkillSet.Contains(InSkillSet) ||
		!DodgeMontageListBySkillSet.Contains(InSkillSet) ||
		!DeathMontageListBySkillSet.Contains(InSkillSet) ||
		!WeaponMeshListBySkillSet.Contains(InSkillSet))
	{
		UE_LOG(LogTemp, Error, TEXT("Missing animation data for skill set type: %d"), static_cast<int32>(InSkillSet));
		return;
	}
	
	UAnimBlueprint* AnimBP = CommonAnimBlueprintListBySkillSet[InSkillSet];
	if (AnimBP && AnimBP->GeneratedClass)
	{
		GetMesh()->SetAnimClass(AnimBP->GeneratedClass);
	}

	CurrentComboMontage		= ComboMontageListBySkillSet[InSkillSet];
	CurrentHitMontage		= HitMontageListBySkillSet[InSkillSet];
	CurrentDodgeMontage		= DodgeMontageListBySkillSet[InSkillSet];
	CurrentDeathMontage		= DeathMontageListBySkillSet[InSkillSet];

	CurrentWeaponMesh = WeaponMeshListBySkillSet[InSkillSet];
	if (WeaponMeshComponent && CurrentWeaponMesh)
	{
		WeaponMeshComponent->SetSkeletalMesh(CurrentWeaponMesh);
	}
}

void AKeeperCharacter::UpdateUnlockedSkillInfo(ESkillSetType InSkillSet)
{
	UnlockedSkillInfo[InSkillSet] = true;
}

