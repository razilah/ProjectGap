// Fill out your copyright notice in the Description page of Project Settings.


#include "CueHitShake.h"
#include "Animation\SkeletalMeshActor.h"
#include "GapBaseCharacter.h"
#include "GapPlayerController.h"

UCueHitShake::UCueHitShake()
{
    GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Combat.HitShake"));
}

bool UCueHitShake::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Gameplay Cue Executed!"));

    if (AGapBaseCharacter* Attacker = Cast<AGapBaseCharacter>(Parameters.Instigator))
    {
        // 2. Access the Camera Manager
        if (AGapPlayerController* PC = Cast<AGapPlayerController>(Attacker->GetInstigatorController()))
        {
            // 3. Shake the camera based on the "Magnitude" (Combo Index) we passed
            float ShakeIntensity = 1.0f + (Parameters.RawMagnitude * 0.5f);
            PC->PlayerCameraManager->StartCameraShake(HitShakeClass, ShakeIntensity);

			UE_LOG(LogTemp, Log, TEXT("Hit Shake executed with magnitude: %f"), Parameters.RawMagnitude);
        }
    }
    return true;
}
