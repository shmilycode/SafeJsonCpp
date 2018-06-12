#ifndef __JSON_OPT_TRAIT__
#define __JSON_OPT_TRAIT__
#include "json/value.h"

template<typename JsonValue>
class JsonOptTrait
{
public:
    //you'd better use typetrait here.
    typedef JsonValue _Elem;
    typedef JsonValue& _ElemReference;
    typedef JsonValue* _ElemPointer;

    static bool CheckExist(const _Elem& info);

    static bool CheckObject(const _Elem& info);

    template<typename T>
    static bool CheckType(const _Elem& info);

    template<typename T>
    static T GetValue(const _Elem& info);

    template<typename T>
    static void SetValue(_Elem& info, const std::string& key, const T& value)
    {
        info[key] = value;
    }

};

template<>
bool JsonOptTrait<Json::Value>::CheckExist(const _Elem& info)
{
    return (!info.isNull());
}

template<>
bool JsonOptTrait<Json::Value>::CheckObject(const _Elem& info)
{
	return (info.isObject());
}

template<> template<>
bool JsonOptTrait<Json::Value>::CheckType<bool>(const _Elem& info)
{
	return info.isBool();
}

template<> template<>
bool JsonOptTrait<Json::Value>::CheckType<std::string>(const _Elem& info)
{
	return info.isString();
}

template<> template<>
bool JsonOptTrait<Json::Value>::CheckType<unsigned int>(const _Elem& info)
{
	return info.isUInt();
}

template<> template<>
bool JsonOptTrait<Json::Value>::CheckType<int>(const _Elem& info)
{
	return info.isInt();
}

template<> template<>
bool JsonOptTrait<Json::Value>::CheckType<double>(const _Elem& info)
{
	return info.isDouble();
}

template<> template<>
bool JsonOptTrait<Json::Value>::CheckType<float>(const _Elem& info)
{
	return info.isDouble();
}

template<> template<>
std::string JsonOptTrait<Json::Value>::GetValue<std::string>(const _Elem& info)
{
	return info.asString();
}

template<> template<>
unsigned int JsonOptTrait<Json::Value>::GetValue<unsigned int>(const _Elem& info)
{
	return info.asUInt();
}

template<> template<>
int JsonOptTrait<Json::Value>::GetValue<int>(const _Elem& info)
{
	return info.asInt();
}

template<> template<>
double JsonOptTrait<Json::Value>::GetValue<double>(const _Elem& info)
{
	return info.asDouble();
}

template<> template<>
float JsonOptTrait<Json::Value>::GetValue<float>(const _Elem& info)
{
	return info.asDouble();
}

template<> template<>
bool JsonOptTrait<Json::Value>::GetValue<bool>(const _Elem& info)
{
	return info.asBool();
}

typedef JsonOptTrait<Json::Value> JsonCppTrait;
#endif
