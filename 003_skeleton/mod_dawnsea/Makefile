ifeq ($(APACHE_PREFIX),)
APACHE_PREFIX = /usr/bin
endif

DEFINES = -DBUILD_DEBUG
DEFINES += -DWEB_DEBUG

APXS = $(APACHE_PREFIX)/apxs

MOD_INC = -I./include
MOD_LIB = -L.
MOD_LIB += -L./src/view
MOD_LIBS = -lm
#MOD_LIBS += -ltest

MOD_DIR = $(wildcard src/*.c)
MOD_DIR += $(wildcard src/main/*.c)
MOD_DIR += $(wildcard src/controller/*.c)
MOD_DIR += $(wildcard src/util/*.c)

HTMLS_RAW = $(wildcard src/view/*.html)
HTMLS_O = $(patsubst %.html,%.o,$(wildcard src/view/*.html))

CFLAGS =
CFLAGS += -Wc,-O2
CFLAGS += -Wc,-g
CFLAGS += -Wc,$(DEFINES)
CFLAGS += -Wc,$(FTOK) 
#CFLAGS += -Wc,-Wall 
#CFLAGS += -Wc,-Wextra

#ipc 키를 생성하기 위한 서브 토큰임
FTOK = -D__FTOK__=1

all : mod_dawnsea

mod_dawnsea :
#	objcopy -B i386 -I binary -O elf64-x86-64 $(HTMLS_RAW) $(HTMLS_O)
#	objcopy -B i386 -I binary -O elf64-x86-64 $(HTMLS_RAW) $(HTMLS_O)
#	ar cr libtest.a test.o
	
	$(APXS) -c  $(CFLAGS) $(MOD_INC) $(MOD_LIB) $(MOD_LIBS) \
	            $(APACHE_VERSION) \
                -o mod_dawnsea.so -n mod_dawnsea.o $(MOD_DIR)

clean :
	find ./ -name "*.*o" -exec rm -f {} +
	find ./ -name ".libs" -exec rm -rf {} +
	rm -f mod_dawnsea.la


install :
	$(APXS) -i -a -n dawnsea mod_dawnsea.la

