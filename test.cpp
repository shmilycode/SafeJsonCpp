#include <iostream>
#include <fstream>
#include <json/reader.h>
#include <json/value.h>
#include "SafeJson.h"

struct CheckTest
{
    bool operator()(const Json::Value& value)
    {
        return !value.isNull();
    }
};

int test_get_normal()
{
    std::ifstream is_json_path;
    Json::Reader reader;
    Json::Value js_json_path;
    is_json_path.open("./test.json");
    try
    {
        if (reader.parse(is_json_path, js_json_path) == false)
        {
            throw SafeJsonException("Cant parse json file. ");
        }

        std::string url = SafeJsonCpp::GetValue<std::string>(js_json_path["downloadUrl"]);
        std::cout << url << std::endl;
        
        std::string md5 = SafeJsonCpp::GetValue<std::string>(js_json_path["fileMd5"]);
        std::cout << md5 << std::endl;
        
        int value = SafeJsonCpp::GetValue<int>(js_json_path["size"]);
        std::cout << value << std::endl;
        
        unsigned int uvalue = SafeJsonCpp::GetValue<int>(js_json_path["usize"]);
        std::cout << uvalue << std::endl;
        
        bool tf = SafeJsonCpp::GetValue<bool>(js_json_path["enable"]);
        std::cout << tf << std::endl;
        
        float asfloat = SafeJsonCpp::GetValue<float>(js_json_path["speed"]);
        std::cout << asfloat << std::endl;
        
        double asdouble = SafeJsonCpp::GetValue<double>(js_json_path["other_speed"]);
        std::cout << asdouble << std::endl;
        
        if (js_json_path["updateDesc"].isString() == true)
        {
            std::string desc  = SafeJsonCpp::GetValue<std::string>(js_json_path["updateDesc"]);
            std::cout << desc << std::endl;
        }

        std::string m_url = SafeJsonCpp::GetValue<std::string, CheckTest>(js_json_path["downloadUrl"]);
        std::cout << m_url << std::endl;

    }
    catch (SafeJsonException& ecp)
    {
        if (is_json_path.is_open())
            is_json_path.close();
        std::cout << ecp.what() << std::endl;
    }
    return 0;
}

int test_get_list()
{
    std::ifstream is_json_path;
    Json::Reader reader;
    Json::Value js_json_path;
    is_json_path.open("./test.json");
    try
    {
        if (reader.parse(is_json_path, js_json_path) == false)
        {
            throw SafeJsonException("Cant parse json file. ");
        }

        std::string url = SafeJsonCpp::GetValue<std::string>(js_json_path["tree"]["child1"]);
        std::string md5 = SafeJsonCpp::GetValue<std::string>(js_json_path["tree"]["child4"]["grandchild1"]);
//        std::string child = SafeJsonCpp::GetValue<std::string>(js_json_path["tree"]["child10"]["failed"]["grandchild1"]);
        int value = SafeJsonCpp::GetValue<int>(js_json_path["tree"]["child4"]["grandchild2"]);

        std::cout << url << std::endl;
        std::cout << md5 << std::endl;
        std::cout << value << std::endl;

    }
    catch (SafeJsonException& ecp)
    {
        if (is_json_path.is_open())
            is_json_path.close();
        std::cout << ecp.what() << std::endl;
    }
    return 0;
}

void test_set_normal()
{
    std::ifstream is_json_path;
    Json::Reader reader;
    Json::Value js_json_path;
    is_json_path.open("./test.json");
    try
    {
        if (reader.parse(is_json_path, js_json_path) == false)
        {
            throw SafeJsonException("Cant parse json file. ");
        }

        SafeJsonCpp::SetValue(js_json_path["tree"], "walle", "this is walle");
        std::string url = SafeJsonCpp::GetValue<std::string>(js_json_path["tree"]["walle"]);
        std::cout << url << std::endl;

        Json::Value Child;
        SafeJsonCpp::SetValue(Child, "NewTree", "new Tree");
        SafeJsonCpp::SetValue(js_json_path["tree"], "NewTree", Child);
        SafeJsonCpp::SetValue(js_json_path["tree"]["NewTree"], "none", "NONE");
        std::string md5 = SafeJsonCpp::GetValue<std::string>(js_json_path["tree"]["NewTree"]["none"]);

        // here would occur error, because "walle" is a value, not an Object, not like the error case in test_get_list
//        std::string md5 = SafeJsonCpp::GetValue<std::string>(js_json_path["tree"]["walle"]["none"]);
        std::cout << md5 << std::endl;

        int value = SafeJsonCpp::GetValue<int>(js_json_path["tree"]["child4"]["grandchild2"]);
        std::cout << value << std::endl;

    }
    catch (SafeJsonException& ecp)
    {
        if (is_json_path.is_open())
            is_json_path.close();
        std::cout << ecp.what() << std::endl;
    }
}

int main(int argc, char** argv)
{

    return test_get_list();
//    return test_get_normal();
//    return test_set_normal();

}
