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
