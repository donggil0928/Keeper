// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillActor/BaseProjectileActor.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Skill/BaseSkillDamageField.h"
#include "Character/KeeperCharacter.h"
#include "Monster/MonsterBase.h"


// Sets default values
ABaseProjectileActor::ABaseProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ProjectileSpeed = 300.0f;


	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	ProjectileCollision->InitSphereRadius(10.0f);
	RootComponent = ProjectileCollision;

	ProjectilePivot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pivot"));
	ProjectilePivot->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	ProjectileMesh->AttachToComponent(ProjectilePivot, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->SetUpdatedComponent(ProjectileCollision);
	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileSpeed;
	ProjectileMovement->bRotationFollowsVelocity = false;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void ABaseProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnedLocation = GetActorLocation();

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform ActorTransform = GetTransform();
	FTransform DamageFieldTransform;
	DamageFieldTransform.SetLocation(FVector::Zero());
	DamageFieldTransform.SetRotation(ActorTransform.GetRotation());
	DamageFieldTransform.SetScale3D(FVector::One());

	ProjectileDamageField = GetWorld()->SpawnActor<ABaseSkillDamageField>(ABaseSkillDamageField::StaticClass(), DamageFieldTransform, SpawnInfo);
	ProjectileDamageField->CreateDamageField_Sphere(100.0f , BaseDamage * DamageCoefficient);
	ProjectileDamageField->AttachToComponent(ProjectilePivot, FAttachmentTransformRules::KeepRelativeTransform);

	FireInDirection(GetActorForwardVector());
}

void ABaseProjectileActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

// Called every frame
void ABaseProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectileActor::FireInDirection(const FVector& Direction)
{
	ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
}

void ABaseProjectileActor::SetProjectileInfo(float Damage, float Coefficient, float Range)
{
	BaseDamage = Damage;
	DamageCoefficient = Coefficient;
	MaxDistance = Range * 5.0f;

	ProjectileDamageField->SetDamage(BaseDamage * DamageCoefficient);
}

void ABaseProjectileActor::DestroyProjectile()
{
	ProjectileDamageField->Destroy();
	Destroy();
}


