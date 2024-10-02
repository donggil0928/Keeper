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

#include "Skill/SkillData.h"

// Sets default values
AKeeperCharacter::AKeeperCharacter()
{
	bComboAttackDown = false;
	bComboAttacking = false;
	bComboAttackNext = false;
	ComboAttackNumber = 0;

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
	SpringArmComponent->TargetArmLength = 800.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-30.0f, 45.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	CameraComponent->bUsePawnControlRotation = false;

	CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);

	CameraComponent->SetOrthoWidth(2048.0f);

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
	
	//------------------스킬 사용 관련------------------
	Skills.SetNum(4);	// 캐릭터에게 할당된 스킬은 4개(배열의 크기 설정)
	//-------------------------------------------------
}

void AKeeperCharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateDamageField();
	
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

void AKeeperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeeperCharacter::SetNewDestination(AKeeperCharacterController* _LogPlayerController, const FVector Destination) const
{
	// 공격 중 캐릭터 이동 제어
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
	{
		return;
	}

	float const Distance = FVector::Dist(Destination, GetActorLocation());
	if (Distance > 120.0f)
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(_LogPlayerController, Destination);
}

void AKeeperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
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

// 범위 데미지를 처리하는 함수 추가
void AKeeperCharacter::ApplyAreaDamage(const FVector& DamageCenter, float DamageAmount, float _DamageRadius)
{
	if (DamageField)
	{
		DamageField->SetActorLocation(DamageCenter);
        
		TArray<AActor*> OverlappingActors;
		DamageField->GetHitSphereComponent()->GetOverlappingActors(OverlappingActors, AMonsterBase::StaticClass());

		for (AActor* Actor : OverlappingActors)
		{
			AMonsterBase* Monster = Cast<AMonsterBase>(Actor);
			if (Monster)
			{
				DealDamage(Monster, DamageAmount);
			}
		}
	}
	// 디버깅 용
	//DrawDebugSphere(GetWorld(), DamageCenter, _DamageRadius, 12, FColor::Red, false, 1.0f);
}


void AKeeperCharacter::AttackDown()
{
	// 이동 중 캐릭터 공격 제어
	GetCharacterMovement()->StopActiveMovement();
	
	
	UE_LOG(LogTemp, Warning, TEXT("AttackDown 함수 실행"));
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
	UE_LOG(LogTemp, Warning, TEXT("Attack 함수 실행"));
	bComboAttackDown = true;

	UAnimInstance* AnimaInstance = GetMesh()->GetAnimInstance();

	if (!AnimaInstance || !comboMontage) return;

	bComboAttacking = true;
	const char* comboList[] = { "combo1", "combo2", "combo3", "combo4"};

	if (ComboAttackNumber >= 4)
		ComboAttackNumber = 0;
	UE_LOG(LogTemp, Warning, TEXT("ComboAttack%d 실행"), ComboAttackNumber);

	AnimaInstance->Montage_Play(comboMontage, 1.5f);
	AnimaInstance->Montage_JumpToSection(FName(comboList[ComboAttackNumber]), comboMontage);

	FVector CharacterLocation = GetActorLocation();
	FRotator CharacterRotation = GetActorRotation();
    
	FVector Offset(100.0f, 0.0f, 0.0f); // 거리 설정
	FVector RotatedOffset = CharacterRotation.RotateVector(Offset);
    
	FVector DamageCenter = CharacterLocation + RotatedOffset;
    
	ApplyAreaDamage(DamageCenter, AttackPower, DamageRadius);

}

void AKeeperCharacter::AttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("ComboAttackEnd 함수 실행"));
	bComboAttacking = false;
	ComboAttackNumber = 0;
}

void AKeeperCharacter::AttackCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("ComboAttackCheck �Լ� ... "));

	if (bComboAttackNext == true)
	{
		ComboAttackNumber += 1;
		bComboAttackNext = false;
		Attack(CurrentTarget);
	}
}


//------------------스탯 변경 함수------------------

float AKeeperCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 데미지 계산식
	float ActualDamage = FMath::Max(0.0f, DamageAmount - Defense);
	CurrentHP = FMath::Max(0.0f, CurrentHP - ActualDamage);

	if (CurrentHP <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character has died."));
	}

	return ActualDamage;
}

void AKeeperCharacter::DealDamage(ACharacter* Monster, float DamageAmount)
{
	AMonsterBase* MonsterTarget = Cast<AMonsterBase>(Monster);
	if (Monster && DamageAmount > 0.0f)
	{
		MonsterTarget->TakeDamage(DamageAmount);
		UE_LOG(LogTemp, Warning, TEXT("Dealt %f damage to %s"), DamageAmount, *Monster->GetName());
	}
}

void AKeeperCharacter::IncreasedMadness(float MadnessCost)
{
	CurrentMadness = FMath::Max(MaxMadness, CurrentMadness + MadnessCost);

	if (MaxMadness >= CurrentMadness)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character has died."));
	}
}

void AKeeperCharacter::ModifyMovementSpeed(float SpeedModifier)
{
	MovementSpeed = FMath::Max(0.0f, MovementSpeed + SpeedModifier);
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

//------------------스킬 사용 관련------------------

void AKeeperCharacter::UseSkill(int skillIndex)
{
	Cast<USkillData>(Skills[skillIndex]->GetDefaultObject())->Use(this);

	/*USkillData* Skill = Cast<USkillData>(SkillDataRef);
	if (Skill != nullptr) Skill->Use(this);
	else UE_LOG(LogTemp, Warning, TEXT("Skill Not Found"));*/
}

