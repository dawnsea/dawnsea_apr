#include "debug_test.h"


#ifdef BUILD_DEBUG

int debug_test(life_t *life)
{
	print_info("this is info msg");
	print_info("-DBUILD_DEBUG is enabled");
	
	print_debug("This is a debug msg");
	print_error("This is a error msg");
	
	return TRUE;
}



#endif
