// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "WeaponTraceNotifyState.generated.h"

class AKeeperCharacter;

UCLASS()
class KEEPER_API UWeaponTraceNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Weapon Trace")
	FName WeaponSocketName = TEXT("WeaponSocket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Trace")
	float TraceRadius = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Weapon Trace")
	float DamageMultiplier = 1.0f;
	
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
    virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
    //virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName Socket1Name = FName("WeaponSocket1");

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName Socket2Name = FName("WeaponSocket2");
	
private:

	UPROPERTY()
	FVector PreviousSocket1Location;

	UPROPERTY()
	FVector PreviousSocket2Location;

	UPROPERTY()
	 bool bIsFirstTick;
	
	UPROPERTY()
	TArray<AActor*> AlreadyHitActors;

	void PerformWeaponTraceForSocket(USkeletalMeshComponent* WeaponMesh, AKeeperCharacter* KeeperCharacter, FName SocketName);
	void PerformWeaponLineTrace(AKeeperCharacter* KeeperCharacter, const FVector& StartLocation, const FVector& EndLocation);
};
