// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "GapAbilitySystemComponent.h"
#include "GapAttributeSet.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitAbilities();
	InitEffects();
}