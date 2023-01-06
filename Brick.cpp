// Available for free use - Original Author Joseph Miller


#include "Brick.h"
#include "BrickSpawner.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "PongBall.h"
#include "VectorTypes.h"

// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating Components
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(DefaultSceneRoot);

	BodyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyCollider"));
	BodyCollider->SetupAttachment(Body);
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();
}

// Called to subscribe/Bind to Delegates
void ABrick::PostInitializeComponents() {
	Super::PostInitializeComponents();

	// Collision Functionality Set Up
	BodyCollider->OnComponentBeginOverlap.AddDynamic(this, &ABrick::OnOverlapBegin);
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called on overlap with BodyCollider Component
void ABrick::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult) {
	APongBall* CollidedBall = Cast<APongBall>(OtherActor); // reference to APongBall object
	
	// Updates Ball movement
	if (CollidedBall != nullptr) {
		FVector OtherCompLoc = OtherComp->GetComponentLocation();
		FVector BodyLoc = Body->GetComponentLocation();

		FVector NewDirection = UKismetMathLibrary::GetDirectionUnitVector(BodyLoc, OtherCompLoc);

		CollidedBall->PublicPawnCollision(NewDirection);
		this->Destroy();
	}
}

