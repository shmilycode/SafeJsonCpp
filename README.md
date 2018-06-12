# SafeJsonCpp

# 简介：
现在项目中使用的jsoncpp，经常会因为索引的元素不存在，导致触发断言错误从而死机的问题，这个项目就是为了解决这个问题而创建。

# 使用说明：
这个项目只有两个头文件，JsonOptTrait.h和SafeJson.h。
使用时将这两个放到头文件目录下，然后头文件包含

<code> #include "JsonOptTrait.h" </code>

头文件中主要实现了两个函数, SetValue和GetValue，

使用时，需要使用异常处理机制，即：

```cpp
try{
  
    //SetValue
    
    SafeJsonCpp::SetValue(js_json_path["tree"], "walle", "this is walle");
    
    //GetValue
    
    std::string url = SafeJsonCpp::GetValue<std::string>(js_json_path["tree"]["walle"]);
    
}catch(SafeJsonException& ecp)

{

    std::cout << ecp.what() << std::endl;
    
}
```
就可以成功捕获并处理异常。

# 存在的问题：]
- [ 无法处理部分异常：]
```cpp
   std::string md5 = SafeJsonCpp::GetValue<std::string>(js_json_path["tree"]["walle"]["none"]);
```
  因为"walle"这个节点在json中已经是一个字符串，而不是一个Object,所以对其取"none"属性的值会直接触发断言，因为这是在Json::Value operator[] 中触发的，无法在外面提前做判断，所以暂时没有想到解决方法。需要注意是，如果这个json中"walle"不存在，或者是一个普通的Obejct，则不管"none"为何种元素都能被正常处理（触发异常或正常返回）。
  - [功能不够强大：]
  现在因为业务需要，只实现了GetValue和SetValue这两个接口，后续如果有其他需求会添加上去。
  
