#ifndef __SAFE_JSON_H__
#define __SAFE_JSON_H__
#include "JsonOptTrait.h"
#include <string>
#include <exception>
#include <sstream>

class SafeJsonException : public std::exception
{
public:
    SafeJsonException(const std::string& msg) : msg_(msg){}
    ~SafeJsonException() throw(){}
	const char* what() throw(){return msg_.c_str();}
private:
	std::string msg_;
};

class UnknowMemberException: public SafeJsonException
{
public:
    UnknowMemberException(const std::string& msg)
        :SafeJsonException(msg)
    {
    }
};

class MismatchException : public SafeJsonException
{
public:
    MismatchException(const std::string& msg)
        :SafeJsonException(msg)
    {
    }
};

class NoObjectException : public SafeJsonException
{
public:
    NoObjectException(const std::string& msg)
        :SafeJsonException(msg)
    {
    }
};

template<typename JsonValue, typename OptTrait, typename T>
struct CheckReadableTrait
{
    bool operator()(const JsonValue& info)
    {
        if (!OptTrait::CheckExist(info))
        {
            throw UnknowMemberException("in GetValue, JsonValue should not be NULL");
        }
        if (!OptTrait::template CheckType<T>(info))
        {
            throw MismatchException("in GetValue, result type is not available");
        }
        return true;
    }
};

template<typename JsonValue, typename OptTrait, typename T>
struct CheckWritableTrait
{
    bool operator()(const JsonValue& info, const std::string& key, const T& value)
    {
        if (OptTrait::CheckExist(info) && !OptTrait::CheckObject(info) )
        {
            std::ostringstream exception_msg;
            exception_msg << "in SetValue, JsonValue \"" << key << "\" should be an object";
            throw NoObjectException(exception_msg.str());
        }
        return true;
    }
};

template<typename JsonValue, typename OptTrait>
class SafeJson
{
public:
	
    template<typename T>
    static T GetValue(const JsonValue& info)
    {
    	typedef CheckReadableTrait<JsonValue, OptTrait, T> CheckTrait;
        if (!CheckTrait()(info))
        {
            throw UnknowMemberException("in GetValue, JsonValue should be readable");
        }
        return OptTrait::template GetValue<T>(info);
    }

    template<typename T, typename CheckTrait>
    static T GetValue(const JsonValue& info)
    {
        if (!CheckTrait()(info))
        {
            throw UnknowMemberException("in GetValue, JsonValue should be readable");
        }
        return OptTrait::template GetValue<T>(info);
    }
	
    template<typename T>
    static void SetValue(JsonValue& info, const std::string& key, const T& value)
    {
		typedef CheckWritableTrait<JsonValue, OptTrait, T> CheckTrait;
        if (!CheckTrait()(info, key, value))
        {
            std::ostringstream exception_msg;
            exception_msg << "in SetValue, JsonValue \"" << key << "\" should be writable";
            throw NoObjectException(exception_msg.str());
        }
        OptTrait::SetValue(info, key, value);
    }

    template<typename T, typename CheckTrait>
    static void SetValue(JsonValue& info, const std::string& key, const T& value)
    {
        if (!CheckTrait()(info, key, value))
        {
            std::ostringstream exception_msg;
            exception_msg << "in SetValue, JsonValue \"" << key << "\" should be writable";
            throw NoObjectException(exception_msg.str());
        }
        OptTrait::SetValue(info, key, value);
    }
	
};

typedef SafeJson<JsonCppTrait::_Elem, JsonCppTrait> SafeJsonCpp;

#endif
