#include "Items/Enemies/EnemySpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay(){
    Super::BeginPlay();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
    if (shouldSpawnEnemy()){
        spawnEnemy(whichEnemy());
    }
}

TSubclassOf<AActor> AEnemySpawner::whichEnemy() const{
    int32 Index = FMath::RandRange(0, EnemyTypes.Num() - 1);
    return EnemyTypes[Index];
}

void AEnemySpawner::spawnEnemy(TSubclassOf<AActor> EnemyClass) const{
    if (!EnemyClass)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Not enemy class??"));
        return;
    }
    
    ASpawnPoint* SpawnPoint = whichSpawnPoint();
    if (SpawnPoint){
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Not enemy class??"));
        SpawnPoint->spawnEnemy(EnemyClass);
    }
}

ASpawnPoint* AEnemySpawner::whichSpawnPoint() const{
    int32 Index = FMath::RandRange(0, spawnPoints.Num() - 1);
    return spawnPoints[Index];
}


bool AEnemySpawner::shouldSpawnEnemy() const
{
    int32 RandomNumber = FMath::RandRange(1, 1000);
    
    return RandomNumber >= AEnemySpawner::RAND_SPAWN_LOWER && RandomNumber <= AEnemySpawner::RAND_SPAWN_UPPER;
}
