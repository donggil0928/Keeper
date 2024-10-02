// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageField_Base.h"

#include "Components/SphereComponent.h"

// Sets default values
ADamageField_Base::ADamageField_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CachedRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	SetRootComponent(CachedRootComponent) ;
	damageRadius = 0.0;
}

void ADamageField_Base::CreateDamageField_Sphere(float radius)
{
	damageRadius = radius;
	
	HitSphereComponent = NewObject<USphereComponent>(this);
	HitSphereComponent->SetSphereRadius(damageRadius);

	HitSphereComponent->RegisterComponent();
	HitSphereComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	HitSphereComponent->SetLineThickness(10.0f);

	
}

USphereComponent* ADamageField_Base::GetHitSphereComponent() const
{
	return HitSphereComponent;
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

