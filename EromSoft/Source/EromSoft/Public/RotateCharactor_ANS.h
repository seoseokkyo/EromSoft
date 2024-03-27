// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Animation/AnimNotifies/AnimNotifyState.h>
#include "RotateCharactor_ANS.generated.h"

/**
 * 
 */
UCLASS()
class EROMSOFT_API URotateCharactor_ANS : public UAnimNotifyState
{
	GENERATED_BODY()
	
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
};
