// Available for free use - Original Author Joseph Miller


#include "PongPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "PongBall.h"
#include "VectorTypes.h"

// Sets default values
APongPlayer::APongPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating Components
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(DefaultSceneRoot);
	Camera->SetWorldLocation(FVector(1800.0f, 0.0f, 2000.0f));
	FRotator CamRot(Camera->GetComponentRotation().Pitch + 90.0f, Camera->GetComponentRotation().Yaw, 0.0);
	Camera->AddLocalRotation(CamRot);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(DefaultSceneRoot);

	BodyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyCollider"));
	BodyCollider->SetupAttachment(Body);

	// Default movement values
	bMoveUp = false;
	bMoveDown = false;
}

// Called when the game starts or when spawned
void APongPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Set up Collision handling
void APongPlayer::PostInitializeComponents() {
	Super::PostInitializeComponents();
	
	// Collision Functionality Set Up
	BodyCollider->OnComponentBeginOverlap.AddDynamic(this, &APongPlayer::OnOverlapBegin);
}

// Called every frame
void APongPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Moves PlayerMesh if keys are pressed
	if (bMoveUp) {
		FVector OffsetVector(0.0f, 1.0f * 10.0f, 0.0f);

		Body->AddLocalOffset(OffsetVector);
	}

	if (bMoveDown) {
		FVector OffsetVector(0.0f, -1.0f * 10.0f, 0.0f);

		Body->AddLocalOffset(OffsetVector);
	}
}

// Called to bind functionality to input
void APongPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Up", IE_Pressed, this, &APongPlayer::MoveUp);
	PlayerInputComponent->BindAction("Down", IE_Pressed, this, &APongPlayer::MoveDown);
	PlayerInputComponent->BindAction("Up", IE_Released, this, &APongPlayer::StopUp);
	PlayerInputComponent->BindAction("Down", IE_Released, this, &APongPlayer::StopDown);
}

// Updates APongBall movement on collision and prevents player from moving past AABoundary
void APongPlayer::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult) {
	APongBall* CollidedBall = Cast<APongBall>(OtherActor);
	if (CollidedBall != nullptr) {
		FVector OtherCompLoc = OtherComp->GetComponentLocation();
		FVector BodyLoc = Body->GetComponentLocation();

		FVector NewDirection = UKismetMathLibrary::GetDirectionUnitVector(BodyLoc, OtherCompLoc);

		CollidedBall->PublicPawnCollision(NewDirection);
	}
	else if (bMoveUp) {
		bMoveUp = false;
		bCollideTop = true;
	}
	else if (bMoveDown) {
		bMoveDown = false;
		bCollideBot = true;
	}
}

// Triggered on Up arrow press, enables upwards movement
void APongPlayer::MoveUp() {
	if (!bCollideTop) {
		bMoveUp = true;
		if (bMoveDown) {
			bMoveDown = false;
		}
		if (bCollideBot) {
			bCollideBot = false;
		}
	}
}

// Triggered on Down arrow press, enables downwards movement
void APongPlayer::MoveDown() {
	if (!bCollideBot) {
		bMoveDown = true;
		if (bMoveUp) {
			bMoveUp = false;
		}
		if (bCollideTop) {
			bCollideTop = false;
		}
	}
}

// Triggered on Up arrow release, disables upwards movement
void APongPlayer::StopUp() {
	bMoveUp = false;
}

// Triggered on Down arrow release, disables downwards movement
void APongPlayer::StopDown() {
	bMoveDown = false;
}

