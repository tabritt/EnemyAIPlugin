#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NeedsComponent.generated.h"

UCLASS (Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ENEMYAIPLUGIN_API UNeedsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNeedsComponent();

protected:
	virtual void BeginPlay() override;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Needs")
	float NeedsUpdateInterval = 1.0f;

	UFUNCTION(BlueprintCallable, Category="Needs")
	void UpdateNeeds();

private:
	FTimerHandle NeedsUpdateTimer;

	void OnNeedsUpdateTimer();
};
