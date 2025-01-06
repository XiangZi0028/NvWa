#pragma once
#include "AnimationEditor.h"
#include "StandardShape/StandardShapeBase.h"
#include "StandardShapeEditor.generated.h"

UCLASS()
class UStandardShapeEditorSubSystem : public UEditorSubsystem
{
	GENERATED_BODY()
public:
	static UStandardShapeEditorSubSystem* Get();
	void RegisterEditor(UStandardShapeBase* InStandardShapeBaseAsset, IAssetEditorInstance* InEditor);
	void UnRegisterEditor(UStandardShapeBase* InStandardShapeBaseAsset);
	IAssetEditorInstance* FindInStandardShapeBaseAssetEditor(UStandardShapeBase* InStandardShapeBaseAsset);
	void HandleSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo);
private:
	TMap<UStandardShapeBase*, IAssetEditorInstance*> StandardEditorMap;
};
