#ifndef DATASERVICES_FEED_HTTP
#define DATASERVICES_FEED_HTTP

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <list>    
#include <map>    
#include "HttpException.h"


namespace Http{
	inline size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data) {
		data->append((char*) ptr, size * nmemb);
		return size * nmemb;
	}

	inline void appendHeaders(CURL *curl, std::map<std::string, std::string> headers){
		struct curl_slist *list = NULL;
		for ( auto const& elem : headers){
			std::string item =  elem.first+": "+elem.second;
			list = curl_slist_append(list, item.c_str());
		}

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	}

	inline std::string get(std::string url, std::map<std::string, std::string> headerMap={}, std::string* headerPtr=nullptr){
		std::string body;
		std::string header;

		CURL* curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		if(curl){
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Http::writeFunction);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
			Http::appendHeaders(curl, headerMap);

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
			throw Http::Exception("Curl can't init");
		}
	}

}


#endif //DATASERVICES_FEED_HTTP