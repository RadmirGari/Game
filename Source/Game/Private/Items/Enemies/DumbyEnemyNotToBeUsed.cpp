// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Enemies/DumbyEnemyNotToBeUsed.h"

// Sets default values
ADumbyEnemyNotToBeUsed::ADumbyEnemyNotToBeUsed()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADumbyEnemyNotToBeUsed::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADumbyEnemyNotToBeUsed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADumbyEnemyNotToBeUsed::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void takeDamage_Implementation(int damage){
    return;
}

