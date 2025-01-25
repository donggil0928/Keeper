// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "DialogueData.h"
#include "GameFramework/Actor.h"
#include "DialogueManager.generated.h"

class UDialogueWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogEventSignature, FName, EventTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogEndedSignature);

UCLASS()
class KEEPER_API ADialogueManager : public AActor
{
    GENERATED_BODY()

public:
    ADialogueManager();

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FDialogueSequence DialogueSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    TSubclassOf<UDialogueWidget> DialogueWidgetClass;
    
    UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
    UDialogueWidget* DialogueWidget;

    UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
    bool bIsDialogueActive;

    UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
    bool bIsPaused;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    TMap<FName, float> DialogueVariables;

    // Events
    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnDialogEventSignature OnDialogEvent;

    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnDialogEndedSignature OnDialogEnded;

    // Public functions
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void StartDialogue();

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void EndDialogue();

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void PauseDialogue();

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void ResumeDialogue();
    
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void HandleInput();

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void ProgressToNextDialogue();

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void JumpToDialogueIndex(int32 Index);
    
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void SetDialogueVariable(FName Name, float Value);

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    float GetDialogueVariable(FName Name) const;

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void OnNextButtonClicked();
    
    UFUNCTION(BlueprintPure, Category = "Dialogue")
    bool IsDialogueActive() const { return bIsDialogueActive; }

    UFUNCTION(BlueprintPure, Category = "Dialogue")
    bool IsPaused() const { return bIsPaused; }

protected:
    UPROPERTY()
    int32 CurrentDialogueIndex;

    UPROPERTY()
    FTimerHandle AutoProgressTimer;

    void ShowCurrentDialogue();
    void SetupInputBinding();
    bool CheckDialogueConditions(const FDialogueData& DialogueData) const;
    void ProcessDialogueEvents(const FDialogueData& DialogueData);

private:
    void HandleNextDialogueInput();
    void CreateDialogueWidget();
    void RemoveDialogueWidget();
    void CleanupDialogue();
};