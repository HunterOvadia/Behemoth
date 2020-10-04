#include "Components/BHAttributesComponent.h"
#include "Behemoth/Behemoth.h"

void FBHAttribute::UpdateValue(const float UpdateAmount)
{
    const float NewValue = (Value + UpdateAmount);
    SetValue(NewValue);
}

void FBHAttribute::SetValue(const float SetAmount)
{
    Value = SetAmount;
    Value = FMath::Clamp(Value, 0.0f, Max);
}

void FBHAttribute::UpdateMax(const float UpdateAmount)
{
    const float NewValue = (Max + UpdateAmount);
    SetMax(NewValue);
}

void FBHAttribute::SetMax(const float SetAmount)
{
    Max = SetAmount;

    if (Value > Max)
    {
        SetValue(Max);
    }
    else
    {
        if (bSetToMaxOnMaxChange)
        {
            SetValue(Max);
        }
    }
}

float UBHAttributesComponent::ModifyAttributeCurrent(const TEnumAsByte<EBHAttributeType> AttributeType, const float ModifyAmount)
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute to modify.")
        return -1.0f;
    }

    FBHAttribute& Attribute = Attributes[AttributeType];
    Attribute.UpdateValue(ModifyAmount);
    return Attribute.GetValue();
}

float UBHAttributesComponent::SetAttributeCurrent(const TEnumAsByte<EBHAttributeType> AttributeType, const float SetValue)
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute to set.")
        return -1.0f;
    }

    FBHAttribute& Attribute = Attributes[AttributeType];
    Attribute.SetValue(SetValue);
    return Attribute.GetValue();
}

float UBHAttributesComponent::ModifyAttributeMax(const TEnumAsByte<EBHAttributeType> AttributeType, const float ModifyAmount)
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute to modify.")
        return -1.0f;
    }

    FBHAttribute& Attribute = Attributes[AttributeType];
    Attribute.UpdateMax(ModifyAmount);
    return Attribute.GetMax();
}

float UBHAttributesComponent::SetAttributeMax(const TEnumAsByte<EBHAttributeType> AttributeType, const float SetValue)
{
    if(!Attributes.Contains(AttributeType))
    {
        BH_LOG("Unable to find attribute to set.")
        return -1.0f;
    }

    FBHAttribute& Attribute = Attributes[AttributeType];
    Attributes[AttributeType].SetValue(SetValue);
    return Attribute.GetMax();
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
        Attribute.SetValue(Attribute.GetMax());
    }
}


