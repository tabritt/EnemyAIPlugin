#include "UtilityAIComponent.h"
#include "UtilityAIAction.h"
#include "EnemyAIController.h"


void UUtilityAIComponent::EvaluateAndExecute()
{
	AEnemyAIController* Controller = Cast<AEnemyAIController>(GetOwner());
	if (!Controller) return;

	APawn* Pawn = Controller->GetPawn();
	if (!Pawn) return;

	float BestScore = -1.f;
	UUtilityAIAction* BestAction = nullptr;

	for (UUtilityAIAction* Action : Actions)
	{
		if (!Action) continue;

		float Score = Action->Evaluate(Pawn);

		if (Score > BestScore)
		{
			BestScore = Score;
			BestAction = Action;
		}
	}

	if (BestAction)
	{
		BestAction->Execute(Pawn);
	}
}
