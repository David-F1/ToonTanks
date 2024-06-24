// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()


	public:

		ATower();

		// Called every frame
		virtual void Tick(float DeltaTime) override;
	
	protected:
		// 
		virtual void BeginPlay();

	private:
		class ATank* Tank;

		UPROPERTY(EditAnywhere, Category = "Combat")
		float TargetLength = 300;

		FTimerHandle FireRateTimerHandle;
		float FireRate = 2.f;
		void CheckFireCondition();

		bool InFireRange();

};
