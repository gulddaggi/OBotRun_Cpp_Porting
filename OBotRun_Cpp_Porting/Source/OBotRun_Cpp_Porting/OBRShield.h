// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OBotRun_Cpp_Porting.h"
#include "GameFramework/Actor.h"
#include "OBRShield.generated.h"

UCLASS()
class OBOTRUN_CPP_PORTING_API AOBRShield : public AActor
{
	GENERATED_BODY()
	
public:	
	AOBRShield();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* Mesh;

private:
	UFUNCTION()
	void OnShieldBeginoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
