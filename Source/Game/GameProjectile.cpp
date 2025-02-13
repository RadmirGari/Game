// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Damageable.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"


AGameProjectile::AGameProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AGameProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AGameProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    
    if(OtherActor == nullptr || OtherActor == this || OtherComp == nullptr){
        return;
    }
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(OtherActor == PlayerPawn){
        return;
    }
    
    if (OtherActor->Implements<UDamageable>()) {
        IDamageable::Execute_takeDamage(OtherActor, AGameProjectile::getDamage_Implementation());
    }
    
    if (OtherComp->IsSimulatingPhysics()){
       OtherComp->AddImpulseAtLocation(ProjectileMovement->Velocity * 10.0f, Hit.ImpactPoint);
   }
    
    Destroy();
}

int AGameProjectile::getDamage_Implementation(){
    return AGameProjectile::DAMAGE;
}
