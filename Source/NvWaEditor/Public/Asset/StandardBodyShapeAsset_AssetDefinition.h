#pragma once
#include "AssetDefinitionDefault.h"
#include "AssetTypeActions_Base.h"
#include "AssetTypeActions/AssetTypeActions_AnimationAsset.h"
#include "StandardBodyShapeAsset_AssetDefinition.generated.h"
UCLASS()
class NVWAEDITOR_API UStandardBodyShapeAsset_AssetDefinition : public UAssetDefinitionDefault
{
	GENERATED_BODY()
	
public:
	//~UAssetDefinition interface
	virtual FText GetAssetDisplayName() const override;
	virtual TSoftClassPtr<UObject> GetAssetClass() const override;
	virtual FLinearColor GetAssetColor() const override;
	virtual FText GetAssetDescription(const FAssetData& AssetData) const override;
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
	//~End of UAssetDefinition interface
};

//方式2

class FStandardBodyShapeTypeActions : public FAssetTypeActions_AnimationAsset
{
public:
public:
	/** Returns the name of this type */
	virtual FText GetName() const override;

	/** Get the supported class of this type. */
	virtual UClass* GetSupportedClass() const override;

	/** Returns the color associated with this type */
	virtual FColor GetTypeColor() const override;

	/** Returns the categories that this asset type appears in. The return value is one or more flags from EAssetTypeCategories.  */
	virtual uint32 GetCategories() override;

	/** Opens the asset editor for the specified objects. If EditWithinLevelEditor is valid, the world-centric editor will be used. */
	virtual void OpenAssetEditor( const TArray<UObject*>& InObjects,
		TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>() ) override;

	/** Returns additional tooltip information for the specified asset, if it has any (otherwise return the null widget) */
	virtual FText GetAssetDescription(const FAssetData& AssetData) const override;
};
