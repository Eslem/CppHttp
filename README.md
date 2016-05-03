# CppHttp [![Build Status](https://travis-ci.org/Eslem/CppHttp.svg?branch=master)](https://travis-ci.org/Eslem/CppHttp)
Simple Cpp Http header library using curl

###Features
* Simple get request allowing set and return headers.
* Simple post request allowing set and return headers.
* Chunked Http

###Usage
* GET
```Cpp
    std::string Http::get(string url, [map<string, string] headers={}], [std::string *headerPtr=nullptr]);
```

* POST
```Cpp
    std::string Http::post(string url, map<string, string] params, [map<string, string> headers={}], [string *headerPtr=nullptr]);
```


* Chunk
```
    Http::HttpChunked request{[](const string &data){}}; //Lambda Function
    request.start();
```
