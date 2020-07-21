// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#define OUT

// Sets default values
APawnTank::APawnTank()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());


}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Turn();
	Move();

	if(PlayerControllerRef)
	{
		FVector HitLocation = MouseHitLocation(PlayerControllerRef);

		RotateTurret(HitLocation);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateTurnInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
	//PlayerInputComponent->BindAxis("RotateTurret", this, &APawnTank::CalculateMoveInput);
}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateTurnInput(float Value)
{
	float TurnAmount = Value * TurnSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0.f, TurnAmount, 0.f);
	TurnDirection = FQuat(Rotation);
}

void APawnTank::Move() 
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Turn() 
{
	AddActorLocalRotation(TurnDirection, true);
}

void APawnTank::HandleDestruction() 
{
	Super::HandleDestruction();
	//Destroy();
	//TODO: HIDE player 
}