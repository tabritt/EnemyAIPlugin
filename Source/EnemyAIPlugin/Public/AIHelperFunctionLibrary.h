#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AIHelperFunctionLibrary.generated.h"

class UNeedsComponent;
class AActor;

UCLASS()
class ENEMYAIPLUGIN_API UAIHelperFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // Distance Functions
    UFUNCTION(BlueprintCallable, Category = "AI Helper|Distance", meta = (CompactNodeTitle = "Distance Score"))
    static float GetDistanceScore(AActor* Actor, AActor* Target, float OptimalRange, float MaxRange);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Distance", meta = (CompactNodeTitle = "Is In Range"))
    static bool IsInRange(AActor* Actor, AActor* Target, float Range);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Distance", meta = (CompactNodeTitle = "Proximity Score"))
    static float GetProximityScore(AActor* Actor, AActor* Target, float PreferredDistance);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Distance", meta = (CompactNodeTitle = "Distance"))
    static float GetDistanceToActor(AActor* Actor, AActor* Target);

    // Health Functions
    UFUNCTION(BlueprintCallable, Category = "AI Helper|Health", meta = (CompactNodeTitle = "Health Score"))
    static float GetHealthScore(AActor* Actor, float LowHealthThreshold = 0.3f);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Health", meta = (CompactNodeTitle = "Is Health Low"))
    static bool IsHealthLow(AActor* Actor, float Threshold = 0.3f);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Health", meta = (CompactNodeTitle = "Target Health Score"))
    static float GetTargetHealthScore(AActor* TargetActor, float LowHealthThreshold = 0.3f);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Health", meta = (CompactNodeTitle = "Health Percentage"))
    static float GetHealthPercentage(AActor* Actor);

    // Needs Functions
    UFUNCTION(BlueprintCallable, Category = "AI Helper|Needs", meta = (CompactNodeTitle = "Hunger Score"))
    static float GetHungerScore(AActor* Actor, float HighHungerThreshold = 0.7f);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Needs", meta = (CompactNodeTitle = "Is Hungry"))
    static bool IsHungry(AActor* Actor, float Threshold = 0.7f);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Needs", meta = (CompactNodeTitle = "Stamina Score"))
    static float GetStaminaScore(AActor* Actor, float LowStaminaThreshold = 0.3f);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Needs", meta = (CompactNodeTitle = "Is Tired"))
    static bool IsTired(AActor* Actor, float Threshold = 0.3f);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Needs", meta = (CompactNodeTitle = "Magic Score"))
    static float GetMagicScore(AActor* Actor, float LowMagicThreshold = 0.3f);

    // Visibility Functions
    UFUNCTION(BlueprintCallable, Category = "AI Helper|Visibility", meta = (CompactNodeTitle = "Has Line of Sight"))
    static bool HasLineOfSight(AActor* Actor, AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Visibility", meta = (CompactNodeTitle = "Visibility Score"))
    static float GetVisibilityScore(AActor* Actor, AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Visibility", meta = (CompactNodeTitle = "Is Player Visible"))
    static bool IsPlayerVisible(AActor* Actor);

    // Math Functions
    UFUNCTION(BlueprintCallable, Category = "AI Helper|Math", meta = (CompactNodeTitle = "Normalize"))
    static float NormalizeScore(float Value, float Min, float Max);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Math", meta = (CompactNodeTitle = "Inverse"))
    static float InverseScore(float Score);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Math", meta = (CompactNodeTitle = "Curve Score"))
    static float CurveScore(float Value, bool bInvert = false);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Math", meta = (CompactNodeTitle = "Clamp Score"))
    static float ClampScore(float Score, float Min = 0.0f, float Max = 1.0f);

    // Combat Functions
    UFUNCTION(BlueprintCallable, Category = "AI Helper|Combat", meta = (CompactNodeTitle = "Can Attack"))
    static bool CanAttack(AActor* Actor);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Combat", meta = (CompactNodeTitle = "Attack Cooldown Score"))
    static float GetAttackCooldownScore(AActor* Actor);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Combat", meta = (CompactNodeTitle = "Threat Level"))
    static float GetThreatLevel(AActor* Actor, AActor* Target);

    // Utility Functions
    UFUNCTION(BlueprintCallable, Category = "AI Helper|Utility", meta = (CompactNodeTitle = "Get Player"))
    static AActor* GetPlayerCharacter(AActor* ContextActor);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Utility", meta = (CompactNodeTitle = "Needs Component"))
    static UNeedsComponent* GetNeedsComponent(AActor* Actor);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Utility", meta = (CompactNodeTitle = "Is Dead"))
    static bool IsDead(AActor* Actor);

    // Time Functions
    UFUNCTION(BlueprintCallable, Category = "AI Helper|Time", meta = (CompactNodeTitle = "Time of Day Score"))
    static float GetTimeOfDayScore(float PreferredHour, float CurrentHour);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Time", meta = (CompactNodeTitle = "Is Night"))
    static bool IsNighttime(float CurrentHour);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Time", meta = (CompactNodeTitle = "Current Hour"))
    static float GetCurrentHour();
    // Weighted Scoring Helper Functions
    UFUNCTION(BlueprintCallable, Category = "AI Helper|Weighted Scoring", meta = (CompactNodeTitle = "Apply Weight"))
    static float ApplyWeight(float Score, float Weight);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Weighted Scoring", meta = (CompactNodeTitle = "Weighted Score"))
    static float GetWeightedScore(float Score, float Importance);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Weighted Scoring", meta = (CompactNodeTitle = "Critical Weight"))
    static float GetCriticalWeight(float Score);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Weighted Scoring", meta = (CompactNodeTitle = "Minor Weight"))
    static float GetMinorWeight(float Score);

    UFUNCTION(BlueprintCallable, Category = "AI Helper|Weighted Scoring", meta = (CompactNodeTitle = "Balanced Weight"))
    static float GetBalancedWeight(float Score);
};
