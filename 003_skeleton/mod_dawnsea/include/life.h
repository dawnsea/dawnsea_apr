#ifndef __life_h__
#define __life_h__

#include "httpd.h"
#include "http_protocol.h"
#include "http_config.h"
#include "http_log.h"

#include "apr_hash.h"


// 쓸지 말지는 추후 결정
#define get_life_pool(life)				(life->r->pool)
#define get_life_request(life)			(life->r)

typedef struct {
	
	request_rec			*r;
	
	
	char 				*response;
	
#ifdef WEB_DEBUG	
	char 				*web_debug;
#endif	

	
} life_t;



int init_life(request_rec *r, life_t *life);



#endif
