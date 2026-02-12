#include "UtilityAIAction.h"
#include "UtilityAIConsideration.h"


float UUtilityAIAction::Evaluate(AActor* ControlledActor)
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
