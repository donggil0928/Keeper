// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class KEEPER_API USkillData : public UObject
{
	GENERATED_BODY()
	
public:
	USkillData();

	void Use(class AKeeperCharacter* player);
	void StartCooldown();
	void EndCooldown();

public:	// 스킬에 필요한 정보들
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name; // 스킬 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;	// 스킬 설명
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentLevel;	// 스킬의 현재 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;	// 스킬의 범위(사거리)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Cost;	// 스킬의 코스트, 사용 시 얻는 광기의 양을 의미

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondToCooldown;	// 스킬의 쿨타임
	uint8 bIsCooldown:1;
	FTimerHandle CooldownTimerHandle;

	// 아래는 굳이 여기에 없어도 될 것 같은 정보들
	//Transform CurrentCharacterPos;
	//Vector2 CurrentMousePos;
	//int32 MaxHp;
	//int32 CurrentHp;
	//int32 CharacterAtkPower;
	//int32 CharacterMovementSpeed;
	//int32 RegenHpPerSecond;
	//int32 CurrentMadness;
	/*
	* 추가로 필요한 정보(기획 회의 때 정리해야 될 부분)
		스킬 슬롯에 표시될 스킬 텍스쳐 이미지, 
		스킬 사용 시 애니메이션, 
		스킬 이펙트, 
		스킬의 종류(근거리공격, 원거리공격, 버프/디버프 등),
		스킬의 위치(Q,W,E,R),
		스킬 활성화 여부(마혈석을 얻었는가),
		스킬의 최고 레벨,
		...
	*/
};
