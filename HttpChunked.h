
#ifndef DATASERVICES_FEED_HTTPCHUNKED
#define DATASERVICES_FEED_HTTPCHUNKED

#include "Http.h"


namespace Http{

	using HttpChunkCallback = std::function<void(std::string)>;

	class HttpChunked{
	public:
		const HttpChunkCallback callback;
		static inline size_t onDataChunk(void *ptr, size_t size, size_t nmemb, HttpChunked* obj) {
			obj->callback((char*)ptr);
			return size * nmemb;
		}

		inline HttpChunked( const HttpChunkCallback& callback): callback{callback}{}

		inline void start(std::string url, std::map<std::string, std::string> headerMap = {}, std::string* bodyPtr = nullptr, std::string* headerPtr = nullptr){

			std::string body;
			std::string header;

			CURL* curl = curl_easy_init();
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			if(curl){
				curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &HttpChunked::onDataChunk);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
				curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);
				curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, Http::writeFunction);
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
					if(bodyPtr)
						*bodyPtr = body;
				}
			}else{
				curl_easy_cleanup(curl);
				throw Http::Exception("Curl can't init");
			}

		}
	};
}

#endif //DATASERVICES_FEED_HTTPCHUNKED