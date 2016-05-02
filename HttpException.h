#ifndef DATASERVICES_FEED_HTTPEXCEPTION
#define DATASERVICES_FEED_HTTPEXCEPTION


#include <iostream>
#include <string>

namespace Http{

	class Exception{
	private:
		std::string desc;
	public:
		inline Exception(std::string desc):desc{desc}
		{}

		inline virtual const char* what() const throw()
		{
			return desc.c_str();
		}
	};

};

#endif //DATASERVICES_FEED_HTTPEXCEPTION