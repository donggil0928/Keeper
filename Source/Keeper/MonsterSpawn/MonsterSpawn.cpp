#include "MonsterSpawn/MonsterSpawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AMonsterSpawn::AMonsterSpawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMonsterSpawn::OnOverlapBegin);
}

void AMonsterSpawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterSpawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
									 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
									 bool bFromSweep, const FHitResult& SweepResult)
{
	// OtherActor가 유효하고 자신이 아닌 경우 처리
	if (OtherActor && (OtherActor != this))
	{
		// 충돌한 액터가 플레이어인지 확인
		if (OtherActor->IsA(TargetBlueprintClass))
		{
			// 스폰할 엑터 클래스가 설정되어 있는지 확인
			if (ActorToSpawn)
			{
				// 스폰할 위치 배열을 순회하며 엑터를 스폰
				for (const FTransform& Transform : SpawnLocations)
				{
					GetWorld()->SpawnActor<AActor>(ActorToSpawn, Transform);
				}

				// 첫 충돌 후 스폰을 한 번만 하기 위해, 필요시 트리거를 비활성화
				TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
	}
}

