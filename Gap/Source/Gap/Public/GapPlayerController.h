// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "GapPlayerController.generated.h"

/**
 * 
 */

class AGapBaseCharacter;
class UInputMappingContext;
class UInputAction;

USTRUCT(BlueprintType)
struct FEnhancedInputData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mapping context")
    UInputMappingContext* InputMapping = nullptr;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    UInputAction* MoveAction = nullptr;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    UInputAction* LookAction = nullptr;
};

UCLASS()
class GAP_API AGapPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    

protected:

    virtual void BeginPlay() override;

    virtual void OnPossess(APawn* aPawn) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_Enhanced input settings")
    FEnhancedInputData InputData;

private:
    void ControllerSetup();

    TWeakObjectPtr<AGapBaseCharacter> PlayerCharacter;
};
