#pragma once
#include "AnimationEditor.h"
#include "StandardShape/StandardShapeBase.h"
#include "StandardShapeEditor.generated.h"

UCLASS()
class UStandardShapeEditorSubSystem : public UEditorSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void OnOpenAssetEditor(UObject* InAsset, IAssetEditorInstance* AssetEditorInstance);
	void OnCloseAssetEditor(UObject* Asset, EAssetEditorCloseReason CloseReason);
	static UStandardShapeEditorSubSystem* Get();
	// void RegisterEditor(UStandardShapeBase* InStandardShapeBaseAsset, IAssetEditorInstance* InEditor);
	// void UnRegisterEditor(UStandardShapeBase* InStandardShapeBaseAsset);
	void HandleSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo, UStandardShapeBase* InStandardAsset);
private:
	TArray<TSharedPtr<ISkeletonTreeItem>> CachedTreeBoneItem;
};
