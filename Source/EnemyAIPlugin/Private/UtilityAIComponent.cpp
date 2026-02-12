#include "UtilityAIComponent.h"
#include "UtilityAIAction.h"


void UUtilityAIComponent::EvaluateAndExecute()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	float BestScore = -1.f;
	UUtilityAIAction* BestAction = nullptr;

	for (UUtilityAIAction* Action : Actions)
	{
		if (!Action) continue;

		float Score = Action->Evaluate(Owner);

		if (Score > BestScore)
		{
			BestScore = Score;
			BestAction = Action;
		}
	}

	if (BestAction)
	{
		BestAction->Execute(Owner);
	}
}
