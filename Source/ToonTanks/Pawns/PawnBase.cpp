// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);


	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}


void APawnBase::RotateTurret(FVector LookAtTarget) 
{
	// This current Pawns location vector
	FVector StartLocation = TurretMesh->GetComponentLocation();

	// Get our X, Y of our target at the same height as this Pawn
	FVector LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, StartLocation.Z);

	// To find our rotation we need to find the difference between our target and current location
	FRotator TurretRotation = FVector( LookAtTargetClean - StartLocation ).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}


void APawnBase::Fire() 
{

	if (ProjectileClass) 
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		
		TempProjectile->SetOwner(this);
	}
}


void APawnBase::HandleDestruction() 
{
	// Play hit animations
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
}


FVector APawnBase::MouseHitLocation(APlayerController* PlayerControllerRef) 
{
	FHitResult TraceHitResult;
	PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, OUT TraceHitResult);
	return TraceHitResult.ImpactPoint;
}
