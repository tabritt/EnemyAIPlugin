// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "UtilityAIComponent.h"

AEnemyAIController::AEnemyAIController()
{
    PrimaryActorTick.bCanEverTick = false;

    UtilityAIComponent = CreateDefaultSubobject<UUtilityAIComponent>(TEXT("UtilityAIComponent"));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    
    if (GetWorld() && UtilityAIComponent)
    {
        GetWorld()->GetTimerManager().SetTimer(
            EvaluationTimer,
            this,
            &AEnemyAIController::OnEvaluationTimer,
            EvaluationInterval,
            true
        );
    }
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AEnemyAIController::OnEvaluationTimer()
{
    if (UtilityAIComponent)
    {
        UtilityAIComponent->EvaluateAndExecute();
    }
}