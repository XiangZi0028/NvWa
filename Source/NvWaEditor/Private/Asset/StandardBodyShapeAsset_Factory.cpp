#include "Asset/StandardBodyShapeAsset_Factory.h"

#include "StandardShape/StandardBodyShape.h"

UStandardBodyShapeAsset_Factory::UStandardBodyShapeAsset_Factory()
{
	SupportedClass = UStandardBodyShape::StaticClass();
	bCreateNew = true;
}

UObject* UStandardBodyShapeAsset_Factory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UStandardBodyShape>(InParent, Class, Name, Flags, Context);
}
