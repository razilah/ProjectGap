// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"


#include "AbilityHeavyCombo.generated.h"

/**
 * 
 */
class UDA_HeavyCombo;

UCLASS()
class GAP_API UAbilityHeavyCombo : public UGameplayAbility
{
	GENERATED_BODY()

public:
	
	UAbilityHeavyCombo();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Ability")
	UDA_HeavyCombo* HeavyComboList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Ability")
	float MontagePlayrate = 1.0f;

	int32 CurrentIndex = 0;

	bool bNextComboQueued = false;

	UFUNCTION()
	void OnMontageCompleted();

	UFUNCTION()
	void OnNextComboInput(FGameplayEventData EventData);

	UFUNCTION()
	void OnHitReceived(FGameplayEventData EventData);

	void PlayComboStep(int32 Index);


	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
