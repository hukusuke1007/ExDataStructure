#ifndef _LOGOUT_H_
#define _LOGOUT_H_

#include "stdafx.h"
#include "stdarg.h"
#include <typeinfo> // classname—p

using namespace std;
namespace hukusuke {
	
#define LOG_OUTPUT(...) logout_.log( __LINE__, __func__ , __VA_ARGS__)

/* logout class */
class logout {
	/*--------------------------------*/
	/*  Public method.                */
	/*--------------------------------*/
	public:
		// Constructor.
		logout(){};
	
		// Destructor.
		~logout(){};
	
		// Output.
		void log( const int line, const char* func, const char* fmt, ...);
	/*--------------------------------*/
	/* Private method.                */
	/*--------------------------------*/
	private:
		
	/*--------------------------------*/
	/* Private member.                */
	/*--------------------------------*/
	private:
};
	
extern logout logout_;
	
}

#endif /* _LOGOUT_H_ */

