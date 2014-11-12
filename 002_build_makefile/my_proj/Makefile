ifeq ($(APACHE_PREFIX),)
APACHE_PREFIX = /usr/bin
endif


APXS = $(APACHE_PREFIX)/apxs

MOD_INC_DIR = -I./include
MOD_LIB_DIR = -L.
MOD_LIBS = -lm 

MOD_DIR = $(wildcard src/main/*.c)

CFLAGS = -Wc,-Wall 
CFLAGS += -Wc,-O2
CFLAGS += -Wc,-g
CFLAGS += -Wc,-Wextra

#ipc 키를 생성하기 위한 서브 토큰임
FTOK = -D__FTOK__=1

all : mod_dawnsea

mod_dawnsea :
	$(APXS) -c  $(CFLAGS) $(MOD_INC) $(MOD_LIBS) \
	            -Wc,$(FTOK) $(APACHE_VERSION) \
                -o mod_dawnsea.so -n hi.o $(MOD_DIR)

clean :
	find ./ -name "*.*o" -exec rm -f {} +
	rm -f mod_dawnsea.la
	rm -rf .libs


install :
	$(APXS) -i -a -n hi mod_dawnsea.la

