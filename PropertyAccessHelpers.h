// Copyright 2019 Marcin Swiderski. All Rights Reserved.

#pragma once

namespace PropertyAccessHelpers
{

template<typename Type> struct TPropertyMapper { typedef void PropertyType; };

template<> struct TPropertyMapper<uint8> { typedef UByteProperty PropertyType; };
template<> struct TPropertyMapper<uint16> { typedef UUInt16Property PropertyType; };
template<> struct TPropertyMapper<uint32> { typedef UUInt32Property PropertyType; };
template<> struct TPropertyMapper<uint64> { typedef UUInt64Property PropertyType; };
template<> struct TPropertyMapper<int8> { typedef UInt8Property PropertyType; };
template<> struct TPropertyMapper<int16> { typedef UInt16Property PropertyType; };
template<> struct TPropertyMapper<int32> { typedef UIntProperty PropertyType; };
template<> struct TPropertyMapper<int64> { typedef UInt64Property PropertyType; };

template<> struct TPropertyMapper<float> { typedef UFloatProperty PropertyType; };
template<> struct TPropertyMapper<double> { typedef UDoubleProperty PropertyType; };

template<> struct TPropertyMapper<bool> { typedef UBoolProperty PropertyType; };

template<> struct TPropertyMapper<FString> { typedef UStrProperty PropertyType; };
template<> struct TPropertyMapper<FName> { typedef UNameProperty PropertyType; };

template<> struct TPropertyMapper<UObject*> { typedef UObjectProperty PropertyType; };
template<> struct TPropertyMapper<FWeakObjectPtr> { typedef UWeakObjectProperty PropertyType; };
template<> struct TPropertyMapper<FLazyObjectPtr> { typedef ULazyObjectProperty PropertyType; };
template<> struct TPropertyMapper<FSoftObjectPtr> { typedef USoftObjectProperty PropertyType; };

template<> struct TPropertyMapper<UClass*> { typedef UClassProperty PropertyType; };

template<typename Type, const TCHAR* PropertyName, typename ContainerType>
typename TPropertyMapper<Type>::PropertyType* GetProperty()
{
    typedef typename TPropertyMapper<Type>::PropertyType PropertyType;
    static PropertyType* Property = nullptr;
    if (!Property)
    {
        UClass* ContainerClass = ContainerType::StaticClass();
        Property = FindField<PropertyType>(ContainerClass, PropertyName);
    }
    return Property;
}

template<typename Type, const TCHAR* PropertyName, typename ContainerType>
Type* GetPropertyValuePtr(ContainerType* Container)
{
    return GetProperty<Type, PropertyName, ContainerType>()->GetPropertyValuePtr_InContainer(Container);
}

template<typename Type, const TCHAR* PropertyName, typename ContainerType>
const Type* GetPropertyValuePtr(const ContainerType* Container)
{
    return GetProperty<Type, PropertyName, ContainerType>()->GetPropertyValuePtr_InContainer(Container);
}

template<typename Type, const TCHAR* PropertyName, typename ContainerType>
Type GetPropertyValue(const ContainerType* Container)
{
    return GetProperty<Type, PropertyName, ContainerType>()->GetPropertyValue_InContainer(Container);
}

template<typename Type, const TCHAR* PropertyName, typename ContainerType>
void SetPropertyValue(ContainerType* Container, const Type& Value)
{
    GetProperty<Type, PropertyName, ContainerType>()->SetPropertyValue_InContainer(Container, Value);
}

} // namespace PropertyAccessHelpers

#define DECLARE_PNAME(PropertyName) \
    extern const TCHAR GPropertyAccessHelpersName_##PropertyName[]

#define DEFINE_PNAME(PropertyName) \
    const TCHAR GPropertyAccessHelpersName_##PropertyName[] = TEXT(#PropertyName)

#define PNAME(PropertyName) GPropertyAccessHelpersName_##PropertyName
