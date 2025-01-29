
#include "DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

UDialogueWidget::UDialogueWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    TextAnimationSpeed = 30.0f;
    bIsAnimatingText = false;
    CurrentCharacterIndex = 0;
    bIsProcessingInput = false;
    ActivePortraitColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f); // White
    InactivePortraitColor = FLinearColor(0.5f, 0.5f, 0.5f, 1.0f); // Gray
}

void UDialogueWidget::NativeConstruct()
{
    Super::NativeConstruct();
    ClearDialogue();
    SetVisibility(ESlateVisibility::Visible);
    
    if (NextButton)
    {
        NextButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnNextButtonClicked);
    }
}

void UDialogueWidget::ShowDialogue(const FDialogueData& DialogueData)
{
    if (!DialogueData.bKeepPreviousPortraits)
    {
        PreviousDialogueData = CurrentDialogueData;
    }
    else if (DialogueData.CharacterPosition != CurrentDialogueData.CharacterPosition)
    {
        if (DialogueData.CharacterPosition == ECharacterPosition::Left)
        {
            FDialogueData TempData = CurrentDialogueData;
            PreviousDialogueData = TempData;
            PreviousDialogueData.CharacterPosition = ECharacterPosition::Right;
        }
        else if (DialogueData.CharacterPosition == ECharacterPosition::Right)
        {
            FDialogueData TempData = CurrentDialogueData;
            PreviousDialogueData = TempData;
            PreviousDialogueData.CharacterPosition = ECharacterPosition::Left;
        }
    }
    
    CurrentDialogueData = DialogueData;

    if (LeftPortrait)
    {
        LeftPortrait->SetVisibility(ESlateVisibility::Visible);
        LeftPortrait->SetRenderOpacity(1.0f);
    }
    
    if (RightPortrait)
    {
        RightPortrait->SetVisibility(ESlateVisibility::Visible);
        RightPortrait->SetRenderOpacity(1.0f);
    }
    
    UpdatePortraits(CurrentDialogueData, PreviousDialogueData);
    StartTextAnimation(DialogueData.DialogueText);
    
    if (NextButton)
    {
        NextButton->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UDialogueWidget::UpdatePortraits(const FDialogueData& CurrentData, const FDialogueData& PreviousData)
{
    if (TextBlock_CharacterName)
    {
        TextBlock_CharacterName->SetText(FText::FromString(CurrentData.CharacterName));
    }

    bool bShowCurrentLeft = (CurrentData.CharacterPosition == ECharacterPosition::Left && CurrentData.CharacterPortrait);
    bool bShowCurrentRight = (CurrentData.CharacterPosition == ECharacterPosition::Right && CurrentData.CharacterPortrait);
    bool bShowPreviousLeft = (PreviousData.CharacterPosition == ECharacterPosition::Left && PreviousData.CharacterPortrait);
    bool bShowPreviousRight = (PreviousData.CharacterPosition == ECharacterPosition::Right && PreviousData.CharacterPortrait);
    
    if (LeftPortrait)
    {
        if (bShowCurrentLeft)
        {
            FSlateBrush Brush;
            Brush.SetResourceObject(CurrentData.CharacterPortrait);
            LeftPortrait->SetBrush(Brush);
            LeftPortrait->SetVisibility(ESlateVisibility::Visible);
            LeftPortrait->SetColorAndOpacity(ActivePortraitColor);
        }
        else if (!bShowCurrentLeft && bShowPreviousLeft && CurrentData.bKeepPreviousPortraits)
        {
            FSlateBrush Brush;
            Brush.SetResourceObject(PreviousData.CharacterPortrait);
            LeftPortrait->SetBrush(Brush);
            LeftPortrait->SetVisibility(ESlateVisibility::Visible);
            LeftPortrait->SetColorAndOpacity(InactivePortraitColor);
        }
        else
        {
            LeftPortrait->SetVisibility(ESlateVisibility::Hidden);
        }
    }
    
    if (RightPortrait)
    {
        if (bShowCurrentRight)
        {
            FSlateBrush Brush;
            Brush.SetResourceObject(CurrentData.CharacterPortrait);
            RightPortrait->SetBrush(Brush);
            RightPortrait->SetVisibility(ESlateVisibility::Visible);
            RightPortrait->SetColorAndOpacity(ActivePortraitColor);
        }
        else if (!bShowCurrentRight && bShowPreviousRight && CurrentData.bKeepPreviousPortraits)
        {
            FSlateBrush Brush;
            Brush.SetResourceObject(PreviousData.CharacterPortrait);
            RightPortrait->SetBrush(Brush);
            RightPortrait->SetVisibility(ESlateVisibility::Visible);
            RightPortrait->SetColorAndOpacity(InactivePortraitColor);
        }
        else
        {
            RightPortrait->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void UDialogueWidget::UpdateDialogueText(const FText& DialogueText, const FString& CharacterName)
{
    if (TextBlock_CharacterName)
    {
        TextBlock_CharacterName->SetText(FText::FromString(CharacterName));
    }

    if (TextBlock_DialogueText)
    {
        TextBlock_DialogueText->SetText(DialogueText);
    }
}

void UDialogueWidget::StartTextAnimation(const FText& FullText)
{
    if (TextAnimationSpeed <= 0.0f)
    {
        UpdateDialogueText(FullText, CurrentDialogueData.CharacterName);
        OnDialogueAnimationComplete();
        return;
    }
    
    bIsAnimatingText = true;
    CurrentAnimatedText = FullText.ToString();
    CurrentCharacterIndex = 0;
    
    float TimePerCharacter = 1.0f / TextAnimationSpeed;
    GetWorld()->GetTimerManager().SetTimer(
        TextAnimationTimer,
        this,
        &UDialogueWidget::AnimateNextCharacter,
        TimePerCharacter,
        true
    );
}

void UDialogueWidget::AnimateNextCharacter()
{
    if (!CurrentAnimatedText.IsEmpty() && CurrentCharacterIndex < CurrentAnimatedText.Len())
    {
        CurrentCharacterIndex++;
        FString CurrentVisibleText = CurrentAnimatedText.Left(CurrentCharacterIndex);
        UpdateDialogueText(FText::FromString(CurrentVisibleText), CurrentDialogueData.CharacterName);
        
        if (TypewriterSound)
        {
            UGameplayStatics::PlaySound2D(this, TypewriterSound);
        }
        
        if (CurrentCharacterIndex >= CurrentAnimatedText.Len())
        {
            GetWorld()->GetTimerManager().ClearTimer(TextAnimationTimer);
            bIsAnimatingText = false;
            OnDialogueAnimationComplete();
        }
    }
}

void UDialogueWidget::ClearDialogue()
{
    if (TextBlock_DialogueText)
    {
        TextBlock_DialogueText->SetText(FText::GetEmpty());
    }
    if (TextBlock_CharacterName)
    {
        TextBlock_CharacterName->SetText(FText::GetEmpty());
    }

    if (LeftPortrait)
    {
        LeftPortrait->SetVisibility(ESlateVisibility::Hidden);
    }
    if (RightPortrait)
    {
        RightPortrait->SetVisibility(ESlateVisibility::Hidden);
    }
    
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(TextAnimationTimer);
    }
    
    bIsAnimatingText = false;
    CurrentCharacterIndex = 0;
    CurrentAnimatedText.Empty();
    
    CurrentDialogueData = FDialogueData();
    PreviousDialogueData = FDialogueData();
    
    if (NextButton)
    {
        NextButton->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UDialogueWidget::SkipTextAnimation()
{
    if (bIsAnimatingText)
    {
        GetWorld()->GetTimerManager().ClearTimer(TextAnimationTimer);
        UpdateDialogueText(FText::FromString(CurrentAnimatedText), CurrentDialogueData.CharacterName);
        
        bIsAnimatingText = false;
        OnDialogueAnimationComplete();
    }
}

void UDialogueWidget::OnDialogueAnimationComplete()
{
    if (NextButton)
    {
        NextButton->SetVisibility(ESlateVisibility::Visible);
    }
}

void UDialogueWidget::OnNextButtonClicked()
{
    if (bIsProcessingInput) return;
    
    bIsProcessingInput = true;
    OnNextButtonClickedDelegate.Broadcast();
    
    FTimerHandle UnlockTimer;
    GetWorld()->GetTimerManager().SetTimer(
        UnlockTimer,
        [this]() { bIsProcessingInput = false; },
        0.1f,
        false
    );
}