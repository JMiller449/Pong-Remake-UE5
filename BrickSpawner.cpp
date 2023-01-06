// Available for free use - Original Author Joseph Miller


#include "BrickSpawner.h"
#include "Brick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABrickSpawner::ABrickSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating Components
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyCollider"));
	SpawnArea->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void ABrickSpawner::BeginPlay()
{
	Super::BeginPlay();

	float SphereRadius;

	UKismetSystemLibrary::GetComponentBounds(SpawnArea, Origin, Extent, SphereRadius);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABrickSpawner::SpawnBrick, 5.0f, true, 2.0f);
}

// Called every frame
void ABrickSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called once every 5 seconds
void ABrickSpawner::SpawnBrick() {
	if (ToSpawn) {
		float RandX = FMath::FRandRange(Origin.X - Extent.X, Origin.X + Extent.X);
		float RandY = FMath::FRandRange(Origin.Y - Extent.Y, Origin.Y + Extent.Y);
		float ValueZ = this->GetActorLocation().Z;
		FVector Location = FVector(RandX, RandY, ValueZ);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		GetWorld()->SpawnActor<ABrick>(ToSpawn, Location, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
	}
}