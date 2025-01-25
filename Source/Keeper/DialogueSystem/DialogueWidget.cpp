
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
    PreviousDialogueData = CurrentDialogueData;
    
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
    
    UE_LOG(LogTemp, Warning, TEXT("[ShowDialogue] Setting Previous Portrait: %p, Position: %s"), 
        PreviousDialogueData.CharacterPortrait,
        PreviousDialogueData.CharacterPosition == ECharacterPosition::Left ? TEXT("Left") : TEXT("Right"));
    
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
        UE_LOG(LogTemp, Warning, TEXT("LeftPortrait - Visibility: %d, Opacity: %f"), 
            (int32)LeftPortrait->GetVisibility(), 
            LeftPortrait->GetRenderOpacity());
    }
    
    if (RightPortrait)
    {
        UE_LOG(LogTemp, Warning, TEXT("RightPortrait - Visibility: %d, Opacity: %f"), 
            (int32)RightPortrait->GetVisibility(), 
            RightPortrait->GetRenderOpacity());
    }
    
    // 왼쪽 초상화 처리
    if (LeftPortrait)
    {
        if (bShowCurrentLeft)
        {
            // 현재 화자가 왼쪽
            FSlateBrush Brush;
            Brush.SetResourceObject(CurrentData.CharacterPortrait);
            LeftPortrait->SetBrush(Brush);
            LeftPortrait->SetVisibility(ESlateVisibility::Visible);
            LeftPortrait->SetColorAndOpacity(ActivePortraitColor);
        }
        else if (bShowPreviousLeft && !bShowCurrentLeft && !bShowPreviousRight)
        {
            // 이전 화자가 왼쪽이고 현재 화자가 왼쪽이 아닐 때
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

    // 오른쪽 초상화 처리
    if (RightPortrait)
    {
        if (bShowCurrentRight)
        {
            // 현재 화자가 오른쪽
            FSlateBrush Brush;
            Brush.SetResourceObject(CurrentData.CharacterPortrait);
            RightPortrait->SetBrush(Brush);
            RightPortrait->SetVisibility(ESlateVisibility::Visible);
            RightPortrait->SetColorAndOpacity(ActivePortraitColor);
        }
        else if (bShowPreviousRight && !bShowCurrentRight && !bShowPreviousLeft)
        {
            // 이전 화자가 오른쪽이고 현재 화자가 오른쪽이 아닐 때
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
    
    // UE_LOG(LogTemp, Warning, TEXT("[UpdatePortraits] Current - Position: %s, Portrait: %p"),
    //     CurrentData.CharacterPosition == ECharacterPosition::Left ? TEXT("Left") : TEXT("Right"),
    //     CurrentData.CharacterPortrait);
    // UE_LOG(LogTemp, Warning, TEXT("[UpdatePortraits] Previous - Position: %s, Portrait: %p"),
    //     PreviousData.CharacterPosition == ECharacterPosition::Left ? TEXT("Left") : TEXT("Right"),
    //     PreviousData.CharacterPortrait);
    
    UE_LOG(LogTemp, Warning, TEXT("After Update - Left Visibility: %d, Right Visibility: %d"),
        LeftPortrait ? (int32)LeftPortrait->GetVisibility() : -1,
        RightPortrait ? (int32)RightPortrait->GetVisibility() : -1);
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