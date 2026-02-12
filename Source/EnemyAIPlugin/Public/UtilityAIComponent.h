#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UtilityAIComponent.generated.h"

class UUtilityAIAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ENEMYAIPLUGIN_API UUtilityAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Instanced)
	TArray<UUtilityAIAction*> Actions;

	UFUNCTION(BlueprintCallable)
	void EvaluateAndExecute();
};
