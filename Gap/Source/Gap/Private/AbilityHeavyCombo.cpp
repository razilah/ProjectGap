// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityHeavyCombo.h"
#include "GapBaseCharacter.h"
#include "DA_HeavyCombo.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GapBaseCharacter.h"

UAbilityHeavyCombo::UAbilityHeavyCombo()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Combat.Attack")));
}

void UAbilityHeavyCombo::OnMontageCompleted()
{
    if (bNextComboQueued)
    {
        bNextComboQueued = false;
        CurrentIndex++;
        PlayComboStep(CurrentIndex);
    }
    else
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}

void UAbilityHeavyCombo::OnNextComboInput(FGameplayEventData EventData)
{
	bNextComboQueued = true;
}

void UAbilityHeavyCombo::OnHitReceived(FGameplayEventData EventData)
{
    TSubclassOf<UGameplayEffect> HitEffect = HeavyComboList->ComboSteps[CurrentIndex].HitEffect;

    if (HitEffect && EventData.Target)
    {
        FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(HitEffect);

        if (SpecHandle.IsValid())
        {
            const AGapBaseCharacter* OwnCharacter = Cast<AGapBaseCharacter>(EventData.Instigator);
            const AGapBaseCharacter* TargetCharacter = Cast<AGapBaseCharacter>(EventData.Target);
            if (UAbilitySystemComponent* TargetASC = TargetCharacter->GetAbilitySystemComponent())
            {
                if (!TargetASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Character.State.Death")))
                {
                    // Apply the spec from our ASC to their ASC
                    GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
                }
                if (TargetASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Character.Combat.HitReacting")))
                {
                    //  Use this instead to apply asc on target actor
                    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(const_cast<AActor*>(EventData.Target.Get()),
                        FGameplayTag::RequestGameplayTag(FName("Event.Combat.Damage")), EventData);

                    FGameplayCueParameters GCParams;
                    GCParams.RawMagnitude = 1.0f +(CurrentIndex * 0.5f);
					GetAbilitySystemComponentFromActorInfo()->ExecuteGameplayCue(FGameplayTag::RequestGameplayTag("GameplayCue.Combat.HitShake"), GCParams);

                }
                
            }
        }
    }  
}

void UAbilityHeavyCombo::PlayComboStep(int32 Index)
{
    if (!HeavyComboList || !HeavyComboList->ComboSteps.IsValidIndex(Index))
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
        return;
    }

    // Play the Montage Task
    UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
        this, NAME_None, HeavyComboList->ComboSteps[Index].Montage, MontagePlayrate);

    MontageTask->OnCompleted.AddDynamic(this, &UAbilityHeavyCombo::OnMontageCompleted);
    MontageTask->ReadyForActivation();

    // Listens for a GameplayTag sent from Attack input
    UAbilityTask_WaitGameplayEvent* WaitInputTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
        this, FGameplayTag::RequestGameplayTag("Event.Combat.Attack"));

    WaitInputTask->EventReceived.AddDynamic(this, &UAbilityHeavyCombo::OnNextComboInput);
    WaitInputTask->ReadyForActivation();

	// Listens for a GameplayTag sent when the attack hits an enemy
    UAbilityTask_WaitGameplayEvent* WaitHitTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, FGameplayTag::RequestGameplayTag("Event.Combat.Hit"), nullptr, true);

    WaitHitTask->EventReceived.AddDynamic(this, &UAbilityHeavyCombo::OnHitReceived);
	WaitHitTask->ReadyForActivation();
}

void UAbilityHeavyCombo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CurrentIndex = 0;
	bNextComboQueued = false;
	PlayComboStep(CurrentIndex);
}
