// Fill out your copyright notice in the Description page of Project Settings.


#include "Though_Sword.h"

AThough_Sword::AThough_Sword()
{
	handSocketName = FName("WeaponSocket");
	AttachSocketName = FName("SwordHipAttachSocket");
	eWeaponType = E_WeaponType::LightSword;
	weaponDamage = 20;

	ConstructorHelpers::FObjectFinder<UStaticMesh> loadStaticMesh(TEXT("/Game/CombatSyetem/CourseFile/Meshes/Weapons/Sword_SM.Sword_SM"));
	ItemStaticMesh->SetStaticMesh(loadStaticMesh.Object);

	ConstructorHelpers::FObjectFinder<UMaterial> loadMaterial(TEXT("/Engine/MaterialTemplates/PerfTricks/M_ContrastUsingLerp.M_ContrastUsingLerp"));
	ItemStaticMesh->GetStaticMesh()->SetMaterial(0, loadMaterial.Object);

	ConstructorHelpers::FObjectFinder<UAnimMontage> loadEnterCombatMontage(TEXT("/Game/CombatSyetem/CourseFile/Animations/LightSword/Equip/LightWeaponDraw_Anim_Montage.LightWeaponDraw_Anim_Montage"));
	enterCombatMontage = loadEnterCombatMontage.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> loadExitCombatMontage(TEXT("/Game/CombatSyetem/CourseFile/Animations/LightSword/Equip/LightWeaponDisarm_Anim_Montage.LightWeaponDisarm_Anim_Montage"));
	exitCombatMontage = loadExitCombatMontage.Object;

	attackMontages.Reset();
	attackMontages.Add(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("/Game/CombatSyetem/CourseFile/Animations/LightSword/LightAttack/LightAttack01_Montage.LightAttack01_Montage")).Object);

	attackMontages.Add(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("/Game/CombatSyetem/CourseFile/Animations/LightSword/LightAttack/LightAttack02_Montage.LightAttack02_Montage")).Object);

	attackMontages.Add(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("/Game/CombatSyetem/CourseFile/Animations/LightSword/LightAttack/LightAttack03_Montage.LightAttack03_Montage")).Object);

	dodgeMontages.Reset();
	dodgeMontages.Add(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("/Game/CombatSyetem/CourseFile/Animations/Dodge/Rolling_Montage.Rolling_Montage")).Object);
}
