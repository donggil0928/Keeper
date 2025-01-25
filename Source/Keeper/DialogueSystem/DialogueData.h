// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "DialogueData.generated.h"

// 화자의 위치를 나타내는 열거형 (왼쪽, 오른쪽)
UENUM(BlueprintType)
enum class ECharacterPosition : uint8
{
    Left UMETA(DisplayName = "Left"),
    Right UMETA(DisplayName = "Right")
};

USTRUCT(BlueprintType)
struct FDialogChoice
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    FText ChoiceText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    int32 NextDialogueIndex;

    FDialogChoice()
        : ChoiceText(FText::GetEmpty())
        , NextDialogueIndex(-1)
    {
    }
};

USTRUCT(BlueprintType)
struct FDialogAudioData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    USoundBase* VoiceSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    float PlaybackDelay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    bool bAutoPlaySound;

    FDialogAudioData()
        : VoiceSound(nullptr)
        , PlaybackDelay(0.0f)
        , bAutoPlaySound(true)
    {
    }
};

USTRUCT(BlueprintType)
struct FDialogueData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Basic")
    FText DialogueText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Basic")
    FString CharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Basic")
    FText DialogueTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Visual")
    UTexture2D* CharacterPortrait;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Visual")
    FLinearColor TextColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Visual")
    bool bShowPortrait;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Timing")
    float DisplayDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Timing")
    float TypewriterSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Timing")
    bool bUseTypewriterEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Audio")
    FDialogAudioData AudioData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Choices")
    TArray<FDialogChoice> Choices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Settings")
    bool bCanBeSkipped;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Settings")
    bool bRequireConfirmation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Settings")
    FName CustomEventTag;

    bool bUseCameraFocus;

    // 화자의 위치 정보 추가
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog|Settings")
    ECharacterPosition CharacterPosition;

    FDialogueData()
        : CharacterName("")
        , CharacterPortrait(nullptr)
        , TextColor(FLinearColor::White)
        , bShowPortrait(true)
        , DisplayDuration(3.0f)
        , TypewriterSpeed(20.0f)
        , bUseTypewriterEffect(true)
        , bCanBeSkipped(true)
        , bRequireConfirmation(false)
        , bUseCameraFocus(false)
        , CharacterPosition(ECharacterPosition::Left) // 기본값: Left
    {
    }

    bool IsValid() const
    {
        return !DialogueText.IsEmpty() && !CharacterName.IsEmpty();
    }

    bool HasChoices() const
    {
        return Choices.Num() > 0;
    }

    bool HasVoiceOver() const
    {
        return AudioData.VoiceSound != nullptr;
    }
};

USTRUCT(BlueprintType)
struct FDialogueSequence : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    FString SequenceName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    TArray<FDialogueData> DialogueEntries;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    bool bLoopSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    int32 StartIndex;

    FDialogueSequence()
        : SequenceName("")
        , bLoopSequence(false)
        , StartIndex(0)
    {
    }
    
    bool IsValid() const
    {
        return DialogueEntries.Num() > 0 && !SequenceName.IsEmpty();
    }
    
    int32 GetLength() const
    {
        return DialogueEntries.Num();
    }
    
    const FDialogueData* GetDialogueAt(int32 Index) const
    {
        if (DialogueEntries.IsValidIndex(Index))
        {
            return &DialogueEntries[Index];
        }
        return nullptr;
    }
};