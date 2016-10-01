#pragma once

#include <ostream>
#include <string>
#include <sstream>

// macros for using in code
#define LOG(log) scope_logger __log__(log, __FUNCTION__, __FILE__) 
#define LOG_MESSAGE(msg) __log__.print(msg); 

// convert printable type to string
template < typename T > std::string to_string( const T& n )
{
	std::ostringstream stm;
	stm << n;
	return stm.str();
}

// convert array of printable types to string
template < typename T > std::string log_array( const T *arr, size_t size)
{
    std::ostringstream stm;
    for (unsigned i = 0; i < size; ++i)
        stm << arr[i] << ' ';
    return stm.str();
}

class scope_logger {
    // log stream
    std::ostream &log;
    // scope information
    std::string beginning;

public:
	scope_logger(std::ostream &l, std::string function, std::string file);
	~scope_logger();

	void print (std::string msg);
};
