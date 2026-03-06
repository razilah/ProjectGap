#include "AbilityHealBeacon.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Abilities/GameplayAbilityTargetActor_GroundTrace.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "TargetHealBeacon.h"

UAbilityHealBeacon::UAbilityHealBeacon()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UAbilityHealBeacon::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    bIsTargeting = true;
    CallLoopAnimation();

    AGameplayAbilityTargetActor_GroundTrace* TargetActor =
        GetWorld()->SpawnActor<AGameplayAbilityTargetActor_GroundTrace>(GroundTraceClass);

    TargetActor->MaxRange = TargetingRange;
    TargetActor->TraceProfile = FName("Trigger");

    UAbilityTask_WaitTargetData* TargetTask =
        UAbilityTask_WaitTargetData::WaitTargetDataUsingActor(
            this,
            NAME_None,
            EGameplayTargetingConfirmation::UserConfirmed,
            TargetActor);

    TargetTask->ValidData.AddDynamic(this, &UAbilityHealBeacon::OnTargetConfirmed);
    TargetTask->Cancelled.AddDynamic(this, &UAbilityHealBeacon::OnTargetCancelled);

    TargetTask->ReadyForActivation();

}

void UAbilityHealBeacon::OnTargetConfirmed(const FGameplayAbilityTargetDataHandle& Data)
{
	UE_LOG(LogTemp, Log, TEXT("Target Confirmed!"));

	bIsTargeting = false;

    CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);

    UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
        this, NAME_None, CommitMontage, 1.0f);

	MontageTask->OnCompleted.AddDynamic(this, &UAbilityHealBeacon::OnCommitMontageEnded);
	MontageTask->OnInterrupted.AddDynamic(this, &UAbilityHealBeacon::OnCastMontageEnded);

	MontageTask->ReadyForActivation();

	FVector TargetLocation = Data.Get(0)->GetHitResult()->Location;

    FTransform SpawnTransform(FRotator::ZeroRotator, TargetLocation);

    ATargetHealBeacon* SpawnedBeacon = GetWorld()->SpawnActorDeferred<ATargetHealBeacon>(
        HealBeaconClass,
        SpawnTransform
    );

    if (SpawnedBeacon)
    {
        SpawnedBeacon->EffectClass = HealEffectClass;
        // Set a lifespan so it disappears after 10 seconds
        SpawnedBeacon->SetLifeSpan(10.0f);

        SpawnedBeacon->FinishSpawning(SpawnTransform);
    }
    
}

void UAbilityHealBeacon::OnTargetCancelled(const FGameplayAbilityTargetDataHandle& Data)
{
	UE_LOG(LogTemp, Log, TEXT("Target Cancelled!"));
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UAbilityHealBeacon::CallLoopAnimation()
{
    UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
        this, NAME_None, CastMontage, 1.0f);

	MontageTask->OnBlendOut.AddDynamic(this, &UAbilityHealBeacon::OnLoopCastMontage);
	MontageTask->OnInterrupted.AddDynamic(this, &UAbilityHealBeacon::OnCastMontageEnded);

	MontageTask->ReadyForActivation();
}

void UAbilityHealBeacon::OnLoopCastMontage()
{
    if (bIsTargeting)
    {
        CallLoopAnimation();
	}
}

void UAbilityHealBeacon::OnCastMontageEnded()
{
    if (bIsTargeting)
    {
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}

void UAbilityHealBeacon::OnCommitMontageEnded()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
