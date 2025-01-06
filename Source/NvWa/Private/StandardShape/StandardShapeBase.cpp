#include "StandardShape/StandardShapeBase.h"
UStandardShapeBase::UStandardShapeBase()
{
	AdditiveAnimType = AAT_LocalSpaceBase;
}
bool UStandardShapeBase::IsValidAdditive() const
{
	return true;	
}
#if WITH_EDITORONLY_DATA
void UStandardShapeBase::AppendControlledBoneEntries(const FControlledBoneEntry& BoneEntry)
{
	FString Key = BoneEntry.Name.ToString() + FString::FromInt(BoneEntry.Index);
	if (int32* Id = ControlledBoneEntryKeys.Find(Key))
	{
		ControlledBoneEntries[*Id] = BoneEntry;
	}
	else
	{
		FControlledBoneEntry& NewControlledBoneEntry = ControlledBoneEntries.Emplace_GetRef(BoneEntry.Name, BoneEntry.Index, BoneEntry.Transform);
		ControlledBoneEntryKeys.Add(Key, ControlledBoneEntries.Num() - 1);
	}
}
#endif
void UStandardShapeBase::GetAnimationPose(FAnimationPoseData& OutPoseData, const FAnimExtractContext& ExtractionContext) const
{
	Super::GetAnimationPose(OutPoseData, ExtractionContext);
	if (!IsValidAdditive()) return;

	for (auto& ControlledBoneEntry : ControlledBoneEntries)
	{
		if (ModifiedBoneNames.Find(ControlledBoneEntry.Name) != INDEX_NONE) continue;
		
		FCompactPose& OutPose = OutPoseData.GetPose();
		if (ControlledBoneEntry.Index < OutPose.GetNumBones())
		{
			FCompactPoseBoneIndex ControlledPoseBoneIndex(ControlledBoneEntry.Index);
			OutPose[ControlledPoseBoneIndex] = ControlledBoneEntry.Transform;
		}
	}
}

int32 UStandardShapeBase::GetNumberOfFrames() const
{
	return 1;
}

FFrameRate UStandardShapeBase::GetSamplingFrameRate() const
{
	return FFrameRate(30, 1);
}

const TArray<FControlledBoneEntry>& UStandardShapeBase::GetControlledBones()
{
	return ControlledBoneEntries;	
}
