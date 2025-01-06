#include "Asset/StandardHeadShapeAsset_Factory.h"
#include "StandardShape/StandardHeadShape.h"

UStandardHeadShapeAsset_Factory::UStandardHeadShapeAsset_Factory()
{
	SupportedClass = UStandardHeadShape::StaticClass();
	bCreateNew = true;
}

UObject* UStandardHeadShapeAsset_Factory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UStandardHeadShape>(InParent, Class, Name, Flags, Context);
}



