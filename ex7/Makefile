LDLIBS = -lm -lpapi
CFLAGS = -Wall -Wpedantic -O3 -msse3 -mavx

base: papi_helper.o time_helper.o
mul_pd: papi_helper.o time_helper.o

all: base mul_pd

clean: 
	$(RM) *.o base mul_pd

.PHONY: all clean
