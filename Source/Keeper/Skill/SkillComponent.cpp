// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillComponent.h"
#include "Character/KeeperCharacter.h"
//#include "SkillProjectile.h"

#include "Engine/DataTable.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//FString SkillDataPath = TEXT("/Game/Blueprints/Skills/KeeperSkillData.KeeperSkillData");
	//static ConstructorHelpers::FObjectFinder<UDataTable> DT_Skill(*SkillDataPath);
	//KeeperSkillData = DT_Skill.Object;
}

//FSkillCustomData* USkillComponent::GetSkillCustomData(int32 index)
//{
//	return KeeperSkillData->FindRow<FSkillCustomData>(*FString::FromInt(index), TEXT(""));
//}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//SkillToQ = *GetSkillCustomData(1);
	//SkillToW = *GetSkillCustomData(6);
}


//
// FSkillCustomData에 정의된 함수
//

FSkillCustomData::FSkillCustomData()
{
	Name = FText::FromString(TEXT("Unknown"));
	Description = FText::FromString(TEXT("This skill does not assigned."));
	CurrentLevel = 0;
	SecondToCooldown = 5.0f;
	bIsCooldown = false;
	Range = 20.0f;

	SkillType = ESkillType::Melee;
	//Projectile = nullptr;

	PlayerPosition = FVector::Zero();
	MouseCursorPosition = FVector::Zero();

	// 기타 플레이어의 능력치들
	// (MaxHp, CurrentHp, AttackPower, MovementSpeed, GenerationHp, CurrentStackedCost)
	// 이 부분은 능력치 부분이 정의된 후 작업
	// 방법
	// 1. 델리게이트로 플레이어의 능력치에 변동이 있을 때 변경
	// 2. 스킬을 사용했을 때 플레이어의 능력치를 받아와 변경
	// 일단 2번 방법으로 작성

	Cost = -1;
}

void FSkillCustomData::Use(class AKeeperCharacter* player)
{
	UE_LOG(LogTemp, Log, TEXT("Activated Skill :: %s"), *Name.ToString());

	// 스킬 사용 시 플레이어의 위치와 마우스의 위치를 초기화
	PlayerPosition = player->GetActorLocation();
	APlayerController* MyPlayerController;
	MyPlayerController = player->GetWorld()->GetFirstPlayerController();
	if (MyPlayerController)
	{
		FHitResult Hit;
		MyPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			MouseCursorPosition = Hit.ImpactPoint;
		}

		UE_LOG(LogTemp, Log, TEXT("PlayerPos	:: %f, %f, %f"), PlayerPosition.X, PlayerPosition.Y, PlayerPosition.Z);
		UE_LOG(LogTemp, Log, TEXT("MousePos		:: %f, %f, %f"), MouseCursorPosition.X, MouseCursorPosition.Y, MouseCursorPosition.Z);
	}
	else UE_LOG(LogTemp, Warning, TEXT("Not Found PlayerController!"));

	// 타입별로 구분해서 구조체 내에 입력된 정보에 따라 스킬을 활성화
	switch (SkillType)
	{
	case ESkillType::Melee:
		UE_LOG(LogTemp, Log, TEXT("Melee Skill"));
		DrawDebugSphere(player->GetWorld(), PlayerPosition + player->GetActorForwardVector() * 100.0f, Range, 26, FColor::Red, false, 3.0f, 0, 2);
		break;

	case ESkillType::Ranged:
	{
		UE_LOG(LogTemp, Log, TEXT("Ranged Skill"));
		//static ConstructorHelpers::FClassFinder<AActor>ProjectileRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Skills/BP_CTestProjectile.BP_CTestProjectile'"));
		FVector newDir = MouseCursorPosition - PlayerPosition;
		newDir.Z = 0.0f;
		//if (Projectile) {
		//	FVector PlayerLocation = FVector(PlayerPosition.X, PlayerPosition.Y, 60.0f);
		//	TObjectPtr<ASkillProjectile> TempProjectile = Cast<ASkillProjectile>(player->GetWorld()->SpawnActor(Projectile, &PlayerLocation));
		//	if (TempProjectile) TempProjectile->ShootProjectile(newDir);
		//}
		break;
	}

	default:
		break;
	}
}