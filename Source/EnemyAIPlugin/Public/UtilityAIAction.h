#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityAIConsideration.h"
#include "UtilityAIAction.generated.h"

class UUtilityAIConsideration;

USTRUCT(BlueprintType)
struct FWeightedConsideration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consideration")
	UUtilityAIConsideration* Consideration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consideration", meta = (ClampMin = "0.1", ClampMax = "3.0"))
	float Weight = 1.0f;

	FWeightedConsideration()
	{
		Consideration = nullptr;
		Weight = 1.0f;
	}
};

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class ENEMYAIPLUGIN_API UUtilityAIAction : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Instanced, Category = "Considerations")
	TArray<FWeightedConsideration> WeightedConsiderations;

	// Legacy support - auto-populate WeightedConsiderations
	UPROPERTY(EditAnywhere, Instanced, Category = "Considerations", meta = (DeprecatedProperty, DeprecationMessage = "Use WeightedConsiderations instead"))
	TArray<UUtilityAIConsideration*> Considerations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	bool bUseWeightedScoring = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring", meta = (EditCondition = "bUseWeightedScoring"))
	float GlobalWeightMultiplier = 1.0f;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float Evaluate(AActor* ControlledActor);

	UFUNCTION(BlueprintNativeEvent)
	void Execute(AActor* ControlledActor);

protected:
	// Helper function to migrate legacy considerations
	void MigrateLegacyConsiderations();

	float CalculateWeightedScore(AActor* ControlledActor);
	float CalculateSimpleScore(AActor* ControlledActor);
};
