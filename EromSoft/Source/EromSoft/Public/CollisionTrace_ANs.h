// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Animation/AnimNotifies/AnimNotifyState.h>
#include "CollisionTrace_ANs.generated.h"

/**
 * 
 */
UCLASS()
class EROMSOFT_API UCollisionTrace_ANs : public UAnimNotifyState
{
	GENERATED_BODY()
	
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
