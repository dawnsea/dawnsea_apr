#ifndef __debug_h__
#define __debug_h__

#include "httpd.h"
#include "http_protocol.h"
#include "http_log.h"

#include "apr_strings.h"

#include "life.h"

#ifdef WEB_DEBUG 
	#define add_head_debug(fmt, args...) 	do { life->web_debug = apr_pstrcat(life->r->pool, life->web_debug, apr_psprintf(life->r->pool, "[%s:%d] %s<br />", __FILE__, __LINE__, apr_psprintf(life->r->pool, fmt, ##args)), NULL); } while(0)
#else
	#define add_head_debug(fmt, args...)	do { } while(0)
#endif

#ifdef BUILD_DEBUG
	#define print_debug(fmt, args...)	do { \
				ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, life->r->server, fmt, ##args); \
				add_head_debug(fmt, ##args); \
			} while(0)
#else
	#define print_debug(fmt, args...)		do { } while(0)

#endif

#define print_error(fmt, args...)	do { \
			ap_log_error(APLOG_MARK, APLOG_ERR, 0, life->r->server, fmt, ##args); \
			add_head_debug(fmt, ##args); \
		} while(0)
		
#define print_info(fmt, args...)	do { \
			ap_log_error(APLOG_MARK, APLOG_INFO, 0, life->r->server, fmt, ##args); \
			add_head_debug(fmt, ##args); \
		} while(0)
			
APLOG_USE_MODULE(dawnsea);

#endif

