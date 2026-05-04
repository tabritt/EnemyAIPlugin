#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/DamageType.h"
#include "EnemyBase.generated.h"

class UStaticMeshComponent;
class UUtilityAIComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);
UCLASS()
class ENEMYAIPLUGIN_API AEnemyBase : public ACharacter
{
    GENERATED_BODY()

public:
    AEnemyBase();

protected:
    virtual void BeginPlay() override;
    

public:
    virtual void Tick(float DeltaTime) override;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* WeaponMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float MaxHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float CurrentHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackDamage = 25.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackRange = 150.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float RunSpeed = 600.0f;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDeathDelegate OnDeathDelegate;

    // Override the built-in TakeDamage function
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void PerformAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool IsDead() const { return CurrentHealth <= 0.0f; }

    UFUNCTION(BlueprintCallable, Category = "Combat")
    float GetHealthPercentage() const { return CurrentHealth / MaxHealth; }

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetMovementState(bool bIsRunning);
    bool CanAttack() const;

protected:
    UFUNCTION()
    void OnAttackFinished();

    UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
    void OnAttackStart();

    UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
    void OnAttackEnd();

    UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
    void OnDeath();

    UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
    void OnDamageTaken(float DamageAmount);

    void ApplyDamageToTarget(AActor* TargetActor);
    

public:
    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bIsAttacking;

private:
    bool bIsRunning;

    FTimerHandle AttackTimer;
    float AttackDuration = 1.0f;
};


