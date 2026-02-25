// Fill out your copyright notice in the Description page of Project Settings.


#include "GapBaseCharacter.h"
#include "GapAbilitySystemComponent.h"

// Sets default values
AGapBaseCharacter::AGapBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* AGapBaseCharacter::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(AbilitySystemComponent.Get());
}

void AGapBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGapBaseCharacter::InitAbilities()
{
	if (AbilitySystemComponent && HasAuthority())
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		if (GrantedAbilitiesData)
		{
			for (TSubclassOf<UGameplayAbility>& Ability : GrantedAbilitiesData->GrantedAbilities)
			{
				const FGameplayAbilitySpec AbilitySpec(Ability, 1);
				AbilitySystemComponent->GiveAbility(AbilitySpec);
			}
		}
	}
}




