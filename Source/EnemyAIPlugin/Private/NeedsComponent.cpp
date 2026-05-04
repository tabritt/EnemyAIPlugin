#include "NeedsComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

UNeedsComponent::UNeedsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNeedsComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			NeedsUpdateTimer,
			this,
			&UNeedsComponent::OnNeedsUpdateTimer,
			NeedsUpdateInterval,
			true
		);
	}
}

void UNeedsComponent::UpdateNeeds()
{
	// Example: slow decay for hunger, hygiene, bladder based on 1-second intervals
	Hunger += NeedsUpdateInterval * 0.1f;  
	Hygiene += NeedsUpdateInterval * 0.05f;
	Bladder += NeedsUpdateInterval * 0.08f;

	// Clamp values if you want 0–100
	Hunger = FMath::Clamp(Hunger, 0.f, 100.f);
	Hygiene = FMath::Clamp(Hygiene, 0.f, 100.f);
	Bladder = FMath::Clamp(Bladder, 0.f, 100.f);
}

void UNeedsComponent::OnNeedsUpdateTimer()
{
	UpdateNeeds();
}
