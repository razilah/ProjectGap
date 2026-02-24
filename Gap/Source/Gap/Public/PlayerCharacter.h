// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GapBaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAP_API APlayerCharacter : public AGapBaseCharacter
{
	GENERATED_BODY()
	
	APlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;

private:

	void InitHUD() const;
};
