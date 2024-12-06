// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageField_Base.h"
#include "Components/SphereComponent.h"
#include "Monster/MonsterBase.h"

// Sets default values
ADamageField_Base::ADamageField_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CachedRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(CachedRootComponent) ;

	damageRadius = 0.0;
	DamageAmount = 0.0f;
	damageCalculation = 0.0f;
	bCanDealDamage = true;
}

void ADamageField_Base::CreateDamageField_Sphere(float radius)
{
	damageRadius = radius;
	
	HitSphereComponent = NewObject<USphereComponent>(this);
	HitSphereComponent->SetSphereRadius(damageRadius);
	
	HitSphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	HitSphereComponent->SetGenerateOverlapEvents(true);

	HitSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADamageField_Base::OnOverlapBegin);
	HitSphereComponent->OnComponentEndOverlap.AddDynamic(this, &ADamageField_Base::OnOverlapEnd);

	HitSphereComponent->RegisterComponent();
	HitSphereComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	HitSphereComponent->SetLineThickness(10.0f);
}

void ADamageField_Base::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bCanDealDamage && OtherActor && OtherActor != this)
	{
		AMonsterBase* Monster = Cast<AMonsterBase>(OtherActor);
		if (Monster)
		{
			SetDamageAmount(DamageAmount);
			Monster->TakeDamage(damage);
			
			UE_LOG(LogTemp, Warning, TEXT("Damage %f applied to Monster: %s"), damage, *OtherActor->GetName());
		}
	}
}

void ADamageField_Base::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

USphereComponent* ADamageField_Base::GetHitSphereComponent() const
{
	return HitSphereComponent;
}

void ADamageField_Base::SetDamageAmount(float NewDamageAmount)
{
	damage = NewDamageAmount * damageCalculation;
}

void ADamageField_Base::ActivateDamage()
{
	bCanDealDamage = true;
}

void ADamageField_Base::DeactivateDamage()
{
	bCanDealDamage = false;
}

// Called when the game starts or when spawned
void ADamageField_Base::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADamageField_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//DrawDebugSphere(GetWorld(), GetActorLocation(), damageRadius, 12, FColor::Red, false, 1.0f);

}

