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
	
	InputComponent->BindAction<FUseSkillDelegate>("QSkill", IE_Pressed, this, &AKeeperCharacterController::UseSkill, 0);	// 가독성을 위해 ENUM 타입으로 수정 고려, EX) Skills[ESkillKey::Key_Q].GetDefaultObject()
	//InputComponent->BindAction<FUseSkillDelegate>("WSkill", IE_Pressed, this, &AClickMovePlayerController::UseSkill, 1);	// �������� ���� ENUM Ÿ������ ���� ���, EX) Skills[ESkillKey::Key_Q].GetDefaultObject()
	//InputComponent->BindAction<FUseSkillDelegate>("ESkill", IE_Pressed, this, &AClickMovePlayerController::UseSkill, 2);	// �������� ���� ENUM Ÿ������ ���� ���, EX) Skills[ESkillKey::Key_Q].GetDefaultObject()
	//InputComponent->BindAction<FUseSkillDelegate>("RSkill", IE_Pressed, this, &AClickMovePlayerController::UseSkill, 3);	// �������� ���� ENUM Ÿ������ ���� ���, EX) Skills[ESkillKey::Key_Q].GetDefaultObject()
    	
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

	if (bClickRightMouse)
		MoveToMouseCursor();
}

