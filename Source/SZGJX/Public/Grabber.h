// Design by Michael Bridges.  Implementation by Tristan Brumagin.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float _reach = 100.0f;

	UPROPERTY(EditAnywhere)
		float _strength = 50.0f;


	UPhysicsHandleComponent* _physicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	FVector _playerViewLocation;
	FRotator _playerViewRotation;
	FVector _lineTraceEnd;

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Grab();
	void Release();
	FHitResult GetFirstPhysicsBodyInReach();
	void UpdateLocalViewInfo();

private:
};
