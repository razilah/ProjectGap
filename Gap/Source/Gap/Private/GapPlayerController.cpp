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
}

void AGapPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    ControllerSetup();
	SetupInputComponent();   
}

void AGapPlayerController::SetupInputComponent()
{
    if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        Input->BindAction(InputData.DashAction, ETriggerEvent::Triggered, this, &AGapPlayerController::OnDashPressed);
    }
}

void AGapPlayerController::OnDashPressed()
{
    PlayerCharacter = CastChecked<AGapBaseCharacter>(GetOwner());

    if (PlayerCharacter.IsValid())
    {
		UAbilitySystemComponent* ASC = PlayerCharacter->GetAbilitySystemComponent();

        if (ASC)
        {
            ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(FGameplayTag::RequestGameplayTag(FName("Ability.Movement.Dash"))));
		}
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
