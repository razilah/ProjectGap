// Fill out your copyright notice in the Description page of Project Settings.


#include "GapAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GapBaseCharacter.h"

UGapAttributeSet::UGapAttributeSet()
{
	InitHealth(100.f);
}

void UGapAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
    }
}

void UGapAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    const FGameplayEffectSpec& Spec = Data.EffectSpec;

    FGameplayTagContainer EffectTags;
    Spec.GetAllAssetTags(EffectTags);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
        if (const auto Character = Cast<AGapBaseCharacter>(Data.Target.GetAvatarActor()))
        {
            Character->OnHealthChanged.Broadcast(GetHealth(), EffectTags);
        }
    }
}
