ifeq ($(APACHE_PREFIX),)
APACHE_PREFIX = /opt/local/apache2/bin
endif


APXS = $(APACHE_PREFIX)/apxs

MOD_INC_DIR = -I./include
MOD_LIB_DIR = -L.
MOD_LIBS = -lm 

MOD_DIR = $(wildcard src/*.c)

CFLAGS = -Wc,-Wall -Wc,-O2 -Wc,-g

#ipc 키를 생성하기 위한 서브 토큰임
FTOK = -D__FTOK__=1

all : mod_dawnsea

mod_dawnsea :
	$(APXS) -c  $(CFLAGS) $(MOD_INC) $(MOD_LIBS) 
	            -Wc,$(FTOK) $(APACHE_VERSION) \
                -o mod_dawnsea.so -n mod_tad.o $(MOD_LIBS) $(MOD_DIR)

clean :
    find ./ -name "*.*o" -exec rm -f {} +
