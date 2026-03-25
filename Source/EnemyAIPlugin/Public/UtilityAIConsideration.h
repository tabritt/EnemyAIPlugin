#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityAIConsideration.generated.h"

// Base class for Utility AI considerations.
// A Consideration calculates a score for a given actor, which represents 
// how desirable an action is. Subclasses or Blueprint overrides provide 
// specific scoring logic.

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class ENEMYAIPLUGIN_API UUtilityAIConsideration : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	float Score(AActor* ControlledActor);
};
