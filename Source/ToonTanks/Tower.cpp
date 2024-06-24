// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
}
void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

}



void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Find the distance to the Tank
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        //Check to see if the tank is in range
        if(Distance <= TargetLength)
        {
            //if in range, rotate turret toward Tank.
            RotateTorret(Tank->GetActorLocation());
        }
        
    }




}


