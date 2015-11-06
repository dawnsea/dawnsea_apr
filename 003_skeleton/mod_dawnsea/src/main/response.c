#include <httpd.h>

#include "life.h"

//extern char _binary_src_view_test_html_start;

void send_response_body(life_t *life)
{

//	ap_rputs(&_binary_src_view_test_html_start, life->r);
#ifdef WEB_DEBUG
	ap_rputs(life->web_debug, life->r);
#endif	
	
	if (life->response) 
		ap_rputs(life->response, life->r);
	
}


