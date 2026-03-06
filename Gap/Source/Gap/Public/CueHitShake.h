// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "CueHitShake.generated.h"

/**
 * 
 */
UCLASS()
class GAP_API UCueHitShake : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

public:

	UCueHitShake();

	// The camera shake class to use
	UPROPERTY(EditDefaultsOnly, Category = "GAS | Cue")
	TSubclassOf<UCameraShakeBase> HitShakeClass;


protected:

	bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;
	
};
