// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"


#include "TargetHealBeacon.generated.h"

/**
 * 
 */

class UGameplayEffect;

UCLASS()
class GAP_API ATargetHealBeacon : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
    ATargetHealBeacon();

    // The Effect to apply to actors inside the radius
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stim")
    TSubclassOf<UGameplayEffect> EffectClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stim")
    float Radius = 400.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stim")
    float TickInterval = 0.5f;

protected:
    virtual void BeginPlay() override;

    // Timer function to pulse the heal
    void PulseHeal();

    FTimerHandle PulseTimerHandle;

    UPROPERTY(VisibleAnywhere)
    class USphereComponent* OverlapSphere;
};
