// Fill out your copyright notice in the Description page of Project Settings.


#include "A_EnemyBase.h"

// Sets default values
AA_EnemyBase::AA_EnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AA_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

