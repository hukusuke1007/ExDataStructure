#include "logout.h"

using namespace std;
namespace hukusuke {

// Static Definition 
logout	logout_;

/* logout log function. */
void logout::log( const int line, const char* func, const char* fmt, ...){
	
	char buf_va[ 1024 ]	= {0};
		
	va_list args;
	va_start( args, fmt );
	vsnprintf( buf_va, sizeof( buf_va ) - 1, fmt, args );
	va_end( args );
	
	printf("[%3d][%32s] %s\n", line, func, buf_va );
	
	return;
}

}// namespace hukusuke.