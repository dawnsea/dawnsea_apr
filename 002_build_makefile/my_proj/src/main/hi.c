#include <httpd.h>
#include <http_protocol.h>
#include <http_config.h>
#include <http_log.h>
//#include <apr.h>

static void register_hooks(apr_pool_t* pool);

module AP_MODULE_DECLARE_DATA hi_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks
};



static int hi_handler(request_rec* r)
{
	char temp[256];
	piped_log *my_pipe_log;
	apr_file_t *my_pipe_wfd;
//    struct ap_logconf *myconf;
        
    if (!r->handler || strcmp(r->handler, "hi"))
        return DECLINED;

    if (r->method_number != M_GET)
        return HTTP_METHOD_NOT_ALLOWED;

	APLOG_USE_MODULE(hi);
	
//	myconf = ap_new_log_config(r->pool, NULL)

//	ap_open_stderr_log(r->pool);
//	sprintf(temp, "/var/log/apache2/dawnsea%ld.log", apr_time_now());
	
	my_pipe_log = ap_open_piped_log(r->pool, "/usr/bin/rotatelogs -c /var/log/apache2/dawnsea.%Y%m%d%H%M 60 +540");
	
	my_pipe_wfd = ap_piped_log_write_fd(my_pipe_log);
	
	if (my_pipe_wfd == NULL) 
		ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, "pipe error");
	else 
		ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, "pipe ok");



//	ap_replace_stderr_log(r->pool, "/var/");
    ap_log_perror(APLOG_MARK, APLOG_ERR, 0, r->pool, "qqqqqqqq");
    
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, "erereerer");
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, "hello2");                 
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, "hello3 %d", APLOG_MODULE_INDEX);                 

#if 0    
    apr_table_merge(r->notes, "DEBUG", "hihihihihihihi1 %");	
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, "hello3 %d", APLOG_MODULE_INDEX);                 
    apr_table_merge(r->notes, "DEBUG", "hihihihihihihi2 %");	
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, "hello3 %d", APLOG_MODULE_INDEX);                 
    apr_table_merge(r->notes, "DEBUG", "hihihihihihihi3 % ");	
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, "hello3 %d", APLOG_MODULE_INDEX);                 
    
#endif	
    ap_set_content_type(r, "text/html;charset=ascii");
    ap_rputs("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">", r);
    ap_rputs("<html><head></head>", r);
    ap_rputs("<body><h1>Hello World!", r);
    ap_rprintf(r, "%s", r->uri);
    
//    ap_rputs(r->notes, r);
    ap_rputs("</h1></body></html>", r);
    
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, "log = %d", apr_file_printf(my_pipe_wfd, "sdfjlsdkjflksdjfkljdkl\n"));

	ap_close_piped_log(my_pipe_log);    
  
    return OK;
}

static void register_hooks(apr_pool_t* pool)
{
    ap_hook_handler(hi_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

