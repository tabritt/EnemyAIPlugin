#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityAIConsideration.generated.h"

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class ENEMYAIPLUGIN_API UUtilityAIConsideration : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	float Score(AActor* ControlledActor);
};
