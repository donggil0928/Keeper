// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KeeperCharacterController.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Character/KeeperCharacter.h"

AKeeperCharacterController::AKeeperCharacterController(): DefaultMappingContext(nullptr), RightClickAction(nullptr),
                                                          LeftClickAction(nullptr),
                                                          DodgeAction(nullptr),
                                                          TabAction(nullptr),
                                                          SkillQAction(nullptr),
                                                          CurrentTabMenuWidget(nullptr)
{
	bShowMouseCursor = true;
	MyChar = nullptr;
}

void AKeeperCharacterController::BeginPlay()
{
 	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
    
	MyChar = Cast<AKeeperCharacter>(GetPawn());
}

void AKeeperCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
    
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this, &AKeeperCharacterController::OnRightClick);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &AKeeperCharacterController::OnLeftClickPressed);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &AKeeperCharacterController::OnLeftClickReleased);
		EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Started, this, &AKeeperCharacterController::OnTabPressed);
		EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Completed, this, &AKeeperCharacterController::OnTabReleased);
		EnhancedInputComponent->BindAction(SkillQAction, ETriggerEvent::Started, this, &AKeeperCharacterController::UseQSkill);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &AKeeperCharacterController::Dodge);
	}
}

void AKeeperCharacterController::Dodge()
{
	if (AKeeperCharacter* KeeperChar = Cast<AKeeperCharacter>(GetPawn()))
	{
		KeeperChar->ExecuteDodge();
	}
}

void AKeeperCharacterController::OnRightClick(const FInputActionValue& Value)
{
	AKeeperCharacter* KeeperChar = Cast<AKeeperCharacter>(GetPawn());
	if (!KeeperChar || KeeperChar->IsPerformingAction())
		return;

	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		SetNewDestination(Hit.Location);
	}
}

void AKeeperCharacterController::SetNewDestination(const FVector& DestLocation)
{
	
	AKeeperCharacter* KeeperChar = Cast<AKeeperCharacter>(GetPawn());
	if (!KeeperChar)
		return;

	USkeletalMeshComponent* CharacterMesh = KeeperChar->GetMesh();
	if (CharacterMesh->GetAnimInstance()->IsAnyMontagePlaying())
	{
		return;
	}
	
	float const Distance = FVector::Distance(DestLocation, KeeperChar->GetActorLocation());
    
	if (Distance > MinMoveDistance)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		
		FVector Direction = (DestLocation - KeeperChar->GetActorLocation()).GetSafeNormal();
		FRotator NewRotation = Direction.Rotation();
		NewRotation.Pitch = 0.0f;
		NewRotation.Roll = 0.0f;
		KeeperChar->SetActorRotation(NewRotation);
	}
}

void AKeeperCharacterController::OnLeftClickPressed()
{
	if (MyChar)
	{
		MyChar->AttackDown();
	}
}
void AKeeperCharacterController::OnLeftClickReleased()
{
	if (MyChar)
	{
		MyChar->AttackUp();
	}
}

void AKeeperCharacterController::OnTabPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory 생성"));
	
	if (TabMenuWidgetClass && !CurrentTabMenuWidget)
	{
		CurrentTabMenuWidget = CreateWidget<UUserWidget>(this, TabMenuWidgetClass);
        
		if (CurrentTabMenuWidget)
		{
			CurrentTabMenuWidget->AddToViewport();
			
			//FInputModeUIOnly InputMode;
			//SetInputMode(InputMode);
		}
	}
}

void AKeeperCharacterController::OnTabReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory 삭제"));
	
	if (CurrentTabMenuWidget)
	{
		CurrentTabMenuWidget->RemoveFromViewport();
		CurrentTabMenuWidget = nullptr;
	}
}

void AKeeperCharacterController::UseSkill(int SkillIndex)
{
	if (!MyChar) return;
	
	AKeeperCharacter* Char = Cast<AKeeperCharacter>(GetPawn());
	Char->UseSkill(SkillIndex);
}

void AKeeperCharacterController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

