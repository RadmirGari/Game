// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Pickable.h"
#include "Useable.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUseable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAME_API IUseable : public IPickable
{
	GENERATED_BODY()


public:
    virtual void use() = 0;
};
