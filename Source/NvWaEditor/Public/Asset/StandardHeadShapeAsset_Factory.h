// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "StandardHeadShapeAsset_Factory.generated.h"

UCLASS()
class NVWAEDITOR_API UStandardHeadShapeAsset_Factory : public UFactory
{
	GENERATED_BODY()

public:

	UStandardHeadShapeAsset_Factory();
	
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
