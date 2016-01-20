/*
* librdkafka - Apache Kafka C library
*
* Copyright (c) 2012-2015 Magnus Edenhill
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * Win32 (Visual Studio) support
 */
#pragma once


#include <stdlib.h>
#include <inttypes.h>
#include <sys/types.h>
#include <assert.h>



/**
 * Types
 */
#ifdef _MSC_VER
typedef SSIZE_T ssize_t;
#endif
typedef int socklen_t;

struct iovec {
	void *iov_base;
	size_t iov_len;
};

struct msghdr {
	struct iovec  *msg_iov;
	int            msg_iovlen;
};

#define LOG_EMERG   0
#define LOG_ALERT   1
#define LOG_CRIT    2
#define LOG_ERR     3
#define LOG_WARNING 4
#define LOG_NOTICE  5
#define LOG_INFO    6
#define LOG_DEBUG   7





/**
 * Allocation
 */
#define rd_alloca(N) _alloca(N)


/**
 * Strings, formatting, printf, ..
 */


#if __USE_MINGW_ANSI_STDIO > 0

/* size_t and ssize_t format strings */
#define PRIusz  "zu"
#define PRIdsz  "zd"


#define rd_snprintf(...)  __mingw_snprintf(__VA_ARGS__)
#define rd_vsnprintf(...) __mingw_vsnprintf(__VA_ARGS__)

#else

/* size_t and ssize_t format strings */
#define PRIusz  "Iu"
#define PRIdsz  "Id"


static RD_UNUSED __inline
int rd_vsnprintf (char *str, size_t size, const char *format, va_list ap) {
        int cnt = -1;

        if (size != 0)
                cnt = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
        if (cnt == -1)
                cnt = _vscprintf(format, ap);

        return cnt;
}

static RD_UNUSED __inline
int rd_snprintf (char *str, size_t size, const char *format, ...) {
        int cnt;
        va_list ap;

        va_start(ap, format);
        cnt = rd_vsnprintf(str, size, format, ap);
        va_end(ap);

        return cnt;
}
#endif


#define rd_strcasecmp(A,B) _stricmp(A,B)
#define rd_strncasecmp(A,B,N) _strnicmp(A,B,N)


/**
 * Errors
 */
static __inline RD_UNUSED const char *rd_strerror(int err) {
	static RD_TLS char ret[128];

	strerror_s(ret, sizeof(ret) - 1, err);
	return ret;
}


/**
 * Atomics
 */
#include "rdatomic.h"


/**
 * Misc
 */

/**
 * Microsecond sleep.
 * 'retry': if true, retry if sleep is interrupted (because of signal)
 */
#define rd_usleep(usec,terminate)  Sleep((usec) / 1000)


#define rd_assert(EXPR)  assert(EXPR)

