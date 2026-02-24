// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GapBaseCharacter.h"

#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAP_API AEnemyCharacter : public AGapBaseCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;
};
