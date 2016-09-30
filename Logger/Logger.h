#pragma once

#include <ostream>
#include <string>
#include <sstream>

#define LOG(log) scope_logger __log__(log, __FUNCTION__, __FILE__) 
#define LOG_MESSAGE(msg) __log__.print(msg); 

template < typename T > std::string to_string( const T& n )
{
	std::ostringstream stm;
	stm << n;
	return stm.str();
}

template < typename T > std::string log_array( const T *arr, size_t size)
{
    std::ostringstream stm;
    for (unsigned i = 0; i < size; ++i)
        stm << arr[i] << ' ';
    return stm.str();
}

class scope_logger {
    std::ostream &log;
    std::string beginning;

public:
	scope_logger(std::ostream &l, std::string function, std::string file);
	~scope_logger();

	void print (std::string msg);
};
