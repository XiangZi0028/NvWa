#pragma once
#include "Editor/StandardShapeEditor.h"

void UStandardShapeEditorSubSystem::RegisterEditor(UStandardShapeBase* InStandardShapeBaseAsset, IAssetEditorInstance* InEditor)
{
	StandardEditorMap.Add(InStandardShapeBaseAsset) = InEditor;
}

void UStandardShapeEditorSubSystem::UnRegisterEditor(UStandardShapeBase* InStandardShapeBaseAsset)
{
	StandardEditorMap.FindAndRemoveChecked(InStandardShapeBaseAsset);
}

IAssetEditorInstance* UStandardShapeEditorSubSystem::FindInStandardShapeBaseAssetEditor(UStandardShapeBase* InStandardShapeBaseAsset)
{
	if (const auto Editor = StandardEditorMap.Find(InStandardShapeBaseAsset))
	{
		return *Editor;
	}
	return nullptr;
}

UStandardShapeEditorSubSystem* UStandardShapeEditorSubSystem::Get()
{
	if (GEditor)
	{
		return GEditor->GetEditorSubsystem<UStandardShapeEditorSubSystem>();
	}
	return nullptr;	
}

void UStandardShapeEditorSubSystem::HandleSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo)
{
	
}
