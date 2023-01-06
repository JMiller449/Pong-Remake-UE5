// Available for free use - Original Author Joseph Miller


#include "ABoundary.h"
#include "PongPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AABoundary::AABoundary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	// Static Meshes
	AIGoal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AIGoal"));
	AIGoal->SetupAttachment(DefaultSceneRoot);

	TopWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopWall"));
	TopWall->SetupAttachment(DefaultSceneRoot);

	BottomWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomWall"));
	BottomWall->SetupAttachment(DefaultSceneRoot);

	PlayerGoal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerGoal"));
	PlayerGoal->SetupAttachment(DefaultSceneRoot);

	// Collision Boxes
	AIGoalCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("AIGoalCollider"));
	AIGoalCollider->SetupAttachment(AIGoal);

	TopCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("TopCollider"));
	TopCollider->SetupAttachment(TopWall);

	BottomCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomCollider"));
	BottomCollider->SetupAttachment(BottomWall);

	PlayerGoalCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerGoalCollider"));
	PlayerGoalCollider->SetupAttachment(PlayerGoal);
}

// Called when the game starts or when spawned
void AABoundary::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AABoundary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Setup Collision/Delegate functionality
void AABoundary::PostInitializeComponents() {
	Super::PostInitializeComponents();

	// Collision Functionality Set Up
	AIGoalCollider->OnComponentBeginOverlap.AddDynamic(this, &AABoundary::OnOverlapBegin);
	TopCollider->OnComponentBeginOverlap.AddDynamic(this, &AABoundary::OnOverlapBegin);
	BottomCollider->OnComponentBeginOverlap.AddDynamic(this, &AABoundary::OnOverlapBegin);
	PlayerGoalCollider->OnComponentBeginOverlap.AddDynamic(this, &AABoundary::OnOverlapBegin);
}

// Handles Collision overlap for each separate component (Walls, AIGoal, PlayerGoal)
void AABoundary::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult) {

	APongPlayer* PlayerActor = Cast<APongPlayer>(OtherActor);
	if (HitComp == PlayerGoalCollider) {
		OnPlayerGoalCollision.Broadcast();
	}
	else if (HitComp == AIGoalCollider) {
		OnAIGoalCollision.Broadcast();
	}
	else if ((HitComp == TopCollider || HitComp == BottomCollider) && PlayerActor == nullptr) {
		OnWallCollision.Broadcast();
	}
}
