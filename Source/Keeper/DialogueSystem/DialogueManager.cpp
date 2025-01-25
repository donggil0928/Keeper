// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueManager.h"
#include "DialogueWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameViewportClient.h"

ADialogueManager::ADialogueManager()
{
    PrimaryActorTick.bCanEverTick = false;
    CurrentDialogueIndex = 0;
    bIsDialogueActive = false;
    bIsPaused = false;
}

void ADialogueManager::BeginPlay()
{
    Super::BeginPlay();
    SetupInputBinding();
}

void ADialogueManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    CleanupDialogue();
}

void ADialogueManager::StartDialogue()
{
    if (DialogueSequence.IsValid())
    {
        bIsDialogueActive = true;
        CurrentDialogueIndex = DialogueSequence.StartIndex;

        if (!DialogueWidgetClass)
        {
            return;
        }
        
        CreateDialogueWidget();
        ShowCurrentDialogue();
    }
}

void ADialogueManager::EndDialogue()
{
    CleanupDialogue();
    OnDialogEnded.Broadcast();
}

void ADialogueManager::ShowCurrentDialogue()
{
    if (!DialogueWidget || !DialogueSequence.IsValid())
    {
        return;
    }

    const FDialogueData* CurrentDialogue = DialogueSequence.GetDialogueAt(CurrentDialogueIndex);
    if (!CurrentDialogue)
    {
        return;
    }
    
    DialogueWidget->ShowDialogue(*CurrentDialogue);
    ProcessDialogueEvents(*CurrentDialogue);
}

void ADialogueManager::HandleInput()
{
    if (!bIsDialogueActive || bIsPaused) 
    {
        return;
    }
    
    const FDialogueData* CurrentDialogue = DialogueSequence.GetDialogueAt(CurrentDialogueIndex);
    if (!CurrentDialogue)
    {
        return;
    }
    
    GetWorld()->GetTimerManager().ClearTimer(AutoProgressTimer);
    
    if (CurrentDialogue->bRequireConfirmation && !CurrentDialogue->bCanBeSkipped)
    {
        return;
    }

    UE_LOG(LogTemp,Warning,TEXT("HandleInput : %d"),CurrentDialogueIndex);
    CurrentDialogueIndex++;
    ProgressToNextDialogue();
}

void ADialogueManager::ProgressToNextDialogue()
{
    UE_LOG(LogTemp,Warning,TEXT("ProgressToNextDialogue : %d"),CurrentDialogueIndex);
    //CurrentDialogueIndex++;
    
    if (CurrentDialogueIndex >= DialogueSequence.GetLength())
    {
        if (DialogueSequence.bLoopSequence)
        {
            CurrentDialogueIndex = 0;
        }
        else
        {
            EndDialogue();
            return;
        }
    }

    ShowCurrentDialogue();
}

void ADialogueManager::JumpToDialogueIndex(int32 Index)
{
    if (DialogueSequence.DialogueEntries.IsValidIndex(Index))
    {
        CurrentDialogueIndex = Index;
        ShowCurrentDialogue();
    }
}

void ADialogueManager::ProcessDialogueEvents(const FDialogueData& DialogueData)
{
    if (!DialogueData.CustomEventTag.IsNone())
    {
        OnDialogEvent.Broadcast(DialogueData.CustomEventTag);
    }
}

void ADialogueManager::HandleNextDialogueInput()
{
    UE_LOG(LogTemp,Warning,TEXT("HandleNextDialogueInput : %d"),CurrentDialogueIndex);
    HandleInput();
}

void ADialogueManager::SetupInputBinding()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC && PC->InputComponent)
    {
        PC->InputComponent->BindAction("NextDialog", IE_Pressed, this, &ADialogueManager::HandleNextDialogueInput);
        //PC->InputComponent->BindAction("SkipDialog", IE_Pressed, this, &ADialogueManager::HandleSkipDialogueInput);
    }
}

bool ADialogueManager::CheckDialogueConditions(const FDialogueData& DialogueData) const
{
    if (!DialogueData.IsValid())
    {
        return false;
    }
    
    if (DialogueData.HasVoiceOver())
    {
        if (!DialogueData.AudioData.VoiceSound)
        {
            return false;
        }
    }
    
    if (DialogueData.bShowPortrait && !DialogueData.CharacterPortrait)
    {
        return false;
    }
    
    if (DialogueData.bUseTypewriterEffect && DialogueData.TypewriterSpeed <= 0.0f)
    {
        return false;
    }
    
    if (!DialogueData.bRequireConfirmation && DialogueData.DisplayDuration <= 0.0f)
    {
        return false;
    }

    if (!DialogueData.CustomEventTag.IsNone())
    {
        const float* Value = DialogueVariables.Find(DialogueData.CustomEventTag);
        if (!Value)
        {
            return false;
        }
    }

    return true;
}

void ADialogueManager::CreateDialogueWidget()
{
    if (!DialogueWidgetClass)
    {
        return;
    }
    
    if (!DialogueWidget)
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (!PC)
        {
            return;
        }
        
        DialogueWidget = CreateWidget<UDialogueWidget>(PC, DialogueWidgetClass);
        if (!DialogueWidget)
        {
            return;
        }
        
        DialogueWidget->OnNextButtonClickedDelegate.AddDynamic(this, &ADialogueManager::OnNextButtonClicked);
        DialogueWidget->AddToViewport();
        DialogueWidget->SetVisibility(ESlateVisibility::Visible);
        
        PC->bShowMouseCursor = true;
        FInputModeUIOnly InputMode;
        PC->SetInputMode(InputMode);
    }
}

void ADialogueManager::RemoveDialogueWidget()
{
    if (DialogueWidget)
    {
        DialogueWidget->RemoveFromParent();
        DialogueWidget = nullptr;
        
        if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
        {
            PC->bShowMouseCursor = true;
            FInputModeGameOnly InputMode;
            PC->SetInputMode(InputMode);

            if (UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport())
            {
                ViewportClient->SetMouseLockMode(EMouseLockMode::DoNotLock);
                ViewportClient->SetMouseCaptureMode(EMouseCaptureMode::CaptureDuringMouseDown);
            }
        }
    }
}

void ADialogueManager::CleanupDialogue()
{
    bIsDialogueActive = false;
    bIsPaused = false;
    GetWorld()->GetTimerManager().ClearTimer(AutoProgressTimer);
    RemoveDialogueWidget();
}

void ADialogueManager::PauseDialogue()
{
    bIsPaused = true;
    GetWorld()->GetTimerManager().PauseTimer(AutoProgressTimer);
}

void ADialogueManager::ResumeDialogue()
{
    bIsPaused = false;
    GetWorld()->GetTimerManager().UnPauseTimer(AutoProgressTimer);
}

void ADialogueManager::SetDialogueVariable(FName Name, float Value)
{
    DialogueVariables.Add(Name, Value);
}

float ADialogueManager::GetDialogueVariable(FName Name) const
{
    const float* Value = DialogueVariables.Find(Name);
    return Value ? *Value : 0.0f;
}

void ADialogueManager::OnNextButtonClicked()
{
    HandleInput();
}

//