//COPYRIGHT:: TigerBritt

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class UUtilityAIComponent;
class AEnemyCharacter;

UCLASS()
class ENEMYAIPLUGIN_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY()
	UUtilityAIComponent* UtilityAIComponent;

	UPROPERTY(EditAnywhere, Category="AI")
	float EvaluationInterval = 0.5f;

	FTimerHandle EvaluationTimer;

	void OnEvaluationTimer();
};
