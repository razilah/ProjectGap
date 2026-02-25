// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityDash.generated.h"

/**
 * 
 */
UCLASS()
class GAP_API UAbilityDash : public UGameplayAbility
{
	GENERATED_BODY()

	public:
	UAbilityDash();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Ability")
	float DashDistance = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Ability")
	float DashDuration = 1.0f;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION()
	void OnDashFinished();
};
