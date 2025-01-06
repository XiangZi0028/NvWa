#pragma once
#include "StandardShapeBase.generated.h"

USTRUCT(Blueprintable)
struct FControlledBoneEntry
{
	GENERATED_BODY()
	FControlledBoneEntry(){};
	FControlledBoneEntry(const FName& BoneName, const int32 BoneIndex, const FTransform& BoneTransform)
		: Name(BoneName), Index(BoneIndex), Transform(BoneTransform){ }
	
	UPROPERTY(VisibleAnywhere)
	FName Name;
	
	UPROPERTY(VisibleAnywhere)
	int32 Index;

	UPROPERTY(VisibleAnywhere)
	FTransform Transform;

	friend bool operator==(const FControlledBoneEntry& Lhs, const FControlledBoneEntry& RHS)
	{
		return Lhs.Name == RHS.Name
			&& Lhs.Index == RHS.Index
			&& Lhs.Transform.Equals(RHS.Transform);
	}

	friend bool operator!=(const FControlledBoneEntry& Lhs, const FControlledBoneEntry& RHS)
	{
		return !(Lhs == RHS);
	}

	bool IsSameBone(const FControlledBoneEntry& InBone) const
	{
		return Name == InBone.Name
			&& Index == InBone.Index;
	};
};

UCLASS()
class NVWA_API UStandardShapeBase : public UAnimSequence
{
	GENERATED_BODY()
public:
	UStandardShapeBase();

	UFUNCTION(BlueprintCallable)
	void SetControlledBoneEntries(const TArray<FControlledBoneEntry> &InControlledBoneEntries)
	{
		ControlledBoneEntries = InControlledBoneEntries;
	}
	virtual void GetAnimationPose(FAnimationPoseData& OutPoseData, const FAnimExtractContext& ExtractionContext) const override;
	virtual int32 GetNumberOfFrames() const override;
	virtual FFrameRate GetSamplingFrameRate() const override;
	virtual bool IsValidAdditive() const override;

	void MarkerModifiedBones(const TArray<FName>& BoneNames) {  ModifiedBoneNames = BoneNames; };
#if WITH_EDITORONLY_DATA
	virtual void AppendControlledBoneEntries(const FControlledBoneEntry& BoneEntry);
#endif
	const TArray<FControlledBoneEntry>& GetControlledBones();

private:
	UPROPERTY(VisibleAnywhere)
	TArray<FControlledBoneEntry> ControlledBoneEntries;

#if WITH_EDITORONLY_DATA

	UPROPERTY()
	TMap<FString, int32> ControlledBoneEntryKeys;
	
	UPROPERTY(EditAnywhere)
	UAnimSequence* DependencyAnimSequence = nullptr;

	TArray<FName> ModifiedBoneNames;
#endif
};
