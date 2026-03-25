// Fill out your copyright notice in the Description page of Project Settings.


#include "NeedsComponent.h"

void UNeedsComponent::UpdateNeeds(float DeltaTime)
{
	// Example: slow decay for hunger, hygiene, bladder
	Hunger += DeltaTime * 0.1f;  
	Hygiene += DeltaTime * 0.05f;
	Bladder += DeltaTime * 0.08f;

	// Clamp values if you want 0–100
	Hunger = FMath::Clamp(Hunger, 0.f, 100.f);
	Hygiene = FMath::Clamp(Hygiene, 0.f, 100.f);
	Bladder = FMath::Clamp(Bladder, 0.f, 100.f);
}
