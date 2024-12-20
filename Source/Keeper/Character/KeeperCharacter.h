// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Skill/SkillData.h"
#include "DamageField_Base.h"
#include "KeeperCharacter.generated.h"

class AKeeperCharacterController;
class AMonsterBase;
class ADamageField_Base;
class USphereComponent;

DECLARE_DELEGATE_OneParam(FUseSkillDelegate, int);

UCLASS()
class KEEPER_API AKeeperCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AKeeperCharacter();
	void SetNewDestination(AKeeperCharacterController* _LogPlayerController, const FVector Destination) const;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	ACharacter* CurrentTarget;

	//void ApplyAreaDamage(const FVector& DamageCenter, float DamageAmount, float _DamageRadius);
	
	// ----------공격 애니메이션-----------
public:
	bool bComboAttacking;
	bool bComboAttackDown;
	bool bComboAttackNext;
	int ComboAttackNumber;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "ComboAttack", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* comboMontage;
	
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
	

	// ----- 스탯 변경 함수 -----
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override ;
	
	void DealDamage(ACharacter* Monster, float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void IncreasedMadness(float MadnessCost);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ModifyMovementSpeed(float SpeedModifier);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float DamageRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	ADamageField_Base* DamageField;

protected:
	void CreateDamageField();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	//------------------스킬 사용 관련------------------
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	class USkillComponent* SkillComponent;	// 스킬을 관리하는 컴포넌트. 스킬의 기능이나 요소는 여기에 있습니다.

	// 스킬 쿨타임 제어를 위한 타이머핸들
	FTimerHandle SkillQTimerHandle;
	FTimerHandle SkillWTimerHandle;
	FTimerHandle SkillETimerHandle;
	FTimerHandle SkillRTimerHandle;

public:
	// 스킬 사용 시 바인딩되는 함수들
	UFUNCTION(BlueprintCallable)
	void SkillActivatedQ();
	UFUNCTION(BlueprintCallable)
	void SkillActivatedW();
	UFUNCTION(BlueprintCallable)
	void SkillActivatedE();
	UFUNCTION(BlueprintCallable)
	void SkillActivatedR();

	// 스킬 쿨타임 종료 후 타이머핸들을 클리어 해주는 함수
	UFUNCTION(BlueprintCallable)
	void SkillQCooldown();
	UFUNCTION(BlueprintCallable)
	void SkillWCooldown();
	UFUNCTION(BlueprintCallable)
	void SkillECooldown();
	UFUNCTION(BlueprintCallable)
	void SkillRCooldown();

	//-------------------------------------------------

};
