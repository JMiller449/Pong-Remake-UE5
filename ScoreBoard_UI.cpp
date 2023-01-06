// Available for free use - Original Author Joseph Miller


#include "ScoreBoard_UI.h"
#include "ABoundary.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

// Sets up defualt variable values
void UScoreBoard_UI::NativeConstruct()
{
	Super::NativeConstruct();

	if (AIScore) {
		AIScore->SetText(FText::FromString(TEXT("0")));
	}
	AIScoreNum = 0.0f;
	if (PlayerScore) {
		PlayerScore->SetText(FText::FromString(TEXT("0")));
	}
	PlayerScoreNum = 0.0f;
}

// Called on AI Score
void UScoreBoard_UI::AIScored() {
	AIScoreNum += 1.0f;
	if (AIScore) {
		AIScore->SetText(FText::AsNumber(AIScoreNum));
	}

	if (AIScoreNum >= 10.0f) {
		UE_LOG(LogTemp, Warning, TEXT("%f"), AIScoreNum);
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}

// Called on Player Score
void UScoreBoard_UI::PlayerScored() {
	PlayerScoreNum += 1.0f;
	if (AIScore) {
		PlayerScore->SetText(FText::AsNumber(PlayerScoreNum));
	}

	if (PlayerScoreNum >= 10.0f) {
		UE_LOG(LogTemp, Warning, TEXT("%f"), PlayerScoreNum);
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}
