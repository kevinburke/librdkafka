#pragma once

#ifdef HOST_WIN32
#include <windows.h>
#include <winnt.h>
#include <intrin.h>

#endif

typedef struct {
#ifdef __MINGW32__
        volatile LONG val;
#else
	int32_t val;
#endif
} rd_atomic32_t;

typedef struct {
	int64_t val;
} rd_atomic64_t;

static __inline int32_t RD_UNUSED rd_atomic32_add (rd_atomic32_t *ra, int32_t v) {
#ifndef HOST_WIN32
	return ATOMIC_OP(add, fetch, &ra->val, v);
#else
	return InterlockedAdd(&ra->val, v);
#endif
}

static __inline int32_t RD_UNUSED rd_atomic32_sub(rd_atomic32_t *ra, int32_t v) {
#ifndef HOST_WIN32
	return ATOMIC_OP(sub, fetch, &ra->val, v);
#else
	return InterlockedAdd(&ra->val, -v);
#endif
}

static __inline int32_t RD_UNUSED rd_atomic32_get(rd_atomic32_t *ra) {
#ifndef HOST_WIN32
	return ATOMIC_OP(fetch, add, &ra->val, 0);
#else
	return ra->val;
#endif
}

static __inline int32_t RD_UNUSED rd_atomic32_set(rd_atomic32_t *ra, int32_t v) {
#ifndef HOST_WIN32
	return ra->val = v; // FIXME
#else
	return InterlockedExchange(&ra->val, v);
#endif
}


static __inline int64_t RD_UNUSED rd_atomic64_add (rd_atomic64_t *ra, int64_t v) {
#ifndef HOST_WIN32
	return ATOMIC_OP(add, fetch, &ra->val, v);
#else
	return InterlockedAdd64(&ra->val, v);
#endif
}

static __inline int64_t RD_UNUSED rd_atomic64_sub(rd_atomic64_t *ra, int64_t v) {
#ifndef HOST_WIN32
	return ATOMIC_OP(sub, fetch, &ra->val, v);
#else
	return InterlockedAdd64(&ra->val, -v);
#endif
}

static __inline int64_t RD_UNUSED rd_atomic64_get(rd_atomic64_t *ra) {
#ifndef HOST_WIN32
	return ATOMIC_OP(fetch, add, &ra->val, 0);
#else
	return ra->val;
#endif
}


static __inline int64_t RD_UNUSED rd_atomic64_set(rd_atomic64_t *ra, int64_t v) {
#ifndef HOST_WIN32
	return ra->val = v; // FIXME
#else
	return InterlockedExchange64(&ra->val, v);
#endif
}
