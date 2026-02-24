// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_AbilityList.generated.h"

/**
 * 
 */
UCLASS()
class GAP_API UDA_AbilityList : public UDataAsset
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS | Granted abilities")
	TArray<TSubclassOf<class UGameplayAbility>> GrantedAbilities;
	
};
