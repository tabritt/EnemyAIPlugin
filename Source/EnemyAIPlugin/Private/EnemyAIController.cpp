// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "UtilityAIComponent.h"

AEnemyAIController::AEnemyAIController()
{
    PrimaryActorTick.bCanEverTick = true;

    UtilityAIComponent = CreateDefaultSubobject<UUtilityAIComponent>(TEXT("UtilityAIComponent"));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!UtilityAIComponent) return;

    TimeSinceLastEvaluation += DeltaSeconds;

    if (TimeSinceLastEvaluation >= EvaluationInterval)
    {
        UtilityAIComponent->EvaluateAndExecute();
        TimeSinceLastEvaluation = 0.f;
    }
}