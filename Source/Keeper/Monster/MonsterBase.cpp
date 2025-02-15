// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/MonsterBase.h"

#include "DamageTextWidget.h"
#include "MonsterHealthBarWidget.h"
#include "Controller/MonsterAIControllerBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Blueprint/UserWidget.h"
#include "Character/KeeperCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

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

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);
	HealthBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidget->SetDrawSize(FVector2D(150.0f, 30.0f));
}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;

	MonsterAIController = Cast<AMonsterAIControllerBase>(GetController());
	
	if (BehaviorTree && MonsterAIController)
	{
		MonsterAIController->RunBehaviorTree(BehaviorTree);
	}

	if (HealthBarWidgetClass)
	{
		UMonsterHealthBarWidget* Widget = CreateWidget<UMonsterHealthBarWidget>(GetWorld(), HealthBarWidgetClass);
		if (Widget)
		{
			HealthBarWidget->SetWidget(Widget);
			UpdateHealthBar(); // 초기 체력바 업데이트
		}
	}
	
	bIsHitReacting = false;
}

void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	FVector WorldPosition = GetActorLocation() + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 50);
	FVector2D ScreenPosition;

	for (int32 i = ActiveDamageWidgets.Num() - 1; i >= 0; --i)
	{
		if (ActiveDamageWidgets[i].IsValid())
		{
			if (PC->ProjectWorldLocationToScreen(WorldPosition, ScreenPosition))
			{
				ActiveDamageWidgets[i]->SetPositionInViewport(ScreenPosition);
			}
		}
		else
		{
			ActiveDamageWidgets.RemoveAt(i);
		}
	}
}

void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMonsterBase::Attack()
{
	if (!bIsAttacking && !bIsHitReacting)
	{
		bIsAttacking = true;
		PlayAttackMontage();
	}
}

void AMonsterBase::PlayAttackMontage()
{
	if (!bIsAttacking && !bIsHitReacting)
	{
		if (AttackMontage)
		{
			USkeletalMeshComponent* MeshComponent = GetMesh();
			if (MeshComponent)
			{
				UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance();
				if (AnimInstance)
				{
					bIsAttacking = true;
					
					AnimInstance->OnMontageEnded.AddDynamic(this, &AMonsterBase::OnAttackMontageEnded);
					AnimInstance->Montage_Play(AttackMontage);
				}
			}
		}
	}
}

void AMonsterBase::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == AttackMontage)
	{
		bIsAttacking = false;
		
		if (USkeletalMeshComponent* MeshComponent = GetMesh())
		{
			if (UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance())
			{
				AnimInstance->OnMontageEnded.RemoveDynamic(this, &AMonsterBase::OnAttackMontageEnded);
			}
		}
	}
}

void AMonsterBase::TakeDamage(float DamageAmount)
{
	// 데미지 계산식
	float ActualDamage = FMath::RandRange(0.85f, 1.15f) * FMath::Max(0.0f, DamageAmount - MonsterDef);
	CurrentHP = FMath::Max(0.0f, CurrentHP - ActualDamage);

	if (AKeeperCharacter* PlayerCharacter = Cast<AKeeperCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		PlayerCharacter->StartMadnessDecayDelay();
		UE_LOG(LogTemp, Warning, TEXT("광기 게이지 타이머 초기화"));
	}
	
	if (ActualDamage > 0 && DamageTextWidgetClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			UDamageTextWidget* DamageTextWidget = CreateWidget<UDamageTextWidget>(World, DamageTextWidgetClass);
			if (DamageTextWidget)
			{
				DamageTextWidget->SetDamageText(
					FString::FromInt(FMath::FloorToInt(ActualDamage)), true);
				
				DamageTextWidget->AddToViewport(100);

				ActiveDamageWidgets.Add(TWeakObjectPtr<UDamageTextWidget>(DamageTextWidget));
			}
		}
	}
	
	PlayHitAnimation();
	UpdateHealthBar();
	
	if (CurrentHP <= 0.0f)
	{
		Die();
		return;
	}

	if (!bIsHitReacting)
	{
		if (MonsterAIController)
		{
			MonsterAIController->GetBrainComponent()->PauseLogic("Hit Reaction");
		}
        
		bIsHitReacting = true;
		PlayHitAnimation();
	}

	UE_LOG(LogTemp, Warning, TEXT("Damage %f applied to Monster"), ActualDamage);
}

void AMonsterBase::PlayHitAnimation()
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
				AnimInstance->OnMontageEnded.RemoveDynamic(this, &AMonsterBase::OnHitMontageEnded);
				AnimInstance->OnMontageEnded.AddDynamic(this, &AMonsterBase::OnHitMontageEnded);
                
				// 현재 진행 중인 몽타주 중단
				AnimInstance->StopAllMontages(0.1f);
                
				// 피격 몽타주 재생
				AnimInstance->Montage_Play(HitMontage);
			}
		}
	}
}

void AMonsterBase::OnHitMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == HitMontage)
	{
		bIsHitReacting = false;
		
		ResumeAIBehavior();
		
		if (USkeletalMeshComponent* MeshComponent = GetMesh())
		{
			if (UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance())
			{
				AnimInstance->OnMontageEnded.RemoveDynamic(this, &AMonsterBase::OnHitMontageEnded);
			}
		}
	}
}

void AMonsterBase::ResumeAIBehavior()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;
	
	if (MonsterAIController)
	{
		MonsterAIController->GetBrainComponent()->ResumeLogic("Hit Reaction");
	}
}

void AMonsterBase::UpdateHealthBar()
{
	float HealthPercent = static_cast<float>(CurrentHP) / static_cast<float>(MaxHP);
	OnHealthChanged.Broadcast(HealthPercent);
	if (HealthBarWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("HealthBarWidget exists"));
        
		if (UMonsterHealthBarWidget* Widget = Cast<UMonsterHealthBarWidget>(HealthBarWidget->GetWidget()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Widget cast successful"));
			Widget->UpdateHealthPercent(HealthPercent);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to cast HealthBarWidget"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HealthBarWidget is null"));
	}
}

void AMonsterBase::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Monster has died."));
	
	OnMonsterDead.Broadcast();

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