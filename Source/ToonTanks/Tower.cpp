// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{
}

//Begin Play
void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);

}

//tick function
void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Find the distance to the Tank

    if(InFireRange())
    {
         RotateTorret(Tank->GetActorLocation());
    }

}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();

    Destroy();
}

void ATower::CheckFireCondition()
{
    if(InFireRange())
    {
         Fire();
    }
         
}

bool ATower::InFireRange()
{
     if(Tank)
     {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        //Check to see if the tank is in range
        if(Distance <= TargetLength)
        {
           return true;
        }
     }
    return false;
}
