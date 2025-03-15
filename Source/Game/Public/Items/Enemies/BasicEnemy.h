#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"    // New AI Perception Component
#include "Perception/AISenseConfig_Sight.h"        // Sight sense configuration
#include "Items/Enemies/Enemy.h"
#include "BasicEnemy.generated.h"

UCLASS()
class GAME_API ABasicEnemy : public ACharacter, public IEnemy
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ABasicEnemy();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    
    static constexpr float MIN_DISTANCE = 100.0;
    static constexpr float ATTACK_RANGE = 195.0;
    static constexpr float ATTACK_INTERVAL = 2.0f;
    
    static constexpr int DAMAGE = 25;
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    virtual void takeDamage_Implementation(int damage) override;
    
    // Callback for when the perception component is updated
    UFUNCTION()
    void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    // Follow the sensed player
    void FollowPlayer();
    
    // Placeholder for attack functionality
    void attack();

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    int health;
    
    static constexpr int STARTING_HEALTH = 100;
    
    virtual int getDamage_Implementation() override;
    
    void startAttackTimer();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* AttackMontage;
    
private:
    // AI Perception component for sensing
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComp;

    // Sight configuration for the perception component
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAISenseConfig_Sight* SightConfig;

    // Flag set when a player is sensed
    bool isSensingPlayer;

    // The pawn (player) detected
    APawn* TargetPawn;
    
    FTimerHandle AttackTimerHandle;
    bool isAttacking;
    
   
};
