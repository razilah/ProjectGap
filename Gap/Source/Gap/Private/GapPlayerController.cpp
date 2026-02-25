// Fill out your copyright notice in the Description page of Project Settings.


#include "GapPlayerController.h"
#include "GapBaseCharacter.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AGapPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControllerSetup();
}

void AGapPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        PlayerCharacter = CastChecked<AGapBaseCharacter>(GetCharacter());

        /*Input->BindAction(InputData.MoveAction, ETriggerEvent::Triggered, PlayerCharacter.Get(), &AGapBaseCharacter::MoveAction);
        Input->BindAction(InputData.LookAction, ETriggerEvent::Triggered, PlayerCharacter.Get(), &AGapBaseCharacter::LookAction);*/
    }
}

void AGapPlayerController::ControllerSetup()
{
    if (APlayerController* PC = Cast<APlayerController>(this))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->ClearAllMappings();
            Subsystem->AddMappingContext(InputData.InputMapping, 0);

            UE_LOG(LogTemp, Display, TEXT("Enhanced input mapping setup successfull"));
        }
    }
}
