#include "NvWaEditor.h"

#include "Asset/StandardBodyShapeAsset_AssetDefinition.h"
#include "Asset/StandardHeadShapeAsset_AssetDefinition.h"

#define LOCTEXT_NAMESPACE "FNvWaEditorModule"

void FNvWaEditorModule::StartupModule()
{
	// RegisterTypeActions
	StandardHeadShapeTypeActions = MakeShared<FStandardHeadShapeTypeActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(StandardHeadShapeTypeActions.ToSharedRef());

	StandardBodyShapeTypeActions = MakeShared<FStandardBodyShapeTypeActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(StandardBodyShapeTypeActions.ToSharedRef());
	FAssetToolsModule::GetModule().Get().RegisterAdvancedAssetCategory(FName("NvWa"), FText::FromString(TEXT("女娲")));
}

void FNvWaEditorModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FNvWaEditorModule, NvWaEditor)