// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KeeperCharacterController.h"
#include "Blueprint/UserWidget.h"
#include "Character/KeeperCharacter.h"

AKeeperCharacterController::AKeeperCharacterController()
{
	bShowMouseCursor = true;
	bClickRightMouse = false; //
	MyChar = nullptr; //
}

 void AKeeperCharacterController::BeginPlay()
 {
 	Super::BeginPlay();
	
 	APawn* MyPawn = GetPawn();
	
	AKeeperCharacter* Char = Cast<AKeeperCharacter>(MyPawn);
	if (Char)
	{
		MyChar = Char;
	}
	else
	{
		MyChar = nullptr;
	}
 }

void AKeeperCharacterController::InputRightMouseButtonPressed()
{
	bClickRightMouse = true;
}

void AKeeperCharacterController::InputRightMouseButtonReleased()
{
	bClickRightMouse = false;
}

void AKeeperCharacterController::SetNewDestination( const FVector Destination)
{
	if (MyChar)
	{
		MyChar->SetNewDestination(this, Destination);
	}
}

void AKeeperCharacterController::MoveToMouseCursor()
{
	if (!MyChar) return;
	
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
		SetNewDestination(Hit.ImpactPoint);
}

void AKeeperCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("RightClick", IE_Pressed, this, &AKeeperCharacterController::InputRightMouseButtonPressed);
	InputComponent->BindAction("RightClick", IE_Released, this, &AKeeperCharacterController::InputRightMouseButtonReleased);

	
	
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AKeeperCharacterController::OnLeftClickPressed);
	InputComponent->BindAction("LeftClick", IE_Released, this, &AKeeperCharacterController::OnLeftClickReleased);

	if (InputComponent)
	{
		InputComponent->BindAction("Inventory", IE_Pressed, this, &AKeeperCharacterController::OnTabPressed);
		InputComponent->BindAction("Inventory", IE_Released, this, &AKeeperCharacterController::OnTabReleased);
	}

	//------------------스킬 사용 관련------------------

	InputComponent->BindAction("QSkill", IE_Pressed, this, &AKeeperCharacterController::OnButtonQPressed);
	InputComponent->BindAction("WSkill", IE_Pressed, this, &AKeeperCharacterController::OnButtonWPressed);
	InputComponent->BindAction("ESkill", IE_Pressed, this, &AKeeperCharacterController::OnButtonEPressed);
	InputComponent->BindAction("RSkill", IE_Pressed, this, &AKeeperCharacterController::OnButtonRPressed);

	//-------------------------------------------------   	
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

void AKeeperCharacterController::OnButtonQPressed()
{
	if (MyChar)
	{
		MyChar->SkillActivatedQ();
	}
}

void AKeeperCharacterController::OnButtonWPressed()
{
	if (MyChar)
	{
		MyChar->SkillActivatedW();
	}
}

void AKeeperCharacterController::OnButtonEPressed()
{
	if (MyChar)
	{
		MyChar->SkillActivatedE();
	}
}

void AKeeperCharacterController::OnButtonRPressed()
{
	if (MyChar)
	{
		MyChar->SkillActivatedR();
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

void AKeeperCharacterController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bClickRightMouse)
		MoveToMouseCursor();
}

