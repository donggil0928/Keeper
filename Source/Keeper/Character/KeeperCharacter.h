// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "Skill/SkillData.h"
#include "../Skill/SkillDataStruct.h"
#include "DamageField_Base.h"
#include "KeeperCharacter.generated.h"

class AKeeperCharacterController;
class AMonsterBase;
class ADamageField_Base;
class USphereComponent;

DECLARE_DELEGATE(FOnStatChanged);
DECLARE_DELEGATE_OneParam(FStartCooldown, ESkillKeyMapping);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRemoteSubShooter);

UCLASS()
class KEEPER_API AKeeperCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AKeeperCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsPerformingAction() const
	{
		return bIsAttacking || bIsDodging || bIsHitReacting;
	}

	bool CanMove() const;

private:
	bool bIsAttacking;
	bool bIsDodging;
	bool bIsHitReacting;
	bool bIsDead = false;

	// 광기 게이지 하락
	FTimerHandle MadnessDecayTimer;
	FTimerHandle MadnessDecayDelayTimer;
	
	void StartMadnessDrain();
	void DecreaseMadness();
    
	const float MADNESS_DECAY_DELAY = 5.0f;
	const float MADNESS_DECAY_RATE = 1.0f;
	const float MADNESS_DECAY_INTERVAL = 1.0f;

	// 광기 몬스터 생성
	FTimerHandle TargetSpawnTimer;
	void SpawnTargets();
	void HandleTargetSpawning();
	const float MADNESS_MONSTER_INTERVAL = 20.0f;
	const float MADNESS_SPAWN_DISTANCE = 150.0f;
	bool bIsTargetSpawnOnCooldown = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "MadnessMonster")
	TSubclassOf<AActor> MadnessMonsterBlueprintClass;
	
private:
	ACharacter* CurrentTarget;

	//void ApplyAreaDamage(const FVector& DamageCenter, float DamageAmount, float _DamageRadius);
	
	// ----------공격 애니메이션-----------
public:
	bool bComboAttacking;
	bool bComboAttackDown;
	bool bComboAttackNext;
	int ComboAttackNumber;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Animation")
	TMap<ESkillSetType, class UAnimMontage*> ComboMontageListBySkillSet;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* CurrentComboMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Animation")
	TMap<ESkillSetType, class UAnimMontage*> HitMontageListBySkillSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* CurrentHitMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Animation")
	TMap<ESkillSetType, class UAnimMontage*> DodgeMontageListBySkillSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* CurrentDodgeMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Animation")
	TMap<ESkillSetType, class UAnimMontage*> DeathMontageListBySkillSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* CurrentDeathMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Animation")
	TMap<ESkillSetType, class UAnimBlueprint*> CommonAnimBlueprintListBySkillSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UAnimBlueprint* CurrentAnimBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TSubclassOf<UAnimInstance> DefaultAnimBlueprint;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DodgeAction;

public:
	// -----------------공격 관련-----------------
	UFUNCTION(BlueprintCallable)
	void AttackDown();

	UFUNCTION(BlueprintCallable)
	void AttackUp();

	UFUNCTION(BlueprintCallable)
	void Attack(ACharacter* Monster);

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable)
	void AttackCheck();

	UFUNCTION(BlueprintCallable)
	void TraceWeapon();

	//------------------스탯 관련------------------
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	uint8 Level;  // 레벨
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Exp;  // 경험치
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 AttackPower;  // 공격력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Defense;  // 방어력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 MaxHP;  // 최대 HP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 CurrentHP;  // 현재 HP

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	// float Innocence;  //순수함
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 MaxMadness;  // 최대 광기

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 CurrentMadness;  // 현재 광기

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 MovementSpeed;  // 이동 속도

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void Die();
	
	// --------------------피격 관련---------------------

	UFUNCTION()
	void OnHitMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void AttackReset();
	void PlayHitAnimation();

	void StartMadnessDecayDelay();
	
	// -------------------회피 관련---------------------
	UPROPERTY(EditAnywhere, Category = "Movement")
	float DodgeDistance;
	
	
public:
	void ExecuteDodge();
	UFUNCTION()
	void OnDodgeMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> DeathWidgetClass;

	float GetAttackPower() const { return AttackPower; }
	
	// ----- 스탯 변경 함수 -----
	void TakeDamage_C(float DamageAmount) ;		//HP 감소

	float DamageCalculation(float DamageAmount) const;	// 

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void IncreasedMadness(float MadnessCost);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ModifyMovementSpeed(float SpeedModifier);

	UPROPERTY()
	FTimerHandle DodgeFrictionResetHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float DamageRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	ADamageField_Base* DamageField;

public:
	// 무기 메시 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	TMap<ESkillSetType, class USkeletalMesh*> WeaponMeshListBySkillSet;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	class USkeletalMesh* CurrentWeaponMesh;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	class USkeletalMeshComponent* WeaponMeshComponent;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	//------------------스킬 사용 관련------------------
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	class USkillComponent* SkillComponent;	// 스킬을 관리하는 컴포넌트. 스킬의 기능이나 요소는 여기에 있습니다.

	TMap<ESkillKeyMapping, FTimerHandle> SkillCooldownHandle;	//ĳ���Ͱ� ���� ��ų �迭

	UPROPERTY(EditAnywhere, Category = "Skill")
	TMap<ESkillSetType, bool> UnlockedSkillInfo;

public:
	UFUNCTION()
	FSkillDataStruct FindSkillDataWithMappingKey(ESkillKeyMapping Key);
	// 스킬 사용 시 바인딩되는 함수
	UFUNCTION()
	void ActivateSkill(ESkillKeyMapping Key);
	// 스킬 쿨타임 종료 후 타이머핸들을 클리어 해주는 함수
	UFUNCTION()
	void CooldownSkill(ESkillKeyMapping Key);
	UFUNCTION()
	void SetupAnimationBySkillSet(ESkillSetType InSkillSet);
	UFUNCTION()
	void UpdateUnlockedSkillInfo(ESkillSetType InSkillSet);

	//-------------------------------------------------

public:
	FOnStatChanged OnStatChanged;
	FStartCooldown StartCooldown;
	UPROPERTY(BlueprintAssignable)
	FRemoteSubShooter SubShooterDelegate;
};
