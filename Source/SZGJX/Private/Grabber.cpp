// Design by Michael Bridges.  Implementation by Tristan Brumagin.


#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Set up Components
	_physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (_physicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s grabber could not find associated physics handle"), *GetOwner()->GetName());
		PrimaryComponentTick.bCanEverTick = false;
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (_physicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s grabber could not find associated input component"), *GetOwner()->GetName());
		PrimaryComponentTick.bCanEverTick = false;
	}
	else {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	
	// Initialize Player View info
	UpdateLocalViewInfo();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_physicsHandle->GrabbedComponent) {
		UpdateLocalViewInfo();
		_physicsHandle->SetTargetLocation(_lineTraceEnd);
	}
	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Log, TEXT("Grabber Pressed"));

	FHitResult hit = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = hit.GetComponent();

	if (hit.GetActor() != nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Grabber found %s"), *hit.GetActor()-> GetName());
		_physicsHandle->GrabComponentAtLocation(
			ComponentToGrab
			, NAME_None
			, _lineTraceEnd
		);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Log, TEXT("Grabber Released"));

	if (_physicsHandle->GrabbedComponent) {
		_physicsHandle->ReleaseComponent();
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
	UpdateLocalViewInfo();
	DrawDebugLine(GetWorld(), _playerViewLocation, _lineTraceEnd, FColor::Green, false, -1.0f, (uint8)'\000', 5.0f);

	FHitResult hitResult;
	FCollisionQueryParams TraceParams(TEXT(""), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT hitResult, _playerViewLocation, _lineTraceEnd
		, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)
		, TraceParams
	);
	return hitResult;
}

void UGrabber::UpdateLocalViewInfo() {
	// Get player's viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT _playerViewLocation, OUT _playerViewRotation);
	_lineTraceEnd = _playerViewLocation + _playerViewRotation.Vector() * _reach;
}