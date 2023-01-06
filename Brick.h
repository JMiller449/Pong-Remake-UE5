// Available for free use - Original Author Joseph Miller

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"

UCLASS()
class TUTORIAL_PROJECT_API ABrick : public AActor
{
	GENERATED_BODY()

	// Defualt Scene Root
	UPROPERTY(VisibleAnywhere, Category = Component);
	class USceneComponent* DefaultSceneRoot;
	
	// Visible Brick
	UPROPERTY(VisibleAnywhere, Category = Component);
	class UStaticMeshComponent* Body;

	// Collider for Brick
	UPROPERTY(VisibleAnywhere, Category = Component);
	class UBoxComponent* BodyCollider;

	// Overlap Function
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* HitComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Sets default values for this actor's properties
	ABrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//For add dynamic collisions
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
