// Fill out your copyright notice in the Description page of Project Settings.


#include "ContinueAttack_AN.h"
#include "Combat_Interface.h"

void UContinueAttack_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto checkValid = Cast<ICombat_Interface>(MeshComp->GetOwner());
	if (checkValid != nullptr)
	{
		checkValid->ContinueAttack();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UContinueAttack_AN::Notify - NullptrErr"));
	}
}
