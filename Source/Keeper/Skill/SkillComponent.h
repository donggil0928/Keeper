// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillDataStruct.h"
#include "SkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KEEPER_API USkillComponent : public UActorComponent
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

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = Skill)
	TSubclassOf<class UUserWidget> SkillWindowWidget;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	TMap<ESkillKeyMapping, FSkillDataStruct> Skills;

	//스킬 인덱스로 정보줘서 키 맵핑하기
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Skill)
	TArray<int32> SkillLevelArray;

	//설정한 키를 입력했을 때 정상적으로 정보를 출력하는지 확인
	//스킬에 필요한 정보 다시 정리해서 구조체 재작성하기

	//스킬 UI, 아이템 UI 등을 위한 Slot 작성
	//스킬이 Slot을 통해 스왑되게 하기

};
