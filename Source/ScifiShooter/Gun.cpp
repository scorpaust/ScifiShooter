// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootInstance = CreateDefaultSubobject<USceneComponent>(TEXT("Root Instance"));

	RootComponent = RootInstance;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	Mesh->SetupAttachment(RootComponent);

	MaxRange = 2000.f;

	Damage = 20.f;

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger() {

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;

	FVector ShotDirection;

	bool bSuccess = GunTrace(Hit, ShotDirection);

	if (bSuccess && GetOwnerController() != nullptr) {

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFx, Hit.Location, ShotDirection.Rotation());

		FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);

		if (!ensure(Hit.GetActor() != nullptr)) return;

		Hit.GetActor()->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
	}

}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection) {

	FVector Location;

	FRotator Rotation;

	if (GetOwnerController() == nullptr) return false;

	GetOwnerController()->GetPlayerViewPoint(Location, Rotation);

	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);

	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

}

AController* AGun::GetOwnerController() const {

	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();	

}

