// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachWeaponActor_AN.h"
#include "Combat_Interface.h"

void UAttachWeaponActor_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Cast<ICombat_Interface>(MeshComp->GetOwner())->ResetCombat();
}
