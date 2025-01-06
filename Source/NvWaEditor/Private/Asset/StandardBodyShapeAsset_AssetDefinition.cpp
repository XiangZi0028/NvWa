#include "Asset/StandardBodyShapeAsset_AssetDefinition.h"
#include "StandardShape/StandardBodyShape.h"
TConstArrayView<FAssetCategoryPath> UStandardBodyShapeAsset_AssetDefinition::GetAssetCategories() const
{
	static const auto Categories = { FAssetCategoryPath(NSLOCTEXT("AssetTypeActions_NvWa", "Name", "女娲")) };
	return Categories;
}

TSoftClassPtr<UObject> UStandardBodyShapeAsset_AssetDefinition::GetAssetClass() const
{
	return UStandardBodyShape::StaticClass();
}

FText UStandardBodyShapeAsset_AssetDefinition::GetAssetDescription(const FAssetData& AssetData) const
{
	return FText::GetEmpty();
}

FText UStandardBodyShapeAsset_AssetDefinition::GetAssetDisplayName() const
{
	return FText::FromString(TEXT("身体标准"));
}

FLinearColor UStandardBodyShapeAsset_AssetDefinition::GetAssetColor() const
{
	// if ()
	// {
	// 	
	// }
	return FLinearColor::Yellow;
}



//方式2

FText FStandardBodyShapeTypeActions::GetName() const
{
	return INVTEXT("身体标准");
}

UClass* FStandardBodyShapeTypeActions::GetSupportedClass() const
{
	return UStandardBodyShape::StaticClass();
}

FColor FStandardBodyShapeTypeActions::GetTypeColor() const
{
	return FColor::Purple;
}

uint32 FStandardBodyShapeTypeActions::GetCategories()
{
	return FAssetToolsModule::GetModule().Get().FindAdvancedAssetCategory(FName(TEXT("NvWa")));
}

void FStandardBodyShapeTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	FAssetTypeActions_AnimationAsset::OpenAssetEditor(InObjects, EditWithinLevelEditor);
}

FText FStandardBodyShapeTypeActions::GetAssetDescription(const FAssetData& AssetData) const
{
	return FAssetTypeActions_AnimationAsset::GetAssetDescription(AssetData);
}

