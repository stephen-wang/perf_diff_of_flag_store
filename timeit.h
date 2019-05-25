/*
 * Copyright (c) 2019 wangwenzhi@sina.cn. All rights reserved.
 */ 

#ifndef TIMEIT_H_
#define TIMEIT_H_

#include <stdio.h>
#include <time.h>    // for clock_gettime
#include <stdint.h>  // for int64_t
#include <string.h>  // for strlen


void get_desc_time(uint64_t ns, char *buf, int len)
{
	uint64_t nano_per_sec = 1000000000;
	uint64_t nano_per_milli = 1000000;
	uint64_t nano_per_micro = 1000;
	uint64_t unit = 1000;

	uint64_t nanos = ns % unit;
	uint64_t micros = ns / nano_per_micro % unit;
	uint64_t millis = ns / nano_per_milli % unit;
	uint64_t seconds = ns / nano_per_sec;

	memset(buf, '\0', sizeof buf);
	if (seconds > 0) {
		snprintf(buf+strlen(buf), len-strlen(buf), "%lds", seconds);
	}
	
	if (millis > 0) {
		snprintf(buf+strlen(buf), len-strlen(buf), "%ldms", millis);
	}
	
	if (micros > 0) {
		snprintf(buf+strlen(buf), len-strlen(buf), "%ldµs", micros);
	}
	
	if (nanos > 0) {
		snprintf(buf+strlen(buf), len-strlen(buf), "%ldns", nanos);
	}
}

#define timeit(n, func, ...) do {                                               \
	uint64_t duration;                                                      \
	struct timespec start, end;                                             \
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);                        \
                                                                                \
	for (int i=0; i<n; i++) {                                               \
		func(__VA_ARGS__);                                              \
	}                                                                       \
                                                                                \
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);                          \
	duration = (end.tv_sec - start.tv_sec) * 1000000000                     \
		   + (end.tv_nsec - start.tv_nsec);                             \
                                                                                \
	char strSpan[256];                                                      \
	char strAvgSpan[256];                                                   \
	get_desc_time(duration, strSpan, sizeof(strSpan));                      \
	get_desc_time(duration/n, strAvgSpan, sizeof(strAvgSpan));              \
        if (n > 1) {                                                            \
	    printf("%d loops, %s, avg: %s per loop\n", n, strSpan, strAvgSpan); \
        } else {                                                                \
	    printf("avg: %s (%ld ns)\n", strAvgSpan, duration);                 \
        }                                                                       \
} while (0)


#endif // TIMEIT_H_
