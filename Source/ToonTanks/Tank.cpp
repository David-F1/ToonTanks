// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


ATank::ATank()
{
    ArmLength = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    ArmLength->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(ArmLength);

}


// Called at begining of launch
void ATank::BeginPlay()
{
    		// Call the base class  
	Super::BeginPlay();

    		//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	PlayerControllerRef = Cast<APlayerController>(GetController());


}

// Called every frame
void ATank::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if(PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility, 
			false, 
			HitResult);

			DrawDebugSphere(GetWorld(), 
			HitResult.ImpactPoint, 
			25, 
			12, 
			FColor::Blue, 
			false);

		RotateTorret(HitResult.ImpactPoint);
	}

}



void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    //Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// MoveForward
		EnhancedInputComponent->BindAction(Forward, ETriggerEvent::Triggered, this, &ATank::Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::Turn);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
			
	}
}


void ATank::Move(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();

	FVector DeltaLocation(0.f);
	DeltaLocation.X = DirectionValue * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);

}

void ATank::Turn(const FInputActionValue &Value)
{
	const float DirectionValue = Value.Get<float>();

	//initialise delta rotator with (0, 0, 0).
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = DirectionValue * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);


}
