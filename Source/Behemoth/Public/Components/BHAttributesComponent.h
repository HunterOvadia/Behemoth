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
	void Modify(const float UpdateAmount);
	void ModifyMax(const float UpdateAmount);
	void Set(const float SetAmount);
	void SetMax(const float SetAmount);
	
	float GetValue() const { return CurrentValue; }
	float GetMax() const { return MaxValue; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	float MaxValue = 100;
	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	float CurrentValue = 0;
	
	// TODO(Hunter): Better way to do this?
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	bool bIsAlwaysMax = false;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BEHEMOTH_API UBHAttributesComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:		
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ModifyAttributeCurrent(const TEnumAsByte<EBHAttributeType> AttributeType, const float ModifyAmount);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void SetAttributeCurrent(const TEnumAsByte<EBHAttributeType> AttributeType, const float SetValue);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ModifyAttributeMax(const TEnumAsByte<EBHAttributeType> AttributeType, const float ModifyAmount);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
    void SetAttributeMax(const TEnumAsByte<EBHAttributeType> AttributeType, const float SetValue);
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