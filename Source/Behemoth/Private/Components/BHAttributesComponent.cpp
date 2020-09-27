#include "Components/BHAttributesComponent.h"

#include "Behemoth/Behemoth.h"


UBHAttributesComponent::UBHAttributesComponent()
{
}

float UBHAttributesComponent::ModifyAttribute(const TEnumAsByte<EBHAttributeType> AttributeType, const float ModifyAmount)
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute to modify.")
        return -1.0f;
    }

    FBHAttribute& Attribute = Attributes[AttributeType];
    Attribute.Modify(ModifyAmount);
    return Attribute.GetCurrentValue();
}

float UBHAttributesComponent::SetAttribute(const TEnumAsByte<EBHAttributeType> AttributeType, const float SetValue)
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute to set.")
        return -1.0f;
    }

    FBHAttribute& Attribute = Attributes[AttributeType];
    Attribute.Set(SetValue);
    return Attribute.GetCurrentValue();
}

float UBHAttributesComponent::GetAttributeCurrent(const TEnumAsByte<EBHAttributeType> AttributeType) const
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute.")
        return -1.0f;
    }

    const FBHAttribute Attribute = Attributes[AttributeType];
    return Attribute.GetCurrentValue();
}

float UBHAttributesComponent::GetAttributeMax(const TEnumAsByte<EBHAttributeType> AttributeType) const
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute.")
        return -1.0f;
    }

    const FBHAttribute Attribute = Attributes[AttributeType];
    return Attribute.GetMaxValue();
}

void UBHAttributesComponent::BeginPlay()
{
    Super::BeginPlay();

    for(auto& AttributePair : Attributes)
    {
        FBHAttribute& Attribute = AttributePair.Value;
        Attribute.Set(Attribute.GetMaxValue());
    }
}


