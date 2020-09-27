#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BHAttributesComponent.generated.h"

UENUM()
enum EBHAttributeType
{
	Health,
};

USTRUCT(BlueprintType)
struct FBHAttribute
{
	GENERATED_BODY()

public:
	void Modify(const float ModificationValue)
	{
		CurrentValue += ModificationValue;
		CurrentValue = FMath::Clamp(CurrentValue, 0.0f, MaxValue);
	}
	
	void Set(const float SetValue)
	{
		CurrentValue = SetValue;
		CurrentValue = FMath::Clamp(CurrentValue, 0.0f, MaxValue);
	}

	float GetMaxValue() const { return MaxValue; }
	float GetCurrentValue() const { return CurrentValue; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	float MaxValue = 100;
	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	float CurrentValue = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEHEMOTH_API UBHAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBHAttributesComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float ModifyAttribute(const TEnumAsByte<EBHAttributeType> AttributeType, const float ModifyAmount);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float SetAttribute(const TEnumAsByte<EBHAttributeType> AttributeType, const float SetValue);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetAttributeCurrent(const TEnumAsByte<EBHAttributeType> AttributeType) const;
	UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetAttributeMax(const TEnumAsByte<EBHAttributeType> AttributeType) const;
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TMap<TEnumAsByte<EBHAttributeType>, FBHAttribute> Attributes;
};
