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

	//<< HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 maxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AddedHealthPoint;
	//>>

	//<< MP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 maxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AddedManaPoint;
	//>>

	//<< SP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 maxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AddedStaminaPoint;
	//>>
	
	// 이후 공격력 계산에 사용될 예정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 strength;

	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 endurance;
};