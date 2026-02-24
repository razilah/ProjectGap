// Fill out your copyright notice in the Description page of Project Settings.


#include "GapAbilitySystemComponent.h"

void UGapAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag InputTag)
{
	if (!InputTag.IsValid()) return;

	TryActivateAbilitiesByTag(InputTag.GetSingleTagContainer());

	UE_LOG(LogTemp, Log, TEXT("AbilityInputTagPressed: %s"), *InputTag.ToString());
}
