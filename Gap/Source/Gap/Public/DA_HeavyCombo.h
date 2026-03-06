// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "DA_HeavyCombo.generated.h"

/**
 * 
 */
class AnimMontage;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FAttackComboStep
{
    GENERATED_BODY()

    // The animation to play for this hit
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
    UAnimMontage* Montage = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
    TSubclassOf<UGameplayEffect> HitEffect;

    // Optional: Add metadata here (e.g., stamina cost, damage multiplier)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
    float DamageMultiplier = 1.0f;
};

UCLASS()
class GAP_API UDA_HeavyCombo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
	TArray<FAttackComboStep> ComboSteps;
};
