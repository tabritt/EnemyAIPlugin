#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class UUtilityAIComponent;

UCLASS(Blueprintable)
class ENEMYAIPLUGIN_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UUtilityAIComponent* UtilityAIComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float EvaluationInterval = 0.5f;

private:
	float TimeSinceLastEvaluation = 0.f;
};
