#include "UtilityAIAction.h"
#include "UtilityAIConsideration.h"

// Base class for Utility AI actions.
// Each action has a set of Considerations that evaluate its desirability.
// Evaluate() combines consideration scores multiplicatively to determine
// the action's overall utility. Execute() performs the action when chosen.

#include "UtilityAIAction.h"
#include "UtilityAIConsideration.h"

float UUtilityAIAction::Evaluate_Implementation(AActor* ControlledActor)
{
	// Migrate legacy considerations if needed
	MigrateLegacyConsiderations();

	if (bUseWeightedScoring)
	{
		return CalculateWeightedScore(ControlledActor);
	}
	else
	{
		return CalculateSimpleScore(ControlledActor);
	}
}

void UUtilityAIAction::Execute_Implementation(AActor* ControlledActor)
{
	// Override in BP or C++
}

void UUtilityAIAction::MigrateLegacyConsiderations()
{
	// If we have legacy considerations but no weighted ones, migrate them
	if (Considerations.Num() > 0 && WeightedConsiderations.Num() == 0)
	{
		for (UUtilityAIConsideration* LegacyConsideration : Considerations)
		{
			if (LegacyConsideration)
			{
				FWeightedConsideration WeightedConsideration;
				WeightedConsideration.Consideration = LegacyConsideration;
				WeightedConsideration.Weight = 1.0f; // Default weight
				WeightedConsiderations.Add(WeightedConsideration);
			}
		}
		// Clear legacy array to avoid duplication
		Considerations.Empty();
	}
}

float UUtilityAIAction::CalculateWeightedScore(AActor* ControlledActor)
{
	if (WeightedConsiderations.Num() == 0)
		return 0.f;

	float TotalScore = 1.f;

	for (const FWeightedConsideration& WeightedConsideration : WeightedConsiderations)
	{
		if (!WeightedConsideration.Consideration) continue;

		float Score = WeightedConsideration.Consideration->Score(ControlledActor);
		
		// Apply weight using power function: Score^Weight
		// Weight > 1.0: Amplifies the score (more important)
		// Weight < 1.0: Dampens the score (less important)
		// Weight = 1.0: No effect (normal multiplication)
		float WeightedScore = FMath::Pow(Score, WeightedConsideration.Weight);
		
		TotalScore *= WeightedScore;

		// Early exit if score becomes 0 (multiplicative property)
		if (TotalScore <= 0.f)
		{
			return 0.f;
		}
	}

	// Apply global weight multiplier
	TotalScore *= GlobalWeightMultiplier;

	// Clamp to valid range
	return FMath::Clamp(TotalScore, 0.f, 1.f);
}

float UUtilityAIAction::CalculateSimpleScore(AActor* ControlledActor)
{
	// Use weighted considerations array but ignore weights (treat all as weight 1.0)
	if (WeightedConsiderations.Num() == 0)
		return 0.f;

	float TotalScore = 1.f;

	for (const FWeightedConsideration& WeightedConsideration : WeightedConsiderations)
	{
		if (!WeightedConsideration.Consideration) continue;

		float Score = WeightedConsideration.Consideration->Score(ControlledActor);
		TotalScore *= Score; // Simple multiplication

		// Early exit if score becomes 0
		if (TotalScore <= 0.f)
		{
			return 0.f;
		}
	}

	return FMath::Clamp(TotalScore, 0.f, 1.f);
}

