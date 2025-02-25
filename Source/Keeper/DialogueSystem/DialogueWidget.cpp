
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
    bNeedsPortraitUpdate = false;
    bIsPortraitInitialized = false;
    bIsFirstDialogue = true;
    ActivePortraitColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
    InactivePortraitColor = FLinearColor(0.5f, 0.5f, 0.5f, 1.0f);
    InitialDesiredSize = FVector2D(1.0f, 1.0f);
}

void UDialogueWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    if (LeftPortrait)
    {
        LeftPortrait->SetVisibility(ESlateVisibility::Hidden);
        LeftPortrait->SetDesiredSizeOverride(InitialDesiredSize);
    }
    
    if (RightPortrait)
    {
        RightPortrait->SetVisibility(ESlateVisibility::Hidden);
        RightPortrait->SetDesiredSizeOverride(InitialDesiredSize);
    }
    
    ClearDialogue();
    SetVisibility(ESlateVisibility::Visible);
    
    if (NextButton)
    {
        NextButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnNextButtonClicked);
    }
}

void UDialogueWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    
    if (bNeedsPortraitUpdate && PortraitContainer)
    {
        FVector2D ContainerSize = PortraitContainer->GetCachedGeometry().GetLocalSize();
        if (ContainerSize.Y > 0)
        {
            UpdatePortraits(CurrentDialogueData, PreviousDialogueData);
            bNeedsPortraitUpdate = false;
        }
    }
}

void UDialogueWidget::ShowDialogue(const FDialogueData& DialogueData)
{
    if (bIsFirstDialogue)
    {
        if (LeftPortrait)
        {
            LeftPortrait->SetVisibility(ESlateVisibility::Hidden);
            LeftPortrait->SetDesiredSizeOverride(InitialDesiredSize);
        }
        if (RightPortrait)
        {
            RightPortrait->SetVisibility(ESlateVisibility::Hidden);
            RightPortrait->SetDesiredSizeOverride(InitialDesiredSize);
        }
    }
    
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
    bNeedsPortraitUpdate = true;

    if (bIsFirstDialogue)
    {
        GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
        {
            UpdatePortraits(CurrentDialogueData, PreviousDialogueData);
            bIsFirstDialogue = false;
        });
    }
    
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
    
    if (PortraitContainer)
    {
        FVector2D ContainerSize = PortraitContainer->GetCachedGeometry().GetLocalSize();
        if (ContainerSize.Y > 0)
        {
            if (bShowCurrentLeft || (bShowPreviousLeft && CurrentData.bKeepPreviousPortraits))
            {
                const UTexture2D* LeftTexture = bShowCurrentLeft ? CurrentData.CharacterPortrait : PreviousData.CharacterPortrait;
                if (LeftPortrait && LeftTexture)
                {
                    UpdatePortraitSize(LeftPortrait, LeftTexture);
                }
            }
            
            if (bShowCurrentRight || (bShowPreviousRight && CurrentData.bKeepPreviousPortraits))
            {
                const UTexture2D* RightTexture = bShowCurrentRight ? CurrentData.CharacterPortrait : PreviousData.CharacterPortrait;
                if (RightPortrait && RightTexture)
                {
                    UpdatePortraitSize(RightPortrait, RightTexture);
                }
            }
            
            bIsPortraitInitialized = true;
        }
        else
        {
            bNeedsPortraitUpdate = true;
            return;
        }
    }

    if (bIsPortraitInitialized)
    {
        if (LeftPortrait)
        {
            if (bShowCurrentLeft)
            {
                FSlateBrush Brush;
                Brush.SetResourceObject(CurrentData.CharacterPortrait);
                LeftPortrait->SetBrush(Brush);
                LeftPortrait->SetColorAndOpacity(ActivePortraitColor);
                LeftPortrait->SetVisibility(ESlateVisibility::Visible);
            }
            else if (!bShowCurrentLeft && bShowPreviousLeft && CurrentData.bKeepPreviousPortraits)
            {
                FSlateBrush Brush;
                Brush.SetResourceObject(PreviousData.CharacterPortrait);
                LeftPortrait->SetBrush(Brush);
                LeftPortrait->SetColorAndOpacity(InactivePortraitColor);
                LeftPortrait->SetVisibility(ESlateVisibility::Visible);
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
                RightPortrait->SetColorAndOpacity(ActivePortraitColor);
                RightPortrait->SetVisibility(ESlateVisibility::Visible);
            }
            else if (!bShowCurrentRight && bShowPreviousRight && CurrentData.bKeepPreviousPortraits)
            {
                FSlateBrush Brush;
                Brush.SetResourceObject(PreviousData.CharacterPortrait);
                RightPortrait->SetBrush(Brush);
                RightPortrait->SetColorAndOpacity(InactivePortraitColor);
                RightPortrait->SetVisibility(ESlateVisibility::Visible);
            }
            else
            {
                RightPortrait->SetVisibility(ESlateVisibility::Hidden);
            }
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

void UDialogueWidget::UpdatePortraitSize(UImage* Portrait, const UTexture2D* Texture)
{
    if (!Portrait || !Texture || !PortraitContainer) return;

    FVector2D ContainerSize = PortraitContainer->GetCachedGeometry().GetLocalSize();
    if (ContainerSize.Y <= 0) 
    {
        bNeedsPortraitUpdate = true;
        return;
    }

    // float ContainerHeight = ContainerSize.Y;
    // float MaxPortraitHeight = ContainerHeight * PortraitMaxHeightRatio;
    
    float TextureWidth = Texture->GetSizeX();
    float TextureHeight = Texture->GetSizeY();
    
    float AspectRatio = TextureWidth / TextureHeight;
    
    // float NewHeight = MaxPortraitHeight;
    // float NewWidth = NewHeight * AspectRatio;
    
    //Portrait->SetDesiredSizeOverride(FVector2D(NewWidth, NewHeight));
    Portrait->SetDesiredSizeOverride(FVector2D(TextureWidth, TextureHeight)); 
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
        LeftPortrait->SetDesiredSizeOverride(InitialDesiredSize);
    }
    if (RightPortrait)
    {
        RightPortrait->SetVisibility(ESlateVisibility::Hidden);
        RightPortrait->SetDesiredSizeOverride(InitialDesiredSize);
    }
    
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(TextAnimationTimer);
    }
    
    bIsAnimatingText = false;
    bIsFirstDialogue = true;
    bIsPortraitInitialized = false;
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