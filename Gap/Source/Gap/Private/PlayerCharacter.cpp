// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GapAbilitySystemComponent.h"
#include "GapAttributeSet.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//InitAbilitySystemComponent();
	InitAbilities();
	InitEffects();
	InitHUD();
}

void APlayerCharacter::InitHUD() const
{
}
