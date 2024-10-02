#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawn.generated.h"

class AKeeperCharacter;

UCLASS()
class KEEPER_API AMonsterSpawn : public AActor
{
	GENERATED_BODY()

public:
	AMonsterSpawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Trigger")
	class UBoxComponent* TriggerBox;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
						const FHitResult& SweepResult);

	// 스폰할 엑터
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> ActorToSpawn;

	// 스폰할 위치 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TArray<FTransform> SpawnLocations;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	UClass* TargetBlueprintClass;
};