# CppHttp [![Build Status](https://travis-ci.org/Eslem/CppHttp.svg?branch=master)](https://travis-ci.org/Eslem/CppHttp)
Simple Cpp Http header library using curl

###Features
* Simple get request allowing set and return headers.
* Chunked Http

###Usage
* GET
```Cpp
    std::string Http::get(url, [headerMap<std::string, std::string]={}, [std::string *headerPtr]=nullptr);
```


* Chunk
```
    Http::HttpChunked request{[](const std::string &data){}}; //Lambda Function
    request.start();
```
