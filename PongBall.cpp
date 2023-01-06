// Fill out your copyright notice in the Description page of Project Settings.


#include "PongBall.h"
#include "Pong_GM.h"
#include "ScoreBoard_UI.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APongBall::APongBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(DefaultSceneRoot);

	Speed = 20.0f;
	Direction = FVector(-1.0f, 0.0f, 0.0f);

	ScoreBoardUI = nullptr;
} 

// Called when the game starts or when spawned
void APongBall::BeginPlay()
{
	Super::BeginPlay();


}

void APongBall::PostInitializeComponents() {
	Super::PostInitializeComponents();


	if (Boundary != nullptr) {
		Boundary->OnWallCollision.AddUniqueDynamic(this, &APongBall::OnWallCollision);
		Boundary->OnPlayerGoalCollision.AddUniqueDynamic(this, &APongBall::OnPlayerGoalCollision);
		Boundary->OnAIGoalCollision.AddUniqueDynamic(this, &APongBall::OnAIGoalCollision);
	}
}

// Called every frame
void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector SpeedVector(Speed, Speed, 0.0f);
	Sphere->AddWorldOffset(Direction * SpeedVector);
	ChangeInPos += Direction * SpeedVector;
}

void APongBall::OnPawnCollision(FVector NewDirection) {

	Direction = NewDirection;
}

void APongBall::PublicPawnCollision(FVector NewDirection) {
	this->OnPawnCollision(NewDirection);
}

void APongBall::OnWallCollision()
{
	Direction = FVector(Direction.X, Direction.Y * -1.0f, 0.0f);
}

void APongBall::OnPlayerGoalCollision()
{
	FVector ToStartVector(ChangeInPos.X * -1.0f, ChangeInPos.Y * -1.0f, 0.0f);
	Sphere->AddLocalOffset(ToStartVector);
	ChangeInPos = FVector(0.0f, 0.0f, 0.0f);

	float random = UKismetMathLibrary::RandomFloat();
	if (random < 0.3f) {
		random = 0.3f;
	}
	else if (random > 0.7f) {
		random = 0.7f;
	}

	float sign = 1.0f;
	if (UKismetMathLibrary::RandomBool()) {
		sign = -1.0f;
	}

	Direction = FVector(random * -1.0f, (1.0f - random) * sign, 0.0f);

	if (!ScoreBoardUI) {
		this->GetScoreBoard();
	}
	ScoreBoardUI->AIScored();
}

void APongBall::OnAIGoalCollision()
{
	FVector ToStartVector(ChangeInPos.X * -1.0f, ChangeInPos.Y * -1.0f, 0.0f);
	Sphere->AddLocalOffset(ToStartVector);
	ChangeInPos = FVector(0.0f, 0.0f, 0.0f);

	float random = UKismetMathLibrary::RandomFloat();
	if (random < 0.3f) {
		random = 0.3f;
	}
	else if (random > 0.7f) {
		random = 0.7f;
	}

	float sign = 1.0f;
	if (UKismetMathLibrary::RandomBool()) {
		sign = -1.0f;
	}

	Direction = FVector(random * -1.0f, (1.0f - random) * sign, 0.0f);

	if (!ScoreBoardUI) {
		this->GetScoreBoard();
	}
	ScoreBoardUI->PlayerScored();
}

void APongBall::GetScoreBoard() {
		if (GetWorld()) {
				APong_GM* GameMode = (APong_GM*)GetWorld()->GetAuthGameMode();
			if (GameMode) {
					ScoreBoardUI = GameMode->GetScoreBoard();
			}
		}
}

