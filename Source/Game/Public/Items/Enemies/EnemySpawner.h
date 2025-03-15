// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "SpawnPoint.h"
#include "EnemySpawner.generated.h"

UCLASS()
class GAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    void spawnEnemy(TSubclassOf<AActor>) const;
    
    TSubclassOf<AActor> whichEnemy() const;
    
    ASpawnPoint* whichSpawnPoint() const;
    
private:
    static constexpr int RAND_SPAWN_UPPER = 510;
    static constexpr int RAND_SPAWN_LOWER = 480;
    
    UPROPERTY(EditAnywhere, Category = "Enemy Spawning")
    TArray<TSubclassOf<AActor>> EnemyTypes;
    
    UPROPERTY(EditAnywhere, Category = "Spawn Points")
    TArray<ASpawnPoint*> spawnPoints;

    bool shouldSpawnEnemy() const;
};
