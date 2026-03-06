#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "AbilityHealBeacon.generated.h"



/**
 * 
 */

class ATargetHealBeacon;
class AGameplayAbilityTargetActor_GroundTrace;
class UAnimMontage;

UCLASS()

class GAP_API UAbilityHealBeacon : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UAbilityHealBeacon();

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void OnTargetConfirmed(const FGameplayAbilityTargetDataHandle& Data);

	UFUNCTION()
	void OnTargetCancelled(const FGameplayAbilityTargetDataHandle& Data);

	UPROPERTY(EditDefaultsOnly, Category = "GAS | Ability")
	TSubclassOf<ATargetHealBeacon> HealBeaconClass;

	UPROPERTY(EditDefaultsOnly, Category = "GAS | Ability")
	TSubclassOf<UGameplayEffect> HealEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Ability")
	TSubclassOf<AGameplayAbilityTargetActor_GroundTrace> GroundTraceClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Ability")
	float TargetingRange = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Ability")
	UAnimMontage* CastMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Ability")
	UAnimMontage* CommitMontage;

	bool bIsTargeting = false;

	void CallLoopAnimation();

	UFUNCTION()
	void OnLoopCastMontage();

	UFUNCTION()
	void OnCastMontageEnded();

	UFUNCTION()
	void OnCommitMontageEnded();
};