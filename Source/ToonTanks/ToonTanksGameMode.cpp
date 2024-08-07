// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"


void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();

}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    TankController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(TankController)
    {
        TankController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
                TankController, 
                &AToonTanksPlayerController::SetPlayerEnabledState, 
                true
            );

        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle, 
            PlayerEnableTimerDelegate, 
            StartDelay, 
            false
        );
    }
}


void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if(DeadActor == Tank)
    {

         Tank->HandleDestruction();
         if(TankController)
         {
            TankController->SetPlayerEnabledState(false);
         }
         GameOver(false);
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        --TargetTowers;
        if(TargetTowers == 0)
        {
            GameOver(true);
        }
    }
   
    
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> TowerArray;

    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TowerArray);
    return TowerArray.Num();
}
