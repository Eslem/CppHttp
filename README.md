# CppHttp
Simple Cpp Http header library using curl

##Usage
* GET
```Cpp
    Http::get(url, [headerMap<std::string, std::string]={}, [std::string *headerPtr]=nullptr)

```


* Chunk
```
    HttpChunked request{[](const std::string &data){}} //Lambda Function
```
