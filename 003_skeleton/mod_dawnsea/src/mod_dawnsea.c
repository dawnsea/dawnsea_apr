#include "httpd.h"
#include "http_protocol.h"
#include "http_config.h"
#include "http_log.h"

#include "debug.h"
#include "controller.h"
#include "life.h"
#include "response.h"

#include "env.h"

static void register_dawnsea_hooks(apr_pool_t* pool);
static int dawnsea_handler(request_rec* r);


module AP_MODULE_DECLARE_DATA dawnsea_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    load_env,
    register_dawnsea_hooks
};



static void dawnsea_child_init(apr_pool_t *p, server_rec *s)
{
	ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "server start"); 
	if (!init_controller(s)) {
		ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "server critical error"); 
		exit(-1);
	}

#ifdef BUILD_DEBUG	
	ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "-DBUILD_DEBUG is enabled"); 
#endif 

#ifdef WEB_DEBUG	
	ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "-DWEB_DEBUG is enabled"); 
#endif	
	
}

static life_t global_life;
char aaa[100];
    
static int dawnsea_handler(request_rec* r)
{
    life_t *life = &global_life;
    
    long tt; 

   
    if (!r->handler || strcmp(r->handler, "mod_dawnsea"))
        return DECLINED;
        
	init_life(r, life);
	
	excute_page(life);
	
	ap_set_content_type(r, "text/html;charset=ascii");
	
//	ap_rputs("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">", r);
//    ap_rputs("<html><head></head>", r);
    
    srand((unsigned)time(NULL));
    tt = random();
    
    sprintf(aaa, "random = %ld", tt);
    
	ap_rputs(aaa, r);    
//  ap_rputs(aaa, life->r);
    
	send_response_body(life);
	
	ap_rputs(global_env.test_msg, r);

	
    ap_rputs("</h1></body></html>", r);
//	ap_rprintf(r,"<meta http-equiv=\"REFRESH\" content=\"0; URL=http://localhost\">");
    
	char *cookie = apr_pstrcat(r->pool, "eeee=eeee", NULL);
    apr_table_add(r->headers_out, "Set-Cookie", cookie);
    
    

      return OK;
}

static void register_dawnsea_hooks(apr_pool_t* pool)
{
    ap_hook_child_init (dawnsea_child_init, NULL, NULL, APR_HOOK_MIDDLE); 
    ap_hook_handler(dawnsea_handler, NULL, NULL, APR_HOOK_MIDDLE);
}






















#if 0

    if (r->method_number != M_GET)
        return HTTP_METHOD_NOT_ALLOWED;
        

   
    
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, "erereerer");
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, "hello2");                 
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, "hello3 %s", global_env.test_msg);                 
    ap_set_content_type(r, "text/html;charset=ascii");
    ap_rputs("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">", r);
    ap_rputs("<html><head></head>", r);
    ap_rputs("<body><h1>Hello World!", r);
    ap_rprintf(r, "%s, %s, %ld", r->uri, global_env.test_msg, global_env.test_int);
//    ap_rprintf(r, "%s, %s, %d", r->uri, global_env.test_msg, 3333);
    
//    ap_rputs(r->notes, r);
    ap_rputs("</h1></body></html>", r);

#endif
