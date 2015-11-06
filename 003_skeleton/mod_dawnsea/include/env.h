#ifndef __env_h__
#define __env_h__

#include "httpd.h"
#include "http_protocol.h"
#include "http_config.h"
#include "http_log.h"

#include "apr_strings.h"

typedef struct {
	char 			*test_msg;
	long			test_int;
	
} global_env_t;

extern global_env_t global_env;
extern const command_rec load_env[];

#endif
