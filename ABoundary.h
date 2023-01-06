// Available for free use - Original Author Joseph Miller

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABoundary.generated.h"

// Declaring Collision handling delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWallCollisionSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAIGoalCollisionSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerGoalCollisionSignature);

UCLASS()
class TUTORIAL_PROJECT_API AABoundary : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABoundary();

	// Defualt Scene Root
	UPROPERTY(VisibleAnywhere, Category = Component);
	class USceneComponent* DefaultSceneRoot;

	// Boundary Mesh
	UPROPERTY(EditAnywhere, Category = Component);
	class UStaticMeshComponent* AIGoal;

	UPROPERTY(EditAnywhere, Category = Component);
	class UStaticMeshComponent* TopWall;

	UPROPERTY(EditAnywhere, Category = Component);
	class UStaticMeshComponent* BottomWall;

	UPROPERTY(EditAnywhere, Category = Component);
	class UStaticMeshComponent* PlayerGoal;

	// Collision Boxes
	UPROPERTY(EditAnywhere, Category = Component);
	class UBoxComponent* AIGoalCollider;

	UPROPERTY(EditAnywhere, Category = Component);
	class UBoxComponent* TopCollider;

	UPROPERTY(EditAnywhere, Category = Component);
	class UBoxComponent* BottomCollider;

	UPROPERTY(EditAnywhere, Category = Component);
	class UBoxComponent* PlayerGoalCollider;

	// Overlap Function
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* HitComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Delegates
	UPROPERTY(BlueprintAssignable);
		FOnWallCollisionSignature OnWallCollision;

	UPROPERTY(BlueprintAssignable);
		FOnAIGoalCollisionSignature OnAIGoalCollision;

	UPROPERTY(BluePrintAssignable);
		FOnPlayerGoalCollisionSignature OnPlayerGoalCollision;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//For add dynamic collisions
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
