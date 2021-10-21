// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform ()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime) 
{
	
	Super::Tick(DeltaTime);
	if (HasAuthority() && ActiveTriggers >=1)
	{
		FVector Location = GetActorLocation();
		 
		FVector Direction = (GlobalTargetLocation -Location).GetSafeNormal();
		
		//UE_LOG(LogTemp, Warning, TEXT("Directionnormal =, %s "), *Direction.ToString());
		//UE_LOG(LogTemp, Error, TEXT("         "));

		Location += (Direction *MovementSpeed*DeltaTime);

		SetActorLocation(Location);
		
		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravelled = (Location - GlobalStartLocation).Size();

		if (JourneyTravelled >= JourneyLength)
		{
			FVector TempLocation = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = TempLocation;
			
			
		}
		SetActorLocation(Location);


		//UE_LOG(LogTemp, Warning, TEXT("dot product =, %s "), *Direction.ToString());
		
			

	}


	
}
void AMovingPlatform::addActiveTrigger()
{
	ActiveTriggers += 1;

}
void AMovingPlatform::removeActiveTrigger()
{
	ActiveTriggers -= 1;
	if (ActiveTriggers < 1) ActiveTriggers = 0;
}
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	GlobalStartLocation = GetActorLocation();
	
}