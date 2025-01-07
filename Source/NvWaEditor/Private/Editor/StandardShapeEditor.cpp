#pragma once
#include "Editor/StandardShapeEditor.h"
#include "SSkeletonTree.h"
#include "ISkeletonTree.h"
#include "SAdvancedTransformInputBox.h"
#include "SkeletonTreeBoneItem.h"
#include "Editor/AnimGraph/Public/AnimPreviewInstance.h"

static void AppendControlledBone(TArray<TSharedPtr<ISkeletonTreeItem>> ControlledBones)
{
	UStandardShapeBase* StandardShapeBase = nullptr;
	for (const auto InSelectedItem : ControlledBones)
	{
		if (UAnimationAsset* AnimationAsset = InSelectedItem->GetSkeletonTree()->GetPreviewScene()->GetPreviewAnimationAsset())
		{
			StandardShapeBase = Cast<UStandardShapeBase>(AnimationAsset);
		}
		if (!StandardShapeBase)
		{
			return;
		}
		TSharedPtr<FSkeletonTreeBoneItem> TreeBoneItem = StaticCastSharedPtr<FSkeletonTreeBoneItem>(InSelectedItem);
		if (!TreeBoneItem.IsValid()) continue;
		TObjectPtr<class UAnimPreviewInstance> AnimInstance = nullptr;
		if (const UDebugSkelMeshComponent* PreviewComponent = TreeBoneItem->GetSkeletonTree()->GetPreviewScene()->GetPreviewMeshComponent())
		{
			AnimInstance = PreviewComponent->PreviewInstance;
			if (UBoneProxy* BoneProxy = Cast<UBoneProxy>(TreeBoneItem->GetObject()))
			{
				if (FAnimNode_ModifyBone* ModifiedBone = AnimInstance->FindModifiedBone(BoneProxy->BoneName))
				{
					// AnimInstance->FindModifiedBone(BoneProxy->BoneName);
					FTransform Transform;
					Transform.SetLocation(ModifiedBone->Translation);
					Transform.SetRotation(ModifiedBone->Rotation.Quaternion());
					Transform.SetScale3D(ModifiedBone->Scale);
					FControlledBoneEntry BoneEntry;
					BoneEntry.Name = BoneProxy->BoneName;
					BoneEntry.Index = PreviewComponent->GetBoneIndex(BoneProxy->BoneName);
					BoneEntry.Transform = Transform;
					StandardShapeBase->AppendControlledBoneEntries(BoneEntry);
					BoneProxy->ResetToDefault(ESlateTransformComponent::Type::Max , UBoneProxy::ETransformType::TransformType_Bone);
					BoneProxy->Location = FVector(0);
					BoneProxy->Rotation = FRotator(0);
					BoneProxy->Scale = FVector(1);
					BoneProxy->PreviousLocation = FVector(0);
					BoneProxy->PreviousRotation = FRotator(0);
					BoneProxy->PreviousScale = FVector(1);
					AnimInstance->RemoveBoneModification(BoneProxy->BoneName);
				}
			}
		}
	}
}
void UStandardShapeEditorSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OnAssetOpenedInEditor().AddUObject(this, &UStandardShapeEditorSubSystem::OnOpenAssetEditor);
	GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OnAssetEditorRequestClose().AddUObject(this, &UStandardShapeEditorSubSystem::OnCloseAssetEditor);
}

void UStandardShapeEditorSubSystem::OnCloseAssetEditor(UObject* InAsset, EAssetEditorCloseReason CloseReason)
{
	if (UStandardShapeBase* StandardShapeAsset = Cast<UStandardShapeBase>(InAsset))
	{
		AppendControlledBone(CachedTreeBoneItem);
	}
}

void UStandardShapeEditorSubSystem::OnOpenAssetEditor(UObject* InAsset, IAssetEditorInstance* AssetEditorInstance)
{
	if (UStandardShapeBase* StandardShapeAsset = Cast<UStandardShapeBase>(InAsset))
	{
		 IAnimationEditor* AnimEditor = static_cast<IAnimationEditor*>(AssetEditorInstance);
		 const auto AnimationEditor = static_cast<FAnimationEditor*>(AnimEditor);
		 TSharedRef<ISkeletonTree> SkeletonTree = AnimationEditor->GetSkeletonTree();
		 const TSharedRef<SSkeletonTree> Tree = StaticCastSharedRef<SSkeletonTree>(SkeletonTree);
		 // TSharedRef<FPersonaToolkit> PersonaToolkit = StaticCastSharedRef<FPersonaToolkit>(AnimationEditor->GetPersonaToolkit());
		Tree->RegisterOnSelectionChanged(FOnSkeletonTreeSelectionChanged::CreateUObject(UStandardShapeEditorSubSystem::Get(), &UStandardShapeEditorSubSystem::HandleSelectionChanged, StandardShapeAsset));
	}
}

UStandardShapeEditorSubSystem* UStandardShapeEditorSubSystem::Get()
{
	if (GEditor)
	{
		return GEditor->GetEditorSubsystem<UStandardShapeEditorSubSystem>();
	}
	return nullptr;	
}


/*
 * 选中的Section发生变化时
 * 1。缓存数据
 * 2.清空代理数据(刷新Tree)
 * 3.HandleSelectionChanged一般清空下会调用两次：取消和选中
 */


void UStandardShapeEditorSubSystem::HandleSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo, UStandardShapeBase* InStandardAsset)
{
	TArray<FName> Names;
	for (const auto Item : InSelectedItems)
	{
		const FName ItemBoneName = Item->GetRowItemName();
		for (auto ControlledBone : InStandardAsset->GetControlledBones())
		{
			if (ControlledBone.Name == ItemBoneName)
			{
				const TSharedPtr<FSkeletonTreeItem> TreeItem = StaticCastSharedPtr<FSkeletonTreeItem>(Item);
				UBoneProxy* BoneProxy = Cast<UBoneProxy>(TreeItem->GetObject());
				BoneProxy->Location = ControlledBone.Transform.GetLocation();
				BoneProxy->Rotation = ControlledBone.Transform.GetRotation().Rotator();
				BoneProxy->Scale = ControlledBone.Transform.GetScale3D();
				FAnimNode_ModifyBone& ModifyBone = TreeItem->GetSkeletonTree()->GetPreviewScene()->GetPreviewMeshComponent()->PreviewInstance->ModifyBone(BoneProxy->BoneName);
				ModifyBone.Translation = BoneProxy->Location;
				ModifyBone.Rotation = BoneProxy->Rotation; 
				ModifyBone.Scale = BoneProxy->Scale; 
				break;
			}
		}
		Names.Add(ItemBoneName);
	}
	AppendControlledBone(CachedTreeBoneItem);
	CachedTreeBoneItem = InSelectedItems;
	InStandardAsset->MarkerModifiedBones(Names);
	if (InSelectedItems.IsEmpty())
	{
		if (IAssetEditorInstance* AssetEditorInstance = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(InStandardAsset, false))
		{
			FAnimationEditor* AnimationEditor = static_cast<FAnimationEditor*>(AssetEditorInstance);
			AnimationEditor->GetSkeletonTree()->GetPreviewScene()->GetPreviewMeshComponent()->PreviewInstance->ResetModifiedBone();
		}
	}
}
