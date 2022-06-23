#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <execinfo.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

static pthread_mutex_t stdout_lock = PTHREAD_MUTEX_INITIALIZER;

#define BT_BUF_SIZE 100

int timestamped_printf(const char *fmt, ...){

    // Make stdout access thread-safe (only one at a time)
    pthread_mutex_lock(&stdout_lock);

    // Get the caller function name (requires -rdynamic at link time!)
    void *buffer[BT_BUF_SIZE];
    int nptrs = backtrace(buffer, BT_BUF_SIZE);
    char ** strings = backtrace_symbols(buffer, nptrs);
    char * secondFrame = strdup(strings[1]);
    free(strings);
    strtok(secondFrame, "(");
    char * callerBuffer = strtok(NULL, "+");

    // Get current timestamp with micro-second precision
    struct tm* tm_info;
    char timestamp_buffer[80];
    struct timeval tv;
    gettimeofday(&tv, NULL);
    tm_info = localtime(&tv.tv_sec);
    strftime(timestamp_buffer,80,"%Y-%m-%d %H:%M:%S", tm_info);

    // Print entry header
    fprintf(stdout, "%s,%06ld - %s() - ", timestamp_buffer, tv.tv_usec, callerBuffer);

    // Print message
    va_list argl;
    va_start(argl, fmt);
    vfprintf(stdout, fmt, argl);
    va_end(argl);

    free(secondFrame);
    pthread_mutex_unlock(&stdout_lock);
    return 0;
}
