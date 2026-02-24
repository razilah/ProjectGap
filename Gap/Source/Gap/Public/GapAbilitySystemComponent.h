// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GapAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAP_API UGapAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "GAS | Input")
    void AbilityInputTagPressed(const FGameplayTag InputTag);


};
