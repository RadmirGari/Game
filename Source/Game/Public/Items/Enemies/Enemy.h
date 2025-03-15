// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.h"
#include "Enemy.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UEnemy : public UDamageable // Inherit from UInterface NOT UDamageable
{
    GENERATED_BODY()
};

// Correct IEnemy declaration
class GAME_API IEnemy : public IDamageable // Implements IDamageable interface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int getDamage();
};
