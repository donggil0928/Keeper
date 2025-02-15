// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillDataStruct.h"

#include "SkillUI/SkillWindowWidgetInterface.h"

#include "SkillComponent.generated.h"

DECLARE_DELEGATE(FOnSkillChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KEEPER_API USkillComponent : public UActorComponent, public ISkillWindowWidgetInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

private:
	UPROPERTY()
	class UDataTable* SkillDataTable;

public:
	FORCEINLINE UDataTable* GetSkillDataTable() { return SkillDataTable; };
	UFUNCTION(BlueprintCallable)
	FSkillDataStruct GetSkillDataRow(int32 index);
	int32 GetSkillDataIndexToCurrentLevel(ESkillKeyMapping key, ESkillSetType skillSet, int32 currentSkillLevel);
	int32 GetSkillLevelIndex(ESkillKeyMapping InKey, ESkillSetType SkillSet);

	virtual void SetupSelectedSkillData(class USkillSlot* InSlot) override;
	virtual void ModifySkillLevel(USkillSlot* InSlot, ESkillKeyMapping InKey) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	TMap<ESkillKeyMapping, FSkillDataStruct> Skills;

	//스킬 인덱스로 정보줘서 키 맵핑하기
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Skill)
	TArray<int32> SkillLevelArray;

	FOnSkillChanged OnSkillChanged;

	ESkillSetType PrevSkillSetData;
};
