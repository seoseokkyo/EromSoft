// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetCombat_AN.h"
#include "Combat_Interface.h"

void UResetCombat_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (Cast<ICombat_Interface>(MeshComp->GetOwner()))
	{
		ICombat_Interface::Execute_ResetCombat(MeshComp->GetOwner());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UResetCombat_AN::Notify - NullptrErr"));
	}
	//auto checkValid = Cast<ICombat_Interface>(MeshComp->GetOwner());
	//if (checkValid != nullptr)
	//{
	//	checkValid->ResetCombat();
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("UResetCombat_AN::Notify - NullptrErr"));
	//}
}
