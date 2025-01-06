

#include "StandardShape/StandardShapeBase.h"

bool UStandardShapeBase::IsValidAdditive() const
{
	return true;	
}

void UStandardShapeBase::GetAnimationPose(FAnimationPoseData& OutPoseData, const FAnimExtractContext& ExtractionContext) const
{
	if (!IsValidAdditive()) return;

	for (auto& ControlledBoneEntry : ControlledBoneEntries)
	{
		FCompactPose& OutPose = OutPoseData.GetPose();
		// FBoneContainer& BoneContainer = OutPose.GetBoneContainer();
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

void UStandardShapeBase::UpdateControlledBoneEntries()
{
	const FReferenceSkeleton& ReferenceSkeleton = GetSkeleton()->GetReferenceSkeleton();
	const TArray<FTransform>& RefBonePose = ReferenceSkeleton.GetRefBonePose();
	const TArray<FTransform>& RefRawBonePose = ReferenceSkeleton.GetRawRefBonePose();
	//ReferenceSkeleton.GetRawRefBonePose()
	const auto& AnimDataModel = GetDataModel();
	//获取所有的骨骼点
	TArray<FName> AnimBoneTrackNames;
	AnimDataModel->GetBoneTrackNames(AnimBoneTrackNames);
	//获取所有的骨骼的变换
	TArray<FTransform> AnimBoneTrackTransforms;
	AnimDataModel->GetBoneTracksTransform(AnimBoneTrackNames, FFrameNumber(), AnimBoneTrackTransforms);

	// for (const auto& AnimBoneName : AnimBoneTrackNames)
	for (int32 Index = 0; Index < RefBonePose.Num(); Index++)
	{
		FName AnimBoneName = ReferenceSkeleton.GetBoneName(Index);
		int32 BoneIndex = ReferenceSkeleton.FindBoneIndex(AnimBoneName);
		if (RefBonePose[BoneIndex].GetScale3D().Y == 2.0)
		{
			ControlledBoneEntries.Emplace(AnimBoneTrackNames[BoneIndex], BoneIndex, AnimBoneTrackTransforms[BoneIndex]);
		}
		if (!RefBonePose[BoneIndex].Equals(RefRawBonePose[BoneIndex]))
		{
			ControlledBoneEntries.Emplace(AnimBoneTrackNames[BoneIndex], BoneIndex, AnimBoneTrackTransforms[BoneIndex]);
		}
	}
}

