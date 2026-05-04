#include "EnemyBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/DamageType.h"
#include "Engine/DamageEvents.h"


AEnemyBase::AEnemyBase()
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetupAttachment(GetMesh(), TEXT("hand_r"));
    WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    CurrentHealth = MaxHealth;
    bIsAttacking = false;
    bIsRunning = false;

    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AEnemyBase::BeginPlay()
{
    Super::BeginPlay();
}

void AEnemyBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

float AEnemyBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    if (IsDead())
    {
        return 0.0f;
    }

    const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    
    if (ActualDamage > 0.0f)
    {
        CurrentHealth = FMath::Max(0.0f, CurrentHealth - ActualDamage);
        
        OnDamageTaken(ActualDamage);

        if (IsDead())
        {
            OnDeath();
            OnDeathDelegate.Broadcast();
            GetCharacterMovement()->DisableMovement();
            SetActorEnableCollision(false);
        }
    }
    
    return ActualDamage;
}

void AEnemyBase::PerformAttack()
{
    if (!CanAttack())
    {
        return;
    }

    bIsAttacking = true;
    OnAttackStart();

    FVector StartLocation = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    FVector EndLocation = StartLocation + ForwardVector * AttackRange;

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    QueryParams.bTraceComplex = true;

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECC_Pawn,
        QueryParams
    );

    if (bHit && HitResult.GetActor())
    {
        ApplyDamageToTarget(HitResult.GetActor());
    }

    DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 2.0f, 0, 2.0f);

    GetWorldTimerManager().SetTimer(
        AttackTimer,
        this,
        &AEnemyBase::OnAttackFinished,
        AttackDuration,
        false
    );
}

void AEnemyBase::OnAttackFinished()
{
    bIsAttacking = false;
    OnAttackEnd();
}

void AEnemyBase::SetMovementState(bool bNewIsRunning)
{
    bIsRunning = bNewIsRunning;

    if (bIsRunning)
    {
        GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }
}

void AEnemyBase::ApplyDamageToTarget(AActor* TargetActor)
{
    if (TargetActor && TargetActor != this)
    {
        ACharacter* TargetCharacter = Cast<ACharacter>(TargetActor);
        if (TargetCharacter)
        {
            FDamageEvent DamageEvent;
            TargetCharacter->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
        }
    }
}

bool AEnemyBase::CanAttack() const
{
    return !bIsAttacking && !IsDead();
}
