// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectileActor.generated.h"

UCLASS()
class KEEPER_API ABaseProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 투사체의 충돌을 확인해줄 Component
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class USphereComponent* ProjectileCollision;
	// 투사체의 Pivot, Mesh의 특정 지점을 기준으로 설정한다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	class UStaticMeshComponent* ProjectilePivot;
	// 투사체의 Mesh. Skeletal 또는 Static으로 설정된다.
	// or class UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	class USkeletalMeshComponent* ProjectileMesh;
	// 투사체의 움직임을 위한 Component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	// 노티파이에서 생성할 때 받아야 할 정보
	// 기본피해량, 일반적으로 플레이어 캐릭터의 공격력
	UPROPERTY()
	float BaseDamage; 
	// 데미지 계수, 스킬 정보(SkillDataStruct)에서 해당 데이터를 받음.
	UPROPERTY()
	float DamageCoefficient;
	// 최대 비거리, 원거리 스킬 정보에서 Range에 해당하는 정보.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	float MaxDistance;

	// 생성될 때 가지고 있어야 하는 정보
	// 최초 생성된 위치 정보, Location 정보.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	FVector SpawnedLocation;
	// 현재까지의 비행거리.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	float CurrentDistance;
	// 투사체의 반환여부, 되돌아오는 투사체라면 true.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	uint8 bCanReturn : 1;
	// 투사체가 반환점을 지났다면 true.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (EditCondition = "bCanReturn"))
	uint8 bIsReturn : 1;
	// 투사체 속도, 투사체의 비행 속도.
	UPROPERTY()
	float ProjectileSpeed;
	// 투사체 데미지필드, 투사체는 데미지필드를 가진체 스폰된다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	class ABaseSkillDamageField* ProjectileDamageField;


public:
	// 바라보는 방향으로 투사체를 날리는 함수.
	UFUNCTION(BlueprintCallable, Category = "KeeperProjectile")
	void FireInDirection(const FVector& Direction);
	// 투사체의 정보를 Set. 기본데미지, 데미지계수, 사거리를 매개변수로 받는다.
	UFUNCTION()
	void SetProjectileInfo(float Damage, float Coefficient, float Range);

	UFUNCTION(BlueprintCallable, Category = "KeeperProjectile")
	void DestroyProjectile();
};
