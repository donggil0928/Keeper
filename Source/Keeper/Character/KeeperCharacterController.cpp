// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KeeperCharacterController.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Character/KeeperCharacter.h"

AKeeperCharacterController::AKeeperCharacterController()
// DefaultMappingContext(nullptr), RightClickAction(nullptr),
//                                                           LeftClickAction(nullptr),
//                                                           DodgeAction(nullptr),
//                                                           TabAction(nullptr),
//                                                           SkillQAction(nullptr),
//                                                           CurrentTabMenuWidget(nullptr)
{
	bShowMouseCursor = true;
	MyChar = nullptr;

	static ConstructorHelpers::FObjectFinder<UInputAction> SkillPopupRef = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/SkillAction/IA_SkillPopup.IA_SkillPopup'");
	if (SkillPopupRef.Object) SkillPopupAction = SkillPopupRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> QSkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/SkillAction/IA_Skill_Q.IA_Skill_Q'"));
	if(QSkillActionRef.Succeeded()) QSkillAction = QSkillActionRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> WSkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/SkillAction/IA_Skill_W.IA_Skill_W'"));
	if(WSkillActionRef.Succeeded()) WSkillAction= WSkillActionRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> ESkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/SkillAction/IA_Skill_E.IA_Skill_E'"));
	if(ESkillActionRef.Succeeded()) ESkillAction = ESkillActionRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> RSkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/SkillAction/IA_Skill_R.IA_Skill_R'"));
	if(RSkillActionRef.Succeeded()) RSkillAction = RSkillActionRef.Object;
}

void AKeeperCharacterController::SetLastClickedLocation(const FVector& Location)
{
	LastClickedLocation = Location;
}

FVector AKeeperCharacterController::GetLastClickedLocation() const
{
	return LastClickedLocation;
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
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &AKeeperCharacterController::Dodge);

		EnhancedInputComponent->BindAction(ESCMenuAction, ETriggerEvent::Started, this, &AKeeperCharacterController::OnESCPressed);
		
		EnhancedInputComponent->BindAction(SkillPopupAction, ETriggerEvent::Started, this, &AKeeperCharacterController::OnSkillPopupPressed);
		EnhancedInputComponent->BindAction(QSkillAction, ETriggerEvent::Started, this, &AKeeperCharacterController::OnButtonQPressed);
		EnhancedInputComponent->BindAction(WSkillAction, ETriggerEvent::Started, this, &AKeeperCharacterController::OnButtonWPressed);
		EnhancedInputComponent->BindAction(ESkillAction, ETriggerEvent::Started, this, &AKeeperCharacterController::OnButtonEPressed);
		EnhancedInputComponent->BindAction(RSkillAction, ETriggerEvent::Started, this, &AKeeperCharacterController::OnButtonRPressed);
		
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
	{
		UE_LOG(LogTemp, Warning, TEXT("KeeperChar is null"));
		return;
	}

	USkeletalMeshComponent* CharacterMesh = KeeperChar->GetMesh();
	if (!CharacterMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterMesh is null"));
		return;
	}
        
	UAnimInstance* AnimInstance = CharacterMesh->GetAnimInstance();
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimInstance is null"));
		return;
	}

	if (AnimInstance->IsAnyMontagePlaying())
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
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	SetLastClickedLocation(HitResult.Location);
	
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
		CurrentTabMenuWidget->RemoveFromParent();
		CurrentTabMenuWidget = nullptr;
	}
}

void AKeeperCharacterController::OnESCPressed()
{
	if (CurrentSkillPopupWidget)
	{
		CurrentSkillPopupWidget->RemoveFromParent();
		CurrentSkillPopupWidget = nullptr;
	}
	
	if (ESCMenuWidgetClass && !CurrentESCMenuWidget)
	{
		CurrentESCMenuWidget = CreateWidget<UUserWidget>(this, ESCMenuWidgetClass);

		if (CurrentESCMenuWidget)
		{
			CurrentESCMenuWidget->AddToViewport();
		}
	}
	else if (CurrentESCMenuWidget)
	{
		CurrentESCMenuWidget->RemoveFromParent();
		CurrentESCMenuWidget = nullptr;
	}
}

void AKeeperCharacterController::OnSkillPopupPressed()
{
	if (SkillPopupWidgetClass && !CurrentSkillPopupWidget)
	{
		CurrentSkillPopupWidget = CreateWidget<UUserWidget>(this, SkillPopupWidgetClass);

		if (CurrentSkillPopupWidget) CurrentSkillPopupWidget->AddToViewport();
	}
	else if (CurrentSkillPopupWidget)
	{
		CurrentSkillPopupWidget->RemoveFromParent();
		CurrentSkillPopupWidget = nullptr;
	}
}

void AKeeperCharacterController::OnButtonQPressed()
{
	if (MyChar)
	{
		MyChar->ActivateSkill(ESkillKeyMapping::Q);
	}
}

void AKeeperCharacterController::OnButtonWPressed()
{
	if (MyChar)
	{
		MyChar->ActivateSkill(ESkillKeyMapping::W);
	}
}

void AKeeperCharacterController::OnButtonEPressed()
{
	if (MyChar)
	{
		MyChar->ActivateSkill(ESkillKeyMapping::E);
	}
}

void AKeeperCharacterController::OnButtonRPressed()
{
	if (MyChar)
	{
		MyChar->ActivateSkill(ESkillKeyMapping::R);
	}
}

void AKeeperCharacterController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

