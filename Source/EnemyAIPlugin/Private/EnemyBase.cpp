#include "EnemyBase.h"
#include "UtilityAIComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	UtilityAIComponent = CreateDefaultSubobject<UUtilityAIComponent>(TEXT("UtilityAIComponent"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!UtilityAIComponent) return;

	TimeSinceLastEvaluation += DeltaTime;

	if (TimeSinceLastEvaluation >= EvaluationInterval)
	{
		UtilityAIComponent->EvaluateAndExecute();
		TimeSinceLastEvaluation = 0.f;
	}
}
