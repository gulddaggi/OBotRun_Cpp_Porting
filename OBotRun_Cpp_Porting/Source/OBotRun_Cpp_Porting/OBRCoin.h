// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "GameFramework/Actor.h"
#include "OBRCoin.generated.h"

UCLASS()
class OBOTRUN_CPP_PORTING_API AOBRCoin : public AActor
{
	GENERATED_BODY()
	
public:	
	AOBRCoin();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Mesh;

private:
	UFUNCTION()
	void OnCoinBeginoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	int CoinValue;
};
