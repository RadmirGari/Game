#include "Items/Enemies/BasicEnemy.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABasicEnemy::ABasicEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    // Initialize health
    health = STARTING_HEALTH;
    isSensingPlayer = false;
    TargetPawn = nullptr;

    // Create the AI Perception component
    AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));

    // Create and configure the sight sense configuration
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    if (SightConfig)
    {
        SightConfig->SightRadius = 1000.f;
        SightConfig->LoseSightRadius = 1200.f;
        SightConfig->PeripheralVisionAngleDegrees = 180.f;
        SightConfig->SetMaxAge(5.0f);
        SightConfig->DetectionByAffiliation.bDetectEnemies = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

        // Configure the perception component to use the sight sense
        AIPerceptionComp->ConfigureSense(*SightConfig);
        AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
    }

    // --- Mesh Setup ---
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(
        TEXT("/Script/Engine.SkeletalMesh'/Game/FPWeapon/Mesh/TutorialTPP.TutorialTPP'")
    );

    if (MeshAsset.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(MeshAsset.Object);
        GetMesh()->SetHiddenInGame(false);
        GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -85.0f));
        GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
        GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Mesh asset not found at the specified path."));
    }
}

void ABasicEnemy::BeginPlay()
{
    Super::BeginPlay();

    if (AIPerceptionComp)
    {
        // Bind the perception update event
        AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ABasicEnemy::OnTargetPerceptionUpdated);
    }
}

void ABasicEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!TargetPawn){
        return;
    }
    
    float Distance = FVector::Dist(TargetPawn->GetActorLocation(), GetActorLocation());

    if (Distance > SightConfig->SightRadius)
    {
        isSensingPlayer = false;
        TargetPawn = nullptr;
    }
    
    if(Distance < ABasicEnemy::ATTACK_RANGE){
        startAttackTimer();
    } else {
        FollowPlayer();
    }
}

void ABasicEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasicEnemy::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    APawn* SeenPawn = Cast<APawn>(Actor);
    if (!SeenPawn) return;

    if (!Stimulus.WasSuccessfullySensed()){
        isSensingPlayer = false;
        TargetPawn = nullptr;
        return;
    }
    
    isSensingPlayer = true;
    TargetPawn = SeenPawn;
}

void ABasicEnemy::FollowPlayer()
{
    if (!isSensingPlayer || !TargetPawn)
    {
        return;
    }

    AAIController* AIController = Cast<AAIController>(GetController());
    if (!AIController)
    {
        return;
    }
    
    AIController->MoveToActor(TargetPawn, ABasicEnemy::MIN_DISTANCE);
}

void ABasicEnemy::startAttackTimer(){
    if (isAttacking) return;

        isAttacking = true;

        GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ABasicEnemy::attack, ATTACK_INTERVAL, true);
}

void ABasicEnemy::attack()
{
    if (TargetPawn == nullptr || !TargetPawn->Implements<UDamageable>()){
       isAttacking = false;
       GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
       return;
   }

   float Distance = FVector::Dist(TargetPawn->GetActorLocation(), GetActorLocation());
   if (Distance >= ABasicEnemy::ATTACK_RANGE){
       isAttacking = false;
       GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
       return;
   }

   IDamageable::Execute_takeDamage(TargetPawn, ABasicEnemy::getDamage_Implementation());
}

int ABasicEnemy::getDamage_Implementation(){
    return DAMAGE;
}

void ABasicEnemy::takeDamage_Implementation(int damage)
{
    health -= damage;
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Health: %d"), health));
    if (health <= 0)
    {
        Destroy();
    }
}
