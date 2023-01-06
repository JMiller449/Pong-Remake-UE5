// Fill out your copyright notice in the Description page of Project Settings.


#include "PongAI.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "PongBall.h"
#include "VectorTypes.h"

// Sets default values
APongAI::APongAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates Components
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(DefaultSceneRoot);

	BodyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyCollider"));
	BodyCollider->SetupAttachment(Body);

	// Sets initial AI navigation values
	bFoundBall = false;
	Ball = nullptr;

	CurrYSearchValue = InitYSearchValue;
}

// Called when the game starts or when spawned
void APongAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame (handles AI decision making)
void APongAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bFoundBall) {
		APongAI::Move();
	}
	else {
		APongAI::FindBall();
	}
}

// Subscribes to necessary delegates (handles collision detection)
void APongAI::PostInitializeComponents() {
	Super::PostInitializeComponents();

	// Collision Functionality Set Up
	BodyCollider->OnComponentBeginOverlap.AddDynamic(this, &APongAI::OnOverlapBegin);
}

// Handles AI movement
void APongAI::Move()
{
	TArray<UStaticMeshComponent*> BallMesh;
	Ball->GetComponents<UStaticMeshComponent>(BallMesh);

	FVector3d BallLocation = BallMesh[0]->GetComponentLocation();
	FVector3d BodyLocation = Body->GetComponentLocation();

	float Difference = BallLocation.Y - BodyLocation.Y;
	if (UKismetMathLibrary::Abs(Difference) > 50.0f) {
		float dir = -1.0f;
		if (BallLocation.Y > BodyLocation.Y + 50) {
			dir = 1.0f;
		}
		if (CurrDistance + dir * 10.0f >= -800 && CurrDistance + dir * 10.0f <= 700) {
			CurrDistance += dir * 10.0f;
			FVector OffsetVector(0.0f, dir * 10.0f, 0.0f);

			Body->AddLocalOffset(OffsetVector);
		}
	}
}

// Uses a line trace to find and remember the location of the APongBall in the level
void APongAI::FindBall()
{
	FVector3d SpawnLocation = DefaultSceneRoot->GetComponentLocation();

	FVector StartLocation(SpawnLocation.X - 200, SpawnLocation.Y, SpawnLocation.Z);
	FVector* StartLocPtr = &StartLocation;

	FVector EndLocation(0.0f, CurrYSearchValue, SpawnLocation.Z);
	FVector* EndLocPtr = &EndLocation;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult Hit;

	if (GetWorld()->LineTraceSingleByChannel(Hit, *StartLocPtr, *EndLocPtr, ECC_Visibility, QueryParams)) {
		Ball = Cast<APongBall>(Hit.GetActor());
		if (Ball != nullptr) {
			bFoundBall = true;
			return;
		}
	}

	CurrYSearchValue += 5.0f;
	if (CurrYSearchValue > InitYSearchValue + 2000) {
		CurrYSearchValue = InitYSearchValue;
	}
}

// Handles updating the movement of the APongBall on collision
void APongAI::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	APongBall* CollidedBall = Cast<APongBall>(OtherActor);
	if (CollidedBall != nullptr) {
		FVector OtherCompLoc = OtherComp->GetComponentLocation();
		FVector BodyLoc = Body->GetComponentLocation();

		FVector NewDirection = UKismetMathLibrary::GetDirectionUnitVector(BodyLoc, OtherCompLoc);

		CollidedBall->PublicPawnCollision(NewDirection);
	}
}

