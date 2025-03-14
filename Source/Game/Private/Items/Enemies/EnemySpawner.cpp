#include "Items/Enemies/EnemySpawner.h"  // Must be the first include.
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
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Should spawn"));
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
    
    UWorld* World = GetWorld();
    if (!World)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Couldn't get world"));
        return;
    }
    
    APlayerController* PC = World->GetFirstPlayerController();
    if (!PC || !PC->GetPawn())
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Couldn't get player"));
        return;
    }
    
    FVector PlayerLocation = PC->GetPawn()->GetActorLocation();
    
    
    float OffsetX = FMath::RandRange(RAND_LOCATION_LOWER, RAND_LOCATION_UPPER) * (FMath::RandBool() ? 1.f : -1.f);
    float OffsetY = FMath::RandRange(RAND_LOCATION_LOWER, RAND_LOCATION_UPPER) * (FMath::RandBool() ? 1.f : -1.f);
    
    FVector SpawnLocation = PlayerLocation + FVector(OffsetX, OffsetY, 0.f);
    
    FRotator SpawnRotation = FRotator::ZeroRotator;
    
    AActor* SpawnedEnemy = World->SpawnActor<AActor>(EnemyClass, SpawnLocation, SpawnRotation);
    if (SpawnedEnemy)
    {
        // Verify that the spawned actor implements IEnemy.
        if (SpawnedEnemy->GetClass()->ImplementsInterface(UEnemy::StaticClass()))
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Enemy spawned successfully and implements IEnemy!"));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Spawned actor does NOT implement IEnemy!"));
        }
    }
}


bool AEnemySpawner::shouldSpawnEnemy() const
{
    int32 RandomNumber = FMath::RandRange(1, 1000);
    
    return RandomNumber >= AEnemySpawner::RAND_SPAWN_LOWER && RandomNumber <= AEnemySpawner::RAND_SPAWN_UPPER;
}
