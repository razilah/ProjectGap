// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetHealBeacon.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "PlayerCharacter.h"

ATargetHealBeacon::ATargetHealBeacon()
{
    PrimaryActorTick.bCanEverTick = false;

    OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
    OverlapSphere->SetSphereRadius(Radius);
    OverlapSphere->SetCollisionProfileName(TEXT("Trigger"));
    RootComponent = OverlapSphere;
}

void ATargetHealBeacon::BeginPlay()
{
    Super::BeginPlay();

    // Start the pulsing logic immediately upon spawning
    GetWorld()->GetTimerManager().SetTimer(PulseTimerHandle, this, &ATargetHealBeacon::PulseHeal, TickInterval, true);
}

void ATargetHealBeacon::PulseHeal()
{
    if (!EffectClass) return;

	// Get all overlapping actors that are of type APlayerCharacter only
    TArray<AActor*> OverlappingActors;
    OverlapSphere->GetOverlappingActors(OverlappingActors, APlayerCharacter::StaticClass());

    for (AActor* Actor : OverlappingActors)
    {
        UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
        if (TargetASC)
        {
            // Create an effect context
            FGameplayEffectContextHandle Context = TargetASC->MakeEffectContext();
            Context.AddInstigator(GetInstigator(), this);

            // Create an outgoing spec and apply it
            FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(EffectClass, 1.0f, Context);
            if (SpecHandle.IsValid())
            {
                TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
            }
        }
    }
}
