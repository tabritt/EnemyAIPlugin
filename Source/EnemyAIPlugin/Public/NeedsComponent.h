// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NeedsComponent.generated.h"

UCLASS (Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ENEMYAIPLUGIN_API UNeedsComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Health & Stamina (common for enemies or companions)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Needs")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Needs")
	float Stamina = 100.f;

	// Hunger, Hygiene, Bladder, Enjoyment (for Sims-like NPCs)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Needs")
	float Hunger = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Needs")
	float Hygiene = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Needs")
	float Bladder = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Needs")
	float Enjoyment = 0.f;

	// Magic (for enemies or casters)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Needs")
	float Magic = 100.f;

	
	UFUNCTION(BlueprintCallable, Category="Needs")
	void UpdateNeeds(float DeltaTime);
};