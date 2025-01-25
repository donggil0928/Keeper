#pragma once

#include "CoreMinimal.h"
#include "DialogueData.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "UObject/ConstructorHelpers.h"
#include "DialogueWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextButtonClickedDelegate);

UCLASS()
class KEEPER_API UDialogueWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnNextButtonClickedDelegate OnNextButtonClickedDelegate;

    UPROPERTY(meta = (BindWidget))
    UButton* NextButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* PortraitContainer;

    UPROPERTY(meta = (BindWidget))
    UImage* LeftPortrait;

    UPROPERTY(meta = (BindWidget))
    UImage* RightPortrait;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TextBlock_CharacterName;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TextBlock_DialogueText;

    UDialogueWidget(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    virtual void ShowDialogue(const FDialogueData& DialogueData);

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void OnNextButtonClicked();

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    virtual void ClearDialogue();

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void SkipTextAnimation();

    UFUNCTION(BlueprintPure, Category = "Dialogue")
    bool ShouldShowLeftPortrait() const
    {
        bool bShowCurrentLeft = (CurrentDialogueData.CharacterPosition == ECharacterPosition::Left && 
                               CurrentDialogueData.CharacterPortrait != nullptr);
        bool bShowPreviousLeft = (PreviousDialogueData.CharacterPosition == ECharacterPosition::Left && 
                                PreviousDialogueData.CharacterPortrait != nullptr);
        
        // 현재 화자가 왼쪽이거나, 이전 화자가 왼쪽이고 현재 화자가 오른쪽일 때
        return bShowCurrentLeft || (bShowPreviousLeft && 
                                  CurrentDialogueData.CharacterPosition == ECharacterPosition::Right);
    }

    UFUNCTION(BlueprintPure, Category = "Dialogue")
    bool ShouldShowRightPortrait() const
    {
        bool bShowCurrentRight = (CurrentDialogueData.CharacterPosition == ECharacterPosition::Right && 
                                CurrentDialogueData.CharacterPortrait != nullptr);
        bool bShowPreviousRight = (PreviousDialogueData.CharacterPosition == ECharacterPosition::Right && 
                                 PreviousDialogueData.CharacterPortrait != nullptr);
        
        // 현재 화자가 오른쪽이거나, 이전 화자가 오른쪽이고 현재 화자가 왼쪽일 때
        return bShowCurrentRight || (bShowPreviousRight && 
                                   CurrentDialogueData.CharacterPosition == ECharacterPosition::Left);
    }

    UFUNCTION(BlueprintPure, Category = "Dialogue")
    UTexture2D* GetLeftPortraitTexture() const
    {
        if (CurrentDialogueData.CharacterPosition == ECharacterPosition::Left)
        {
            return CurrentDialogueData.CharacterPortrait;
        }
        else if (PreviousDialogueData.CharacterPosition == ECharacterPosition::Left && 
                 CurrentDialogueData.CharacterPosition == ECharacterPosition::Right)
        {
            return PreviousDialogueData.CharacterPortrait;
        }
        return nullptr;
    }

    UFUNCTION(BlueprintPure, Category = "Dialogue")
    UTexture2D* GetRightPortraitTexture() const
    {
        if (CurrentDialogueData.CharacterPosition == ECharacterPosition::Right)
        {
            return CurrentDialogueData.CharacterPortrait;
        }
        else if (PreviousDialogueData.CharacterPosition == ECharacterPosition::Right && 
                 CurrentDialogueData.CharacterPosition == ECharacterPosition::Left)
        {
            return PreviousDialogueData.CharacterPortrait;
        }
        return nullptr;
    }

    UFUNCTION(BlueprintPure, Category = "Dialogue")
    FLinearColor GetLeftPortraitColor() const
    {
        if (CurrentDialogueData.CharacterPosition == ECharacterPosition::Left)
        {
            return ActivePortraitColor;
        }
        return InactivePortraitColor;
    }

    UFUNCTION(BlueprintPure, Category = "Dialogue")
    FLinearColor GetRightPortraitColor() const
    {
        if (CurrentDialogueData.CharacterPosition == ECharacterPosition::Right)
        {
            return ActivePortraitColor;
        }
        return InactivePortraitColor;
    }

protected:
    virtual void NativeConstruct() override;

    virtual void UpdateDialogueText(const FText& DialogueText, const FString& CharacterName);
    virtual void UpdatePortraits(const FDialogueData& CurrentData, const FDialogueData& PreviousData);

    virtual void OnDialogueAnimationComplete();

    void StartTextAnimation(const FText& FullText);
    void AnimateNextCharacter();

    UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
    FDialogueData CurrentDialogueData;

    UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
    FDialogueData PreviousDialogueData;

    UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
    bool bIsAnimatingText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (ClampMin = "0.0"))
    float TextAnimationSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    USoundBase* TypewriterSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FLinearColor ActivePortraitColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FLinearColor InactivePortraitColor;

    bool bIsProcessingInput;

private:
    FTimerHandle TextAnimationTimer;
    FString CurrentAnimatedText;
    int32 CurrentCharacterIndex;
};

//