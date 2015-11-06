
#include "apr_hash.h"


#include "debug.h"
#include "debug_test.h"

#include "error_dawnsea.h"

#include "controller.h"

static apr_pool_t 			*control_pool;
static apr_hash_t			*control_map;


#define attach_control_meta(tag, func) apr_hash_set(control_map, tag, APR_HASH_KEY_STRING, (void *)func)

static void attach_controller(void)
{
	attach_control_meta("/dawnsea/debug", &debug_test);
	
}

apr_hash_t *get_control_map(void)
{
		return control_map;
}

int init_controller(server_rec* s)
{
	apr_pool_create(&control_pool, NULL);	
	if (control_pool == NULL) {
		ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "apr pool critical error");
		return FALSE;
	}
	
	control_map = apr_hash_make(control_pool);
	if (!control_map) {
		ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "apr pool critical error");
		return FALSE;
	}
	
	ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "controller init");
	
	attach_controller();
	
	return TRUE;

}

int excute_page(life_t *life)
{
	control_func_t execute_func = NULL;
		
	if (!life->r->uri || strnlen(life->r->uri, URL_LEN_MAX) > URL_LEN_MAX) {
		print_error("uri long error");
		return ERR_URI_LONG;
	}

	print_debug("url = %s", life->r->uri);
	
	execute_func = (control_func_t)apr_hash_get(control_map, life->r->uri, APR_HASH_KEY_STRING);
	if (!execute_func) {
		print_error("uri not found");
		return ERR_URI_NOT_FOUND;
	}
	
	return execute_func(life);
}

