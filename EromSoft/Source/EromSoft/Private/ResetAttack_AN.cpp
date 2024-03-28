// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetAttack_AN.h"
#include "Combat_Interface.h"

void UResetAttack_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto checkValid = Cast<ICombat_Interface>(MeshComp->GetOwner());
	if (checkValid != nullptr)
	{
		checkValid->ResetAttack();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UResetAttack_AN::Notify - NullptrErr"));
	}
}
