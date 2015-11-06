#include "apr_hash.h"

#include "debug.h"
#include "misc_util.h"

#include "init_life.h"


int init_life(request_rec *r, life_t *life) 
{
	life->r = r;
	
#ifdef WEB_DEBUG	
	life->web_debug = apr_psprintf(life->r->pool, "web debug start<br /><br />");
#endif	
	
	life->response = NULL;		// 기본 오류 페이지를 저장해두면 좋지 않을까?
	
	return TRUE;
	
}



