#include "env.h"



global_env_t global_env;

#define http_if_set_env(var)	do { \
									if(!apr_strnatcmp(parms->directive->directive, #var)) { \
										global_env.var = (char *)input; \
									} \
								} while(0)

#define http_if_set_env_int(var)	(global_env.var = (int)apr_atoi64(input))


static const char *set_env_str(cmd_parms *parms, void *mconfig, const char *input)
{
	
	http_if_set_env(test_msg);

	return NULL;
	
}

static const char *set_env_int(cmd_parms *parms, void *mconfig, const char *input)
{
	
	http_if_set_env_int(test_int);

	return NULL;
	
}

const command_rec load_env[] =
{
    AP_INIT_TAKE1("test_msg", set_env_str, NULL, OR_ALL, "eeee"),
    AP_INIT_TAKE1("test_int", set_env_int, NULL, OR_ALL, "qqqq"),

// 아규먼트 2개인 경우
//    AP_INIT_TAKE2("exampleAction", example_set_action, NULL, ACCESS_CONF, "Special action value!"),
    { NULL }
};


