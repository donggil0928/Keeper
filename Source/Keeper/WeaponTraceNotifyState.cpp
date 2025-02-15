#include "WeaponTraceNotifyState.h"
#include "Character/KeeperCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster/MonsterBase.h"

void UWeaponTraceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration);

    AlreadyHitActors.Empty();

    bIsFirstTick = true;
    
    AKeeperCharacter* KeeperCharacter = Cast<AKeeperCharacter>(MeshComp->GetOwner());
    if (!KeeperCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("WeaponTraceNotifyState: Could not find KeeperCharacter"));
        return;
    }
}

void UWeaponTraceNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
    
    AKeeperCharacter* KeeperCharacter = Cast<AKeeperCharacter>(MeshComp->GetOwner());
    if (!KeeperCharacter)
    {
        return;
    }

    USkeletalMeshComponent* WeaponMesh = KeeperCharacter->WeaponMeshComponent;
    if (!WeaponMesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("WeaponTraceNotifyState: Could not find WeaponMesh component"));
        return;
    }

    // 현재 소켓 위치
    FVector CurrentSocket1Location;
    FVector CurrentSocket2Location;
    FTransform Socket1Transform;
    FTransform Socket2Transform;
    bool bHasSocket1 = false;
    bool bHasSocket2 = false;
    
    // 무기 메시의 각 소켓에 대해 트레이스
    if (KeeperCharacter->WeaponMeshComponent->DoesSocketExist(Socket1Name))
    {
        Socket1Transform = KeeperCharacter->WeaponMeshComponent->GetSocketTransform(Socket1Name);
        CurrentSocket1Location = Socket1Transform.GetLocation();
        bHasSocket1 = true;
        
        // 디버그 구체 그리기
        DrawDebugSphere(
            KeeperCharacter->GetWorld(), 
            CurrentSocket1Location, 
            TraceRadius, 
            16, 
            FColor::Red, 
            false, 
            -1.0f
        );
        
        if (!bIsFirstTick)
        {
            PerformWeaponLineTrace(KeeperCharacter, PreviousSocket1Location, CurrentSocket1Location);
        }
        PerformWeaponTraceForSocket(KeeperCharacter->WeaponMeshComponent, KeeperCharacter, Socket1Name);
    }
    
    if (KeeperCharacter->WeaponMeshComponent->DoesSocketExist(Socket2Name))
    {
        Socket2Transform = KeeperCharacter->WeaponMeshComponent->GetSocketTransform(Socket2Name);
        CurrentSocket2Location = Socket2Transform.GetLocation();
        bHasSocket2 = true;
        
        // 디버그 구체 그리기
        DrawDebugSphere(
            KeeperCharacter->GetWorld(), 
            CurrentSocket2Location, 
            TraceRadius, 
            16, 
            FColor::Red, 
            false, 
            -1.0f
        );
        
        if (!bIsFirstTick)
        {
            PerformWeaponLineTrace(KeeperCharacter, PreviousSocket2Location, CurrentSocket2Location);
        }
        PerformWeaponTraceForSocket(KeeperCharacter->WeaponMeshComponent, KeeperCharacter, Socket2Name);
    }
    
    if (bHasSocket1 && bHasSocket2)
    {
        PerformWeaponLineTrace(KeeperCharacter, CurrentSocket1Location, CurrentSocket2Location);
        
        if (!bIsFirstTick)
        {
            PerformWeaponLineTrace(KeeperCharacter, PreviousSocket1Location, CurrentSocket2Location);
            PerformWeaponLineTrace(KeeperCharacter, PreviousSocket2Location, CurrentSocket1Location);
        }
    }
    
    if (bHasSocket1)
    {
        PreviousSocket1Location = CurrentSocket1Location;
    }
    if (bHasSocket2)
    {
        PreviousSocket2Location = CurrentSocket2Location;
    }
    
    bIsFirstTick = false; 
}

// void UWeaponTraceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
// {
//     Super::NotifyEnd(MeshComp, Animation);
//     bIsFirstTick = true;
// }

void UWeaponTraceNotifyState::PerformWeaponLineTrace(AKeeperCharacter* KeeperCharacter, const FVector& StartLocation, const FVector& EndLocation)
{
    if (!KeeperCharacter || !KeeperCharacter->GetWorld())
    {
        return;
    }
    
    TArray<AActor*> IgnoredActors;
    IgnoredActors.Add(KeeperCharacter);
    
    TArray<FHitResult> HitResults;
    
    // 디버그 라인 그리기
    DrawDebugLine(
        KeeperCharacter->GetWorld(),
        StartLocation,
        EndLocation,
        FColor::Blue,
        false,
        -1.0f,
        0,
        2.0f
    );
    
    // 원통형 트레이스 수행
    bool bHit = UKismetSystemLibrary::SphereTraceMulti(
        KeeperCharacter->GetWorld(),
        StartLocation,
        EndLocation,
        TraceRadius,
        UEngineTypes::ConvertToTraceType(ECC_Pawn),
        false,
        IgnoredActors,
        EDrawDebugTrace::ForDuration,
        HitResults,
        true,
        FLinearColor::Red,
        FLinearColor::Green,
        1.0f
    );
    
    if (bHit)
    {
        for (const FHitResult& HitResult : HitResults)
        {
            AActor* HitActor = HitResult.GetActor();
            if (!IsValid(HitActor))
            {
                continue;
            }
            
            AMonsterBase* HitMonster = Cast<AMonsterBase>(HitActor);
            if (!HitMonster)  // 몬스터가 아니면 스킵
            {
                continue;
            }
            
            if (AlreadyHitActors.Contains(HitActor))
            {
                continue;
            }
            
            if (IsValid(KeeperCharacter))
            {
                float FinalDamage = KeeperCharacter->AttackPower * DamageMultiplier;
                //KeeperCharacter->DealDamage(HitMonster, FinalDamage);
                AlreadyHitActors.Add(HitActor);
            }
        }
    }
}

void UWeaponTraceNotifyState::PerformWeaponTraceForSocket(USkeletalMeshComponent* WeaponMesh, AKeeperCharacter* KeeperCharacter, FName SocketName)
{
    if (!WeaponMesh || !KeeperCharacter)
    {
        return;
    }
    
    FTransform WeaponSocketTransform = WeaponMesh->GetSocketTransform(SocketName);
    
    TArray<AActor*> IgnoredActors;
    IgnoredActors.Add(KeeperCharacter);
    
    TArray<FHitResult> HitResults;
    
    bool bHit = UKismetSystemLibrary::SphereTraceMulti(
        KeeperCharacter->GetWorld(),
        WeaponSocketTransform.GetLocation(),
        WeaponSocketTransform.GetLocation(),
        TraceRadius,
        UEngineTypes::ConvertToTraceType(ECC_Pawn),
        false,
        IgnoredActors,
        EDrawDebugTrace::ForDuration,
        HitResults,
        true,
        FLinearColor::Red,
        FLinearColor::Green,
        1.0f
    );
    
    if (bHit)
    {
        for (FHitResult& HitResult : HitResults)
        {
            ACharacter* HitCharacter = Cast<ACharacter>(HitResult.GetActor());
            if (HitCharacter && 
                HitCharacter != KeeperCharacter && 
                !AlreadyHitActors.Contains(HitCharacter))
            {
                float FinalDamage = KeeperCharacter->AttackPower * DamageMultiplier;
                //KeeperCharacter->DealDamage(HitCharacter, FinalDamage);
                AlreadyHitActors.Add(HitCharacter);
            }
        }
    }
}