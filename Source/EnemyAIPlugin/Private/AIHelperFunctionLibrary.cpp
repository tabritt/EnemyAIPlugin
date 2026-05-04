#include "AIHelperFunctionLibrary.h"
#include "NeedsComponent.h"
#include "EnemyBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"

// Distance Functions

float UAIHelperFunctionLibrary::GetDistanceScore(AActor* Actor, AActor* Target, float OptimalRange, float MaxRange)
{
    if (!Actor || !Target) return 0.0f;
    
    float Distance = FVector::Dist(Actor->GetActorLocation(), Target->GetActorLocation());
    
    if (Distance <= OptimalRange) return 1.0f;
    if (Distance >= MaxRange) return 0.0f;
    
    // Linear interpolation between optimal and max range
    return FMath::GetMappedRangeValueClamped(FVector2D(OptimalRange, MaxRange), FVector2D(1.0f, 0.0f), Distance);
}

bool UAIHelperFunctionLibrary::IsInRange(AActor* Actor, AActor* Target, float Range)
{
    if (!Actor || !Target) return false;
    
    float Distance = FVector::Dist(Actor->GetActorLocation(), Target->GetActorLocation());
    return Distance <= Range;
}

float UAIHelperFunctionLibrary::GetProximityScore(AActor* Actor, AActor* Target, float PreferredDistance)
{
    if (!Actor || !Target) return 0.0f;
    
    float Distance = FVector::Dist(Actor->GetActorLocation(), Target->GetActorLocation());
    
    // Score is highest at preferred distance, falls off as we get further away
    if (Distance <= PreferredDistance) return 1.0f;
    
    // Linear falloff beyond preferred distance
    float MaxDistance = PreferredDistance * 3.0f; // Arbitrary max for scoring
    if (Distance >= MaxDistance) return 0.0f;
    
    return FMath::GetMappedRangeValueClamped(FVector2D(PreferredDistance, MaxDistance), FVector2D(1.0f, 0.0f), Distance);
}

float UAIHelperFunctionLibrary::GetDistanceToActor(AActor* Actor, AActor* Target)
{
    if (!Actor || !Target) return FLT_MAX;
    
    return FVector::Dist(Actor->GetActorLocation(), Target->GetActorLocation());
}

// Health Functions

float UAIHelperFunctionLibrary::GetHealthScore(AActor* Actor, float LowHealthThreshold)
{
    if (!Actor) return 0.5f;
    
    UNeedsComponent* Needs = GetNeedsComponent(Actor);
    if (!Needs) return 0.5f; // Default middle score if no needs component
    
    float HealthPercent = Needs->Health / 100.0f;
    
    if (HealthPercent <= LowHealthThreshold) return 0.1f; // Low health = low score
    if (HealthPercent >= 0.8f) return 1.0f; // High health = high score
    
    // Linear interpolation between low threshold and 80%
    return FMath::GetMappedRangeValueClamped(FVector2D(LowHealthThreshold, 0.8f), FVector2D(0.1f, 1.0f), HealthPercent);
}

bool UAIHelperFunctionLibrary::IsHealthLow(AActor* Actor, float Threshold)
{
    if (!Actor) return false;
    
    UNeedsComponent* Needs = GetNeedsComponent(Actor);
    if (!Needs) return false;
    
    return (Needs->Health / 100.0f) <= Threshold;
}

float UAIHelperFunctionLibrary::GetTargetHealthScore(AActor* TargetActor, float LowHealthThreshold)
{
    if (!TargetActor) return 0.0f;
    
    UNeedsComponent* Needs = GetNeedsComponent(TargetActor);
    if (!Needs) return 0.5f;
    
    float HealthPercent = Needs->Health / 100.0f;
    
    // For target health, we want higher score when target is weaker
    if (HealthPercent <= LowHealthThreshold) return 1.0f; // Weak target = high score
    if (HealthPercent >= 0.8f) return 0.1f; // Strong target = low score
    
    // Inverse linear interpolation
    return FMath::GetMappedRangeValueClamped(FVector2D(LowHealthThreshold, 0.8f), FVector2D(1.0f, 0.1f), HealthPercent);
}

float UAIHelperFunctionLibrary::GetHealthPercentage(AActor* Actor)
{
    if (!Actor) return 0.0f;
    
    UNeedsComponent* Needs = GetNeedsComponent(Actor);
    if (!Needs) return 1.0f;
    
    return Needs->Health / 100.0f;
}

// Needs Functions

float UAIHelperFunctionLibrary::GetHungerScore(AActor* Actor, float HighHungerThreshold)
{
    if (!Actor) return 0.0f;
    
    UNeedsComponent* Needs = GetNeedsComponent(Actor);
    if (!Needs) return 0.0f;
    
    float HungerPercent = Needs->Hunger / 100.0f;
    
    if (HungerPercent >= HighHungerThreshold) return 1.0f; // Very hungry = high priority
    if (HungerPercent <= 0.3f) return 0.1f; // Not hungry = low priority
    
    return FMath::GetMappedRangeValueClamped(FVector2D(0.3f, HighHungerThreshold), FVector2D(0.1f, 1.0f), HungerPercent);
}

bool UAIHelperFunctionLibrary::IsHungry(AActor* Actor, float Threshold)
{
    if (!Actor) return false;
    
    UNeedsComponent* Needs = GetNeedsComponent(Actor);
    if (!Needs) return false;
    
    return (Needs->Hunger / 100.0f) >= Threshold;
}

float UAIHelperFunctionLibrary::GetStaminaScore(AActor* Actor, float LowStaminaThreshold)
{
    if (!Actor) return 1.0f;
    
    UNeedsComponent* Needs = GetNeedsComponent(Actor);
    if (!Needs) return 1.0f;
    
    float StaminaPercent = Needs->Stamina / 100.0f;
    
    if (StaminaPercent <= LowStaminaThreshold) return 0.1f; // Low stamina = low score
    if (StaminaPercent >= 0.8f) return 1.0f; // High stamina = high score
    
    return FMath::GetMappedRangeValueClamped(FVector2D(LowStaminaThreshold, 0.8f), FVector2D(0.1f, 1.0f), StaminaPercent);
}

bool UAIHelperFunctionLibrary::IsTired(AActor* Actor, float Threshold)
{
    if (!Actor) return false;
    
    UNeedsComponent* Needs = GetNeedsComponent(Actor);
    if (!Needs) return false;
    
    return (Needs->Stamina / 100.0f) <= Threshold;
}

float UAIHelperFunctionLibrary::GetMagicScore(AActor* Actor, float LowMagicThreshold)
{
    if (!Actor) return 0.0f;
    
    UNeedsComponent* Needs = GetNeedsComponent(Actor);
    if (!Needs) return 0.0f;
    
    float MagicPercent = Needs->Magic / 100.0f;
    
    if (MagicPercent <= LowMagicThreshold) return 0.1f; // Low magic = low score
    if (MagicPercent >= 0.8f) return 1.0f; // High magic = high score
    
    return FMath::GetMappedRangeValueClamped(FVector2D(LowMagicThreshold, 0.8f), FVector2D(0.1f, 1.0f), MagicPercent);
}

// Visibility Functions

bool UAIHelperFunctionLibrary::HasLineOfSight(AActor* Actor, AActor* Target)
{
    if (!Actor || !Target) return false;
    
    FVector StartLocation = Actor->GetActorLocation();
    FVector EndLocation = Target->GetActorLocation();
    
    // Adjust start location to actor's eye level
    StartLocation.Z += Actor->GetSimpleCollisionRadius() * 0.8f;
    
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(Actor);
    
    UWorld* World = Actor->GetWorld();
    if (!World) return false;

    bool bHit = World->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECC_Visibility,
        QueryParams
    );
    
    // If we hit something, check if it's our target
    return !bHit || HitResult.GetActor() == Target;
}

float UAIHelperFunctionLibrary::GetVisibilityScore(AActor* Actor, AActor* Target)
{
    if (!Actor || !Target) return 0.0f;
    
    if (HasLineOfSight(Actor, Target))
    {
        float Distance = GetDistanceToActor(Actor, Target);
        float MaxVisibilityDistance = 1000.0f; // Adjust as needed
        
        if (Distance <= MaxVisibilityDistance)
        {
            return FMath::GetMappedRangeValueClamped(FVector2D(0.0f, MaxVisibilityDistance), FVector2D(1.0f, 0.1f), Distance);
        }
    }
    
    return 0.0f;
}

bool UAIHelperFunctionLibrary::IsPlayerVisible(AActor* Actor)
{
    AActor* Player = GetPlayerCharacter(Actor);
    if (!Player) return false;
    
    return HasLineOfSight(Actor, Player);
}

// Math Functions

float UAIHelperFunctionLibrary::NormalizeScore(float Value, float Min, float Max)
{
    if (FMath::IsNearlyEqual(Max, Min)) return 0.5f;
    
    return FMath::GetMappedRangeValueClamped(FVector2D(Min, Max), FVector2D(0.0f, 1.0f), Value);
}

float UAIHelperFunctionLibrary::InverseScore(float Score)
{
    return FMath::Clamp(1.0f - Score, 0.0f, 1.0f);
}

float UAIHelperFunctionLibrary::CurveScore(float Value, bool bInvert)
{
    // Apply a gentle S-curve for more natural scoring
    float Curved = Value * Value * (3.0f - 2.0f * Value); // Smoothstep
    
    if (bInvert)
    {
        Curved = 1.0f - Curved;
    }
    
    return FMath::Clamp(Curved, 0.0f, 1.0f);
}

float UAIHelperFunctionLibrary::ClampScore(float Score, float Min, float Max)
{
    return FMath::Clamp(Score, Min, Max);
}

// Combat Functions

bool UAIHelperFunctionLibrary::CanAttack(AActor* Actor)
{
    AEnemyBase* Enemy = Cast<AEnemyBase>(Actor);
    if (!Enemy) return false;
    
    return Enemy->CanAttack();
}

float UAIHelperFunctionLibrary::GetAttackCooldownScore(AActor* Actor)
{
    if (CanAttack(Actor))
    {
        return 1.0f; // Can attack = high score
    }
    return 0.0f; // On cooldown = no score
}

float UAIHelperFunctionLibrary::GetThreatLevel(AActor* Actor, AActor* Target)
{
    if (!Actor || !Target) return 0.0f;
    
    float DistanceScore = GetDistanceScore(Actor, Target, 200.0f, 800.0f);
    float TargetHealthScore = GetTargetHealthScore(Target, 0.3f);
    
    // Combine distance and target health for overall threat assessment
    return (DistanceScore * 0.6f) + (TargetHealthScore * 0.4f);
}

// Utility Functions

AActor* UAIHelperFunctionLibrary::GetPlayerCharacter(AActor* ContextActor)
{
    if (!ContextActor || !ContextActor->GetWorld()) return nullptr;
    
    return UGameplayStatics::GetPlayerCharacter(ContextActor->GetWorld(), 0);
}

UNeedsComponent* UAIHelperFunctionLibrary::GetNeedsComponent(AActor* Actor)
{
    if (!Actor) return nullptr;
    
    return Actor->FindComponentByClass<UNeedsComponent>();
}

bool UAIHelperFunctionLibrary::IsDead(AActor* Actor)
{
    AEnemyBase* Enemy = Cast<AEnemyBase>(Actor);
    if (Enemy)
    {
        return Enemy->IsDead();
    }
    
    // Fallback: check if needs component has zero health
    UNeedsComponent* Needs = GetNeedsComponent(Actor);
    if (Needs)
    {
        return Needs->Health <= 0.0f;
    }
    
    return false;
}

// Time Functions

float UAIHelperFunctionLibrary::GetTimeOfDayScore(float PreferredHour, float CurrentHour)
{
    // Normalize hours to 0-1 range
    float Preferred = PreferredHour / 24.0f;
    float Current = CurrentHour / 24.0f;
    
    // Calculate circular distance (handles midnight wraparound)
    float Distance = FMath::Abs(Preferred - Current);
    if (Distance > 0.5f) Distance = 1.0f - Distance;
    
    // Convert distance to score (closer = higher score)
    return FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 0.5f), FVector2D(1.0f, 0.0f), Distance);
}

bool UAIHelperFunctionLibrary::IsNighttime(float CurrentHour)
{
    return CurrentHour >= 20.0f || CurrentHour <= 6.0f;
}

float UAIHelperFunctionLibrary::GetCurrentHour()
{
    // This would need to be implemented based on your game's time system
    // For now, return a placeholder or get from game world
    if (GWorld && GWorld->GetGameState())
    {
        // You might have a custom game state with time tracking
        // For now, return a simple day/night cycle based on real time
        FDateTime Now = FDateTime::Now();
        return static_cast<float>(Now.GetHour()) + (Now.GetMinute() / 60.0f);
    }
    
    return 12.0f; // Default to noon
}
// Weighted Scoring Helper Functions

float UAIHelperFunctionLibrary::ApplyWeight(float Score, float Weight)
{
    // Apply weight using power function
    return FMath::Pow(FMath::Clamp(Score, 0.0f, 1.0f), FMath::Clamp(Weight, 0.1f, 3.0f));
}

float UAIHelperFunctionLibrary::GetWeightedScore(float Score, float Importance)
{
    // Importance: 0.0-1.0 (Low to High)
    // Maps to weight: 0.5-2.0 (Less to More important)
    float Weight = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(0.5f, 2.0f), Importance);
    return ApplyWeight(Score, Weight);
}

float UAIHelperFunctionLibrary::GetCriticalWeight(float Score)
{
    // Critical considerations get high weight (2.0)
    return ApplyWeight(Score, 2.0f);
}

float UAIHelperFunctionLibrary::GetMinorWeight(float Score)
{
    // Minor considerations get low weight (0.5)
    return ApplyWeight(Score, 0.5f);
}

float UAIHelperFunctionLibrary::GetBalancedWeight(float Score)
{
    // Balanced considerations get normal weight (1.0)
    return ApplyWeight(Score, 1.0f);
}
