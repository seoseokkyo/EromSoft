// Fill out your copyright notice in the Description page of Project Settings.


#include "ContinueAttack_AN.h"
#include "Combat_Interface.h"

void UContinueAttack_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Cast<ICombat_Interface>(MeshComp->GetOwner())->ContinueAttack();
}
