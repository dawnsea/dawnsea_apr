#ifndef __controller_h__
#define __controller_h__

#include "apr_hash.h"

#include "life.h"

typedef int (*control_func_t)(life_t *) ;

typedef struct {
	const char 				*tag; 
	control_func_t			func;
} controller_t;


int init_controller(server_rec* s);
apr_hash_t *get_control_map(void);

int excute_page(life_t *life);

#define URL_LEN_MAX				1024

#endif
