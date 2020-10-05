#include "Components/BHAttributesComponent.h"
#include "Behemoth/Behemoth.h"

void FBHAttribute::Modify(const float UpdateAmount)
{
    const float NewValue = (CurrentValue + UpdateAmount);
    Set(NewValue);
}

void FBHAttribute::ModifyMax(const float UpdateAmount)
{
    const float NewValue = (MaxValue + UpdateAmount);
    SetMax(NewValue);
}

void FBHAttribute::Set(const float SetAmount)
{
    CurrentValue = SetAmount;
    CurrentValue = FMath::Clamp(CurrentValue, 0.0f, MaxValue);
}

void FBHAttribute::SetMax(const float SetAmount)
{
    MaxValue = SetAmount;
    if (CurrentValue > MaxValue || bIsAlwaysMax)
    {
        Set(MaxValue);
    }
}

void UBHAttributesComponent::ModifyAttributeCurrent(const TEnumAsByte<EBHAttributeType> AttributeType, const float ModifyAmount)
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute to modify.")
        return;
    }

    Attributes[AttributeType].Modify(ModifyAmount);
}

void UBHAttributesComponent::SetAttributeCurrent(const TEnumAsByte<EBHAttributeType> AttributeType, const float SetValue)
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute to set.")
        return;
    }

    Attributes[AttributeType].Set(SetValue);
}

void UBHAttributesComponent::ModifyAttributeMax(const TEnumAsByte<EBHAttributeType> AttributeType, const float ModifyAmount)
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute to modify.")
        return;
    }

    Attributes[AttributeType].ModifyMax(ModifyAmount);
}

void UBHAttributesComponent::SetAttributeMax(const TEnumAsByte<EBHAttributeType> AttributeType, const float SetValue)
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute to set.")
        return;
    }

    Attributes[AttributeType].Set(SetValue);
}

float UBHAttributesComponent::GetAttributeCurrent(const TEnumAsByte<EBHAttributeType> AttributeType) const
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute.")
        return -1.0f;
    }

    return Attributes[AttributeType].GetValue();
}

float UBHAttributesComponent::GetAttributeMax(const TEnumAsByte<EBHAttributeType> AttributeType) const
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute.")
        return -1.0f;
    }

    return Attributes[AttributeType].GetMax();
}

void UBHAttributesComponent::BeginPlay()
{
    Super::BeginPlay();

    for(auto& AttributePair : Attributes)
    {
        FBHAttribute& Attribute = AttributePair.Value;
        Attribute.Set(Attribute.GetMax());
    }
}


