// Available for free use - Original Author Joseph Miller

#pragma once

#include "CoreMinimal.h"
#include "Brick.h"
#include "GameFramework/Actor.h"
#include "BrickSpawner.generated.h"

UCLASS()
class TUTORIAL_PROJECT_API ABrickSpawner : public AActor
{
	GENERATED_BODY()

	// Defualt Scene Root
	UPROPERTY(VisibleAnywhere, Category = Component);
	class USceneComponent* DefaultSceneRoot;

	// Area to Spawn ABrick Blueprint Classes
	UPROPERTY(VisibleAnywhere, Category = Component);
	class UBoxComponent* SpawnArea;

	FVector Origin;
	FVector Extent;

	FTimerHandle TimerHandle;

public:	
	// Sets default values for this actor's properties
	ABrickSpawner();

	// Reference to Blueprint class
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABrick> ToSpawn;

	// Function to Spawn ABrick in level
	UFUNCTION(BlueprintCallable)
		void SpawnBrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
