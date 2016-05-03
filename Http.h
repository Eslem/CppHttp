#ifndef DATASERVICES_FEED_HTTP
#define DATASERVICES_FEED_HTTP

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <list>    
#include <map>    
#include "HttpException.h"


namespace Http{

	using paramsmap = std::map<std::string, std::string>;
	using std::string;

	inline size_t writeFunction(void *ptr, size_t size, size_t nmemb, string *data) {
		data->append((char*) ptr, size * nmemb);
		return size * nmemb;
	}

	inline void appendHeaders(CURL *curl, paramsmap headers){
		struct curl_slist *list = NULL;
		for ( auto const& elem : headers){
			string item =  elem.first+": "+elem.second;
			list = curl_slist_append(list, item.c_str());
		}

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	}


	inline string mapToURL(const paramsmap &map){
		if (map.empty()){
			return "";
		}
		string query;
		for(const auto &param:map)
			query+="&"+param.first+"="+param.second; 
		query.erase(0,1);
		return query;
	}

	inline bool defaultConfig(CURL *curl, const string &url, const string *header, const string *body, const paramsmap &headerMap){

		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		if(curl){
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Http::writeFunction);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, body);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, header);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
			Http::appendHeaders(curl, headerMap);

			return true;
		}else{
			curl_easy_cleanup(curl);
			throw Http::Exception("Curl can't init");
		}
	}

	inline string get(const string &url, const paramsmap &headerMap={}, string* headerPtr=nullptr){
		string body;
		string header;

		CURL* curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		if(defaultConfig(curl, url, &header, &body, headerMap)){
			
			auto res = curl_easy_perform(curl);

			if(res != CURLE_OK){
				std::cout<<curl_easy_strerror(res);
				throw Http::Exception("Curl perform failed: ");
			}
			else{
				if(headerPtr)
					*headerPtr = header;
				return body;
			}
		}else{
			curl_easy_cleanup(curl);
			throw Http::Exception("Curl config can't init");
		}
	}

	inline string post(const string &url, const paramsmap &params, const paramsmap& headerMap={}, string* headerPtr=nullptr){
		string body;
		string header;

		CURL* curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		if(defaultConfig(curl, url, &header, &body, headerMap)){
			string data = mapToURL(params);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

			auto res = curl_easy_perform(curl);

			if(res != CURLE_OK){
				std::cout<<curl_easy_strerror(res);
				throw Http::Exception("Curl perform failed: ");
			}
			else{
				if(headerPtr)
					*headerPtr = header;
				return body;
			}
		}else{
			curl_easy_cleanup(curl);
			throw Http::Exception("Curl config can't init");
		}
	}

	
}


#endif //DATASERVICES_FEED_HTTP