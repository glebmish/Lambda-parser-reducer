#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#define LOG DEBUG scope_logger __log__(__FUNCTION__, __FILE__) 
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

class scope_logger
{
	string function, file;
    int indent;
public:
	scope_logger(string func, string fl)
	{
		function = func;
		file = fl;	
        indent = function.length() + 4 + file.length();
		std::cout << function << " in " << file  << ": Enter\n";
	}

	~scope_logger()
	{
		std::cout << function << " in " << file  << ": Exit\n";
	}

	void print (std::string msg) 
	{
		std::cout << string(indent, ' ') << ": " << msg << "\n";
	}
};
