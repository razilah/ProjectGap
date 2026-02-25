// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityDash.h"
#include "GapBaseCharacter.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"

UAbilityDash::UAbilityDash()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Movement.Dash")));

}

void UAbilityDash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	AGapBaseCharacter* Character = Cast<AGapBaseCharacter>(ActorInfo->AvatarActor.Get());
	if (Character)
	{
		FVector DashDirection = Character->GetActorForwardVector();
		float DashStrength =  DashDistance / DashDuration;

		//	Root motion ability task
		UAbilityTask_ApplyRootMotionConstantForce* DashTask = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(
			this,
			FName("Dash"),
			DashDirection,
			DashStrength,
			DashDuration,
			false,
			nullptr,
			ERootMotionFinishVelocityMode::SetVelocity, // Set velocity once dash ends
			FVector::ZeroVector, // To zero vector
			0.0f,
			false
		);

		DashTask->OnFinish.AddDynamic(this, &UAbilityDash::OnDashFinished);
		DashTask->ReadyForActivation();
	}

}

void UAbilityDash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UE_LOG(LogTemp, Log, TEXT("Dash Ability ended!"));
}

void UAbilityDash::OnDashFinished()
{
	CommitAbilityCooldown(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);

	// End the ability when the dash finishes
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);

	UE_LOG(LogTemp, Log, TEXT("Dash finished!"));
}
