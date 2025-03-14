// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "EnemySpawner.generated.h"

UCLASS()
class GAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    void spawnEnemy(TSubclassOf<AActor>) const;
    
    TSubclassOf<AActor> whichEnemy() const;
    
private:
    static constexpr int RAND_SPAWN_UPPER = 510;
    static constexpr int RAND_SPAWN_LOWER = 490;
    
    static constexpr int RAND_LOCATION_UPPER = 1400;
    static constexpr int RAND_LOCATION_LOWER = 800;
    
    UPROPERTY(EditAnywhere, Category = "Enemy Spawning")
    TArray<TSubclassOf<AActor>> EnemyTypes;
    
    bool shouldSpawnEnemy() const;
};
