LDLIBS = -lm -lpapi
CFLAGS = -Wall -O0 -msse3

base: papi_helper.o time_helper.o
mul_pd: papi_helper.o time_helper.o

clean: 
	$(RM) *.o base

.PHONY: all clean
