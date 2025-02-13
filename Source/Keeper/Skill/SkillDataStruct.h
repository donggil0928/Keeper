// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillActor/AdditionalEffectActor.h"
#include "SkillDataStruct.generated.h"


class KEEPER_API SkillDataStruct
{
public:
	SkillDataStruct();
	~SkillDataStruct();
};


UENUM(BlueprintType)
enum class ESkillKeyMapping : uint8
{
	Q	UMETA(DisplayName = "Key_Q"),
	W	UMETA(DisplayName = "Key_W"),
	E	UMETA(DisplayName = "Key_E"),
	R	UMETA(DisplayName = "Key_R")
};

// 스킬셋의 종류, 사용중인 스킬이 어느 스킬셋에 포함되었는지 구분을 위함.
UENUM(BlueprintType)
enum class ESkillSetType : uint8
{
	Defalut	UMETA(DisplayName = "DefalutSet"),
	Beast	UMETA(DisplayName = "BeastSet")
};

// 스킬의 공격 방식, 해당 스킬의 공격이 근접인지, 원거리인지 구분을 위함.
UENUM(BlueprintType)
enum class ESkillAttackType : uint8
{
	Melee	UMETA(DisplayName = "Melee"),
	Ranged	UMETA(DisplayName = "Ranged"),
	Target	UMETA(DisplayName = "Targeting"),
	Buff	UMETA(DisplayName = "Buff"),
	Debuff	UMETA(DisplayName = "Debuff")
};

USTRUCT(Atomic, BlueprintType)
struct FSkillDataStruct :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()


public:
	void Use(class AKeeperCharacter* player);
	uint8 IsCooldown() { return bIsCooldown; }
	void StartCooldown() { bIsCooldown = true; }
	void EndCooldown() { bIsCooldown = false; }

public:
	// ---------- 스킬만의 정보 ----------
	// 스킬의 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name; 
	// 스킬 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;	
	// 스킬 아이콘
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SkillIcon;
	// 스킬셋 타입. 어떤 스킬셋에 포함되어 있는지.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillSetType SkillSet;
	// 스킬 타입. 스킬의 유형 구분.
	// Melee : 근거리, Ranged : 원거리, Targeting : 대상지정, Buff : 버프부여, Debuff : 디버프부여
	// 버프, 디버프 부여는 공격 여부 상관없이 해당 효과를 가진 스킬일 경우 사용. 
	// 즉, 스킬이 피해를 입히든 입히지 않든 버프나 디버프를 부여하면 해당 유형으로 구분.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillAttackType SkillAttackType;	
	// 스킬의 현재 레벨
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentLevel;	
	// 스킬의 쿨타임
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondToCooldown;	
	// 쿨타임 활성화 유무
	UPROPERTY()
	uint8 bIsCooldown : 1;	
	// 스킬의 범위(사거리)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;	

	// 원거리 스킬의 투사체. SkillAttackType이 Ranged일 때만 활성화.
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Projectile Actor", EditCondition = "SkillAttackType == ESkillAttackType::Ranged"))
	TSubclassOf<class ABaseProjectileActor> Projectile;

	// 스킬의 효과부여 여부. true면 해당 스킬은 특정 대상에게 효과를 부여함.
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//uint8 bCanApplyEffect : 1;
	// 효과 부여 스킬의 이펙트 액터. bCanApplyEffect가 true일 때만 활성화.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "SkillAttackType == ESkillAttackType::Buff || SkillAttackType == ESkillAttackType::Debuff"))
	TSubclassOf<class AAdditionalEffectActor> EffectActor;
	// 부여된 효과의 지속시간. bCanApplyEffect가 true일 때만 활성화.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "SkillAttackType == ESkillAttackType::Buff || SkillAttackType == ESkillAttackType::Debuff"))
	float EffectDuration;


	// 스킬 애니메이션 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* SkillAnimMontage;
	// 스킬 데미지 계수
	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageCoefficient;

	// <스킬 정보에 추가되어야 하는 내용>
	//  - 스킬 인덱스, 스킬 종류(근접(단일, 광역), 원거리(단일, 광역), 지속형, 재사용, 트리거), 스킬의 지정위치정보(QWER 중 어느 위치인지), 스킬의 집합정보(어떤 스킬셋인지)
	//  - 원거리 스킬의 경우 스킬에 필요한 투사체 액터가 필요.
	//  - 지속형 스킬의 경우 해당 스킬의 지속시간 정보 필요.
	//  - 스킬의 범위와 사거리의 분리 필요 >>> 복합적으로 사용되는 경우가 존재, ex) 전진하며 공격, 전방으로 도약 후 주변의 적에게 광역 데미지 등
	//  - 스킬의 데미지 공식 구상 필요(스킬의 기본데미지, 플레이어의 공격력을 어느정도 비중으로 두는지, 추가 수치가 주어지는 경우가 있는지를 고려)
	//  - (단일, 광역) 구분은 피격된 적(들)에게 상태이상을 부여해야 하는 경우가 있어서 구분 필요.
	//  - 스킬 지속에 의미에 대해 이야기가 필요해 보입니다. 
	//		스킬 발동 후 지속시간이 흐르고 지속이 끝나면 쿨타임(지속형) / 스킬 발동 직후 지속시간과 무관하게 바로 쿨타임(버프 부여)
	//		이전에 플레이어 캐릭터에게 '버프'가 적용되고 UI에도 표시한다고 했는데 지속형 스킬과 버프 스킬의 차이는?


	// ---------- 플레이어의 정보 ----------
	// 플레이어의 위치
	UPROPERTY()
	FVector PlayerPosition;			
	// 마우스의 위치
	UPROPERTY()
	FVector MouseCursorPosition;	
	// 플레이어의 최대 체력
	//UPROPERTY()
	//float MaxHp;				
	// 플레이어의 현재 체력
	//UPROPERTY()
	//float CurrentHp;			
	// 플레이어의 공격력
	//UPROPERTY()
	//float AttackPower;			
	// 플레이어의 이동속도
	//UPROPERTY()
	//float MovementSpeed;		
	// 플레이어의 체력회복량
	//UPROPERTY()
	//float GenerationHp;			
	// 현재 누적된 코스트, 즉 현재 누적된 광기 게이지 량
	//int32 CurrentStackedCost;	

	// [스킬 정보에 플레이어 정보가 필요한가? 플레이어 스텟과 관련된 동작을 하는 함수를 캐릭터쪽에서 제공받아 사용하는게 깔끔할 것 같은데...]

	// <플레이어 정보에 추가되어야 하는 내용>
	//  - 현재 적용된 버프 누적 정보, 플레이어의 현재 대체체력
	//  - 플레이어의 현재 누적된 광기는 필요한가요?
	//		'스킬 사용에 따른 광기의 증가' 때문이라면 [플레이어 캐릭터 코드]에서 '광기를 증가시키는 함수'를 만들어 호출하는게 나을듯 합니다.
	//		광기를 페이백해주는 스킬때문에 있는거라면 스킬 발동 직후 '버프'를 부여하고 처치 시 해당 버프를 소모하여 광기를 낮추는 게 어떨지..

	// ---------- 코스트 ----------
	// 스킬의 코스트, 사용 시 얻는 광기의 양을 의미
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cost;	


	/*FSkillCustomData& operator=(const FSkillCustomData& Other) {
		if (this == &Other) return *this;

		Name = Other.Name;
		Description = Other.Description;
		CurrentLevel = Other.CurrentLevel;
		Range = Other.Range;
		Cost = Other.Cost;
		SecondToCooldown = Other.SecondToCooldown;

		return *this;
	}*/

	// <스킬 레벨에 대한 구상>
	// 스킬 레벨의 변화에 따른 스킬의 정보는 스킬 데이터 시트를 따로 만들어 관리한다.
	// 그리고 현재 적용된 스킬의 레벨을 저장할 때 총 스킬 개수만큼의 정수 배열을 만든 후
	// 스킬에게 각각 인덱스를 부여하고 해당 인덱스의 크기를 변화시키는 방법으로 저장한다.
	// 이 때 스킬 데이터 시트에서는 
	// [ (스킬 인덱스) * (스킬 최대 레벨) + {(스킬의 현재 레벨) - 1} ]
	// 공식을 통해 해당 스킬의 레벨에 맞는 데이터를 호출해 올 수 있게 한다.
	// 어떤 스킬도 지정되있지 않은 경우 -1을 할당하여 구분한다.
	// 애니메이션의 경우 해당 애니메이션의 경로를 저장한다.(생각중)
};