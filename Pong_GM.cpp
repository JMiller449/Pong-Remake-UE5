// Fill out your copyright notice in the Description page of Project Settings.


#include "Pong_GM.h"
#include "ABoundary.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

void APong_GM::BeginPlay() {
	Super::BeginPlay();

	if (!ScoreBoardUI) {
		ScoreBoardUI = CreateWidget<UScoreBoard_UI>(GetWorld(), WidgetArray);
	}
	ScoreBoardUI->AddToViewport();
}

void APong_GM::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APong_GM::UpdatePlayerScore() {
	UE_LOG(LogTemp, Warning, TEXT("PlayerScored"))
	if (ScoreBoardUI) {
		ScoreBoardUI->PlayerScored();
	}
}

void APong_GM::UpdateAIScore() {
	UE_LOG(LogTemp, Warning, TEXT("AIScored"))
	if (ScoreBoardUI) {
		ScoreBoardUI->AIScored();
	}
}

UScoreBoard_UI* APong_GM::GetScoreBoard() {
	return ScoreBoardUI;
}