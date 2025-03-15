// Fill out your copyright notice in the Description page of Project Settings.
#include "SpawnPoint.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPoint::spawnEnemy(TSubclassOf<AActor> EnemyClass) const{
    if (!EnemyClass){
       return;
   }
   
   UWorld* World = GetWorld();
   if (!World)
   {
       return;
   }
   
   FVector SpawnLocation = GetActorLocation();
   float RandomOffsetX = FMath::RandRange(-RAND_LOCATION, RAND_LOCATION);
   float RandomOffsetY = FMath::RandRange(-RAND_LOCATION, RAND_LOCATION);
   SpawnLocation.X += RandomOffsetX;
   SpawnLocation.Y += RandomOffsetY;
   
   FRotator SpawnRotation = GetActorRotation();

   World->SpawnActor<AActor>(EnemyClass, SpawnLocation, SpawnRotation);
}

