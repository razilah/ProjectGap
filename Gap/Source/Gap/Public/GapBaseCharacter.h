// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "DA_AbilityList.h"
#include "GameplayTagContainer.h"
#include "GapAttributeSet.h"

#include "GapBaseCharacter.generated.h"

class UGapPlayerController;
class UGapAbilitySystemComponent;
class UGapAttributeSet;
class UGameplayAbility;
class UGameplayEffect;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, NewHealth, FGameplayTagContainer, EffectTags);

UCLASS()
class GAP_API AGapBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGapBaseCharacter();

	UFUNCTION(BlueprintPure, Category = "GAS")
	UDA_AbilityList* GetGrantedAbilitiesDataAsset() { return GrantedAbilitiesData; }

	UPROPERTY(BlueprintAssignable, Category = "GAS")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "GAS | Ability")
	TObjectPtr<UGapAbilitySystemComponent> AbilitySystemComponent;
	TObjectPtr<const UGapAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS | Ability")
	TObjectPtr<UDA_AbilityList> GrantedAbilitiesData;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	virtual void BeginPlay() override;

	void InitAbilities();

private:

	
};
