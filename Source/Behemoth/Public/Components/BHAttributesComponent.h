#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "BHAttributesComponent.generated.h"

UENUM()
enum EBHAttributeType
{
	Armor,
	Health,
};

USTRUCT(BlueprintType)
struct FBHAttribute
{
	GENERATED_BODY()

public:
	void UpdateValue(const float UpdateAmount);
	void UpdateMax(const float UpdateAmount);
	void SetValue(const float SetAmount);
	void SetMax(const float SetAmount);
	
	float GetValue() const { return Value; }
	float GetMax() const { return Max; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	float Max = 100;
	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	float Value = 0;
	
	// TODO(Hunter): Better way to do this?
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	bool bSetToMaxOnMaxChange = false;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BEHEMOTH_API UBHAttributesComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:		
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float ModifyAttributeCurrent(const TEnumAsByte<EBHAttributeType> AttributeType, const float ModifyAmount);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float SetAttributeCurrent(const TEnumAsByte<EBHAttributeType> AttributeType, const float SetValue);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float ModifyAttributeMax(const TEnumAsByte<EBHAttributeType> AttributeType, const float ModifyAmount);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
    float SetAttributeMax(const TEnumAsByte<EBHAttributeType> AttributeType, const float SetValue);
	
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