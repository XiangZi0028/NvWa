#pragma once
#include "StandardShapeBase.generated.h"

USTRUCT(Blueprintable)
struct FControlledBoneEntry
{
	GENERATED_BODY()
	FControlledBoneEntry(){};
	FControlledBoneEntry(const FName& BoneName, const int32 BoneIndex, const FTransform& BoneTransform)
		: Name(BoneName), Index(BoneIndex), Transform(BoneTransform){ }
	
	UPROPERTY()
	FName Name;
	
	UPROPERTY()
	int32 Index;

	UPROPERTY()
	FTransform Transform;
};

UCLASS()
class NVWA_API UStandardShapeBase : public UAnimSequenceBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetControlledBoneEntries(const TArray<FControlledBoneEntry> &InControlledBoneEntries)
	{
		ControlledBoneEntries = InControlledBoneEntries;
	}
	
	virtual void GetAnimationPose(FAnimationPoseData& OutPoseData, const FAnimExtractContext& ExtractionContext) const override;
	virtual int32 GetNumberOfFrames() const override;
	virtual FFrameRate GetSamplingFrameRate() const override;
	virtual bool IsValidAdditive() const override;

	UFUNCTION(CallInEditor)
	void UpdateControlledBoneEntries();
	
	UPROPERTY(EditAnywhere)
	TArray<FControlledBoneEntry> ControlledBoneEntries;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	UAnimSequence* DependencyAnimSequence = nullptr;	
#endif
};
