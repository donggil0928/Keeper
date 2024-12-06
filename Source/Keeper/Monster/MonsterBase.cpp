// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterBase.h"
#include "Controller/MonsterAIControllerBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTree.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
	DefaultMovementSpeed = 400.0f;	// 이동속도
	MaxHP = 500;					// 기본 최대 HP
	CurrentHP = MaxHP;
	MonsterAtk = 100;				// 기본 공격력
	MonsterDef = 10;				// 기본 방어력
	MonsterExp = 100;				// 몬스터가 주는 마석
	MonsterCoin = 100;				// 몬스터가 주는 코인
	
	AIControllerClass = AMonsterAIControllerBase::StaticClass();

	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;
}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;
	
	if (BehaviorTree)
	{
		AMonsterAIControllerBase* AIController = Cast<AMonsterAIControllerBase>(GetController());
		if (AIController)
		{
			AIController->RunBehaviorTree(BehaviorTree);
		}
	}
}

void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMonsterBase::TakeDamage(float DamageAmount)
{
	// 데미지 계산식
	float ActualDamage = FMath::Max(0.0f, DamageAmount - MonsterDef);
	CurrentHP = FMath::Max(0.0f, CurrentHP - ActualDamage);

	if (CurrentHP <= 0.0f)
	{
		Die();
	}
}

void AMonsterBase::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Monster has died."));

	Destroy();
}

void AMonsterBase::SetMovementSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void AMonsterBase::SomeEventTrigger()
{
	// 가끔 이속 변경할 때
	SetMovementSpeed(DefaultMovementSpeed * 0.0f);
}

void AMonsterBase::ResetMovementSpeed()
{
	// 이속 원상태로 복귀
	SetMovementSpeed(DefaultMovementSpeed);
}