#include "UtilityAIAction.h"
#include "UtilityAIConsideration.h"

// Base class for Utility AI actions.
// Each action has a set of Considerations that evaluate its desirability.
// Evaluate() combines consideration scores multiplicatively to determine
// the action's overall utility. Execute() performs the action when chosen.

float UUtilityAIAction::Evaluate_Implementation(AActor* ControlledActor)
{
	if (Considerations.Num() == 0)
		return 0.f;

	float TotalScore = 1.f;

	for (UUtilityAIConsideration* Consideration : Considerations)
	{
		if (!Consideration) continue;

		float Score = Consideration->Score(ControlledActor);
		TotalScore *= Score; // Multiplicative scoring
	}

	return TotalScore;
}

void UUtilityAIAction::Execute_Implementation(AActor* ControlledActor)
{
	// Override in BP or C++
}
