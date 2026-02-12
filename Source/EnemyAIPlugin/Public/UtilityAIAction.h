#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityAIAction.generated.h"

class UUtilityAIConsideration;

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class ENEMYAIPLUGIN_API UUtilityAIAction : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Instanced)
	TArray<UUtilityAIConsideration*> Considerations;

	UFUNCTION(BlueprintCallable)
	virtual float Evaluate(AActor* ControlledActor);

	UFUNCTION(BlueprintNativeEvent)
	void Execute(AActor* ControlledActor);
};
