#include "Asset/StandardHeadShapeAsset_AssetDefinition.h"
#include "SSkeletonTree.h"
#include "IPersonaToolkit.h"
#include "PersonaToolkit.h"
#include "Editor/StandardShapeEditor.h"
#include "StandardShape/StandardBodyShape.h"
#include "StandardShape/StandardHeadShape.h"

TConstArrayView<FAssetCategoryPath> UStandardHeadShapeAsset_AssetDefinition::GetAssetCategories() const
{
	static const auto Categories = { FAssetCategoryPath(NSLOCTEXT("AssetTypeActions_NvWa", "Name", "女娲")) };
	return Categories;
}

TSoftClassPtr<UObject> UStandardHeadShapeAsset_AssetDefinition::GetAssetClass() const
{
	return UStandardHeadShape::StaticClass();
}

FText UStandardHeadShapeAsset_AssetDefinition::GetAssetDescription(const FAssetData& AssetData) const
{
	return UAssetDefinitionDefault::GetAssetDescription(AssetData);
}

FText UStandardHeadShapeAsset_AssetDefinition::GetAssetDisplayName() const
{
	return FText::FromString(TEXT("头部标准"));
}

FLinearColor UStandardHeadShapeAsset_AssetDefinition::GetAssetColor() const
{
	// if ()
	// {
	// 	
	// }
	return FLinearColor::Red;
}


//方式2

FText FStandardHeadShapeTypeActions::GetName() const
{
	return INVTEXT("头部标准");
}

UClass* FStandardHeadShapeTypeActions::GetSupportedClass() const
{
	return UStandardHeadShape::StaticClass();
}

FColor FStandardHeadShapeTypeActions::GetTypeColor() const
{
	return FColor::Purple;
}

uint32 FStandardHeadShapeTypeActions::GetCategories()
{
	return FAssetToolsModule::GetModule().Get()
	.FindAdvancedAssetCategory(FName(TEXT("NvWa")));
}

void FStandardHeadShapeTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	for (const auto InObject : InObjects)
	{
		if (UStandardShapeBase* StandardShape = Cast<UStandardShapeBase>(InObject))
		{
			FAssetTypeActions_AnimationAsset::OpenAssetEditor(InObjects, EditWithinLevelEditor);

			// Find the anim editors that are doing it
			TArray<IAssetEditorInstance*> AssetEditors;
#if WITH_EDITOR
			AssetEditors = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorsForAsset(StandardShape);
#endif
			for (IAssetEditorInstance* ExistingEditor : AssetEditors)
			{
				if (ExistingEditor->GetEditorName() == FName("AnimationEditor"))
				{
					// Change the current anim to this one
					IAnimationEditor* AnimEditor = static_cast<IAnimationEditor*>(ExistingEditor);
					UStandardShapeEditorSubSystem::Get()->RegisterEditor(StandardShape, AnimEditor);
					const auto AnimationEditor = static_cast<FAnimationEditor*>(AnimEditor);
					TSharedRef<ISkeletonTree> SkeletonTree = AnimationEditor->GetSkeletonTree();
					const TSharedRef<SSkeletonTree> Tree = StaticCastSharedRef<SSkeletonTree>(SkeletonTree);
					TSharedRef<FPersonaToolkit> PersonaToolkit = StaticCastSharedRef<FPersonaToolkit>(AnimationEditor->GetPersonaToolkit());
					//Tree->RegisterOnSelectionChanged(FOnSkeletonTreeSelectionChanged::CreateUObject(UStandardShapeEditorSubSystem::Get(), &UStandardShapeEditorSubSystem::HandleSelectionChanged));
					Tree->GetSelectedItems()
					// Tree->Refresh()
					// if(AnimEditor->GetPersonaToolkit()->GetSkeleton() == AnimAsset->GetSkeleton())
					// {
					// 	AnimEditor->SetAnimationAsset(AnimAsset);
					// 	AnimEditor->FocusWindow();
					// 	bFoundEditor = true;
					// 	break;
					// }
				}
			}
		}
	}
}

FText FStandardHeadShapeTypeActions::GetAssetDescription(const FAssetData& AssetData) const
{
	return FAssetTypeActions_AnimationAsset::GetAssetDescription(AssetData);
}



