# contrib/decimal/Makefile

MODULE_big = decimal
OBJS = decimal.o decimal64.o decimal128.o
PG_CPPFLAGS = -I$(TOOLCHAIN_DIR)/installed/include/decnumber
SHLIB_LINK = -L$(TOOLCHAIN_DIR)/installed/lib -ldecnumber 

EXTENSION = decimal
DATA = decimal--1.0.sql

REGRESS = decimal

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/decimal
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
