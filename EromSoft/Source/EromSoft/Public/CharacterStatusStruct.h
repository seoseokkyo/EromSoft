// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStatusStruct.generated.h"
/**
 * 
 */

class EROMSOFT_API CharacterStatusStruct
{
public:
	CharacterStatusStruct();
	~CharacterStatusStruct();
};

USTRUCT(Atomic, BluePrintType)
struct FCharacterStat
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 maxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AddedHealthPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 maxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AddedStaminaPoint;

	// 이후 공격력 계산에 사용될 예정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 strength;

	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 endurance;
};