/*
 * WARNING: do not edit!
 * Generated by makefile from ..\..\src\include\openssl\crypto.h.in
 *
 * Copyright 1995-2024 The OpenSSL Project Authors. All Rights Reserved.
 * Copyright (c) 2002, Oracle and/or its affiliates. All rights reserved
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */



#ifndef OPENSSL_CRYPTO_H
# define OPENSSL_CRYPTO_H
# pragma once

# include <openssl/macros.h>
# ifndef OPENSSL_NO_DEPRECATED_3_0
#  define HEADER_CRYPTO_H
# endif

# include <stdlib.h>
# include <time.h>

# include <openssl/e_os2.h>

# ifndef OPENSSL_NO_STDIO
#  include <stdio.h>
# endif

# include <openssl/safestack.h>
# include <openssl/opensslv.h>
# include <openssl/types.h>
# include <openssl/opensslconf.h>
# include <openssl/cryptoerr.h>
# include <openssl/core.h>

# ifdef CHARSET_EBCDIC
#  include <openssl/ebcdic.h>
# endif

/*
 * Resolve problems on some operating systems with symbol names that clash
 * one way or another
 */
# include <openssl/symhacks.h>

# ifndef OPENSSL_NO_DEPRECATED_1_1_0
#  include <openssl/opensslv.h>
# endif

#ifdef  __cplusplus
extern "C" {
#endif

# ifndef OPENSSL_NO_DEPRECATED_1_1_0
#  define SSLeay                  OpenSSL_version_num
#  define SSLeay_version          OpenSSL_version
#  define SSLEAY_VERSION_NUMBER   OPENSSL_VERSION_NUMBER
#  define SSLEAY_VERSION          OPENSSL_VERSION
#  define SSLEAY_CFLAGS           OPENSSL_CFLAGS
#  define SSLEAY_BUILT_ON         OPENSSL_BUILT_ON
#  define SSLEAY_PLATFORM         OPENSSL_PLATFORM
#  define SSLEAY_DIR              OPENSSL_DIR

/*
 * Old type for allocating dynamic locks. No longer used. Use the new thread
 * API instead.
 */
typedef struct {
    int dummy;
} CRYPTO_dynlock;

# endif /* OPENSSL_NO_DEPRECATED_1_1_0 */

typedef void CRYPTO_RWLOCK;

CRYPTO_RWLOCK *CRYPTO_THREAD_lock_new(void);
__owur int CRYPTO_THREAD_read_lock(CRYPTO_RWLOCK *lock);
__owur int CRYPTO_THREAD_write_lock(CRYPTO_RWLOCK *lock);
int CRYPTO_THREAD_unlock(CRYPTO_RWLOCK *lock);
void CRYPTO_THREAD_lock_free(CRYPTO_RWLOCK *lock);

int CRYPTO_atomic_add(int *val, int amount, int *ret, CRYPTO_RWLOCK *lock);
int CRYPTO_atomic_add64(uint64_t *val, uint64_t op, uint64_t *ret,
                        CRYPTO_RWLOCK *lock);
int CRYPTO_atomic_and(uint64_t *val, uint64_t op, uint64_t *ret,
                      CRYPTO_RWLOCK *lock);
int CRYPTO_atomic_or(uint64_t *val, uint64_t op, uint64_t *ret,
                     CRYPTO_RWLOCK *lock);
int CRYPTO_atomic_load(uint64_t *val, uint64_t *ret, CRYPTO_RWLOCK *lock);
int CRYPTO_atomic_load_int(int *val, int *ret, CRYPTO_RWLOCK *lock);
int CRYPTO_atomic_store(uint64_t *dst, uint64_t val, CRYPTO_RWLOCK *lock);

/* No longer needed, so this is a no-op */
#define OPENSSL_malloc_init() while(0) continue

# define OPENSSL_malloc(num) \
        CRYPTO_malloc(num, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_zalloc(num) \
        CRYPTO_zalloc(num, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_aligned_alloc(num, alignment, freeptr) \
        CRYPTO_aligned_alloc(num, alignment, freeptr, \
                             OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_realloc(addr, num) \
        CRYPTO_realloc(addr, num, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_clear_realloc(addr, old_num, num) \
        CRYPTO_clear_realloc(addr, old_num, num, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_clear_free(addr, num) \
        CRYPTO_clear_free(addr, num, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_free(addr) \
        CRYPTO_free(addr, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_memdup(str, s) \
        CRYPTO_memdup((str), s, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_strdup(str) \
        CRYPTO_strdup(str, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_strndup(str, n) \
        CRYPTO_strndup(str, n, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_secure_malloc(num) \
        CRYPTO_secure_malloc(num, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_secure_zalloc(num) \
        CRYPTO_secure_zalloc(num, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_secure_free(addr) \
        CRYPTO_secure_free(addr, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_secure_clear_free(addr, num) \
        CRYPTO_secure_clear_free(addr, num, OPENSSL_FILE, OPENSSL_LINE)
# define OPENSSL_secure_actual_size(ptr) \
        CRYPTO_secure_actual_size(ptr)

size_t OPENSSL_strlcpy(char *dst, const char *src, size_t siz);
size_t OPENSSL_strlcat(char *dst, const char *src, size_t siz);
size_t OPENSSL_strnlen(const char *str, size_t maxlen);
int OPENSSL_strtoul(const char *str, char **endptr, int base, unsigned long *num);
int OPENSSL_buf2hexstr_ex(char *str, size_t str_n, size_t *strlength,
                          const unsigned char *buf, size_t buflen,
                          const char sep);
char *OPENSSL_buf2hexstr(const unsigned char *buf, long buflen);
int OPENSSL_hexstr2buf_ex(unsigned char *buf, size_t buf_n, size_t *buflen,
                          const char *str, const char sep);
unsigned char *OPENSSL_hexstr2buf(const char *str, long *buflen);
int OPENSSL_hexchar2int(unsigned char c);
int OPENSSL_strcasecmp(const char *s1, const char *s2);
int OPENSSL_strncasecmp(const char *s1, const char *s2, size_t n);

# define OPENSSL_MALLOC_MAX_NELEMS(type)  (((1U<<(sizeof(int)*8-1))-1)/sizeof(type))

/*
 * These functions return the values of OPENSSL_VERSION_MAJOR,
 * OPENSSL_VERSION_MINOR, OPENSSL_VERSION_PATCH, OPENSSL_VERSION_PRE_RELEASE
 * and OPENSSL_VERSION_BUILD_METADATA, respectively.
 */
unsigned int OPENSSL_version_major(void);
unsigned int OPENSSL_version_minor(void);
unsigned int OPENSSL_version_patch(void);
const char *OPENSSL_version_pre_release(void);
const char *OPENSSL_version_build_metadata(void);

unsigned long OpenSSL_version_num(void);
const char *OpenSSL_version(int type);
# define OPENSSL_VERSION                0
# define OPENSSL_CFLAGS                 1
# define OPENSSL_BUILT_ON               2
# define OPENSSL_PLATFORM               3
# define OPENSSL_DIR                    4
# define OPENSSL_ENGINES_DIR            5
# define OPENSSL_VERSION_STRING         6
# define OPENSSL_FULL_VERSION_STRING    7
# define OPENSSL_MODULES_DIR            8
# define OPENSSL_CPU_INFO               9
# define OPENSSL_WINCTX             	10

const char *OPENSSL_info(int type);
/*
 * The series starts at 1001 to avoid confusion with the OpenSSL_version
 * types.
 */
# define OPENSSL_INFO_CONFIG_DIR                1001
# define OPENSSL_INFO_ENGINES_DIR               1002
# define OPENSSL_INFO_MODULES_DIR               1003
# define OPENSSL_INFO_DSO_EXTENSION             1004
# define OPENSSL_INFO_DIR_FILENAME_SEPARATOR    1005
# define OPENSSL_INFO_LIST_SEPARATOR            1006
# define OPENSSL_INFO_SEED_SOURCE               1007
# define OPENSSL_INFO_CPU_SETTINGS              1008
# define OPENSSL_INFO_WINDOWS_CONTEXT           1009

int OPENSSL_issetugid(void);

struct crypto_ex_data_st {
    OSSL_LIB_CTX *ctx;
    STACK_OF(void) *sk;
};

SKM_DEFINE_STACK_OF_INTERNAL(void, void, void)
#define sk_void_num(sk) OPENSSL_sk_num(ossl_check_const_void_sk_type(sk))
#define sk_void_value(sk, idx) ((void *)OPENSSL_sk_value(ossl_check_const_void_sk_type(sk), (idx)))
#define sk_void_new(cmp) ((STACK_OF(void) *)OPENSSL_sk_new(ossl_check_void_compfunc_type(cmp)))
#define sk_void_new_null() ((STACK_OF(void) *)OPENSSL_sk_new_null())
#define sk_void_new_reserve(cmp, n) ((STACK_OF(void) *)OPENSSL_sk_new_reserve(ossl_check_void_compfunc_type(cmp), (n)))
#define sk_void_reserve(sk, n) OPENSSL_sk_reserve(ossl_check_void_sk_type(sk), (n))
#define sk_void_free(sk) OPENSSL_sk_free(ossl_check_void_sk_type(sk))
#define sk_void_zero(sk) OPENSSL_sk_zero(ossl_check_void_sk_type(sk))
#define sk_void_delete(sk, i) ((void *)OPENSSL_sk_delete(ossl_check_void_sk_type(sk), (i)))
#define sk_void_delete_ptr(sk, ptr) ((void *)OPENSSL_sk_delete_ptr(ossl_check_void_sk_type(sk), ossl_check_void_type(ptr)))
#define sk_void_push(sk, ptr) OPENSSL_sk_push(ossl_check_void_sk_type(sk), ossl_check_void_type(ptr))
#define sk_void_unshift(sk, ptr) OPENSSL_sk_unshift(ossl_check_void_sk_type(sk), ossl_check_void_type(ptr))
#define sk_void_pop(sk) ((void *)OPENSSL_sk_pop(ossl_check_void_sk_type(sk)))
#define sk_void_shift(sk) ((void *)OPENSSL_sk_shift(ossl_check_void_sk_type(sk)))
#define sk_void_pop_free(sk, freefunc) OPENSSL_sk_pop_free(ossl_check_void_sk_type(sk),ossl_check_void_freefunc_type(freefunc))
#define sk_void_insert(sk, ptr, idx) OPENSSL_sk_insert(ossl_check_void_sk_type(sk), ossl_check_void_type(ptr), (idx))
#define sk_void_set(sk, idx, ptr) ((void *)OPENSSL_sk_set(ossl_check_void_sk_type(sk), (idx), ossl_check_void_type(ptr)))
#define sk_void_find(sk, ptr) OPENSSL_sk_find(ossl_check_void_sk_type(sk), ossl_check_void_type(ptr))
#define sk_void_find_ex(sk, ptr) OPENSSL_sk_find_ex(ossl_check_void_sk_type(sk), ossl_check_void_type(ptr))
#define sk_void_find_all(sk, ptr, pnum) OPENSSL_sk_find_all(ossl_check_void_sk_type(sk), ossl_check_void_type(ptr), pnum)
#define sk_void_sort(sk) OPENSSL_sk_sort(ossl_check_void_sk_type(sk))
#define sk_void_is_sorted(sk) OPENSSL_sk_is_sorted(ossl_check_const_void_sk_type(sk))
#define sk_void_dup(sk) ((STACK_OF(void) *)OPENSSL_sk_dup(ossl_check_const_void_sk_type(sk)))
#define sk_void_deep_copy(sk, copyfunc, freefunc) ((STACK_OF(void) *)OPENSSL_sk_deep_copy(ossl_check_const_void_sk_type(sk), ossl_check_void_copyfunc_type(copyfunc), ossl_check_void_freefunc_type(freefunc)))
#define sk_void_set_cmp_func(sk, cmp) ((sk_void_compfunc)OPENSSL_sk_set_cmp_func(ossl_check_void_sk_type(sk), ossl_check_void_compfunc_type(cmp)))



/*
 * Per class, we have a STACK of function pointers.
 */
# define CRYPTO_EX_INDEX_SSL              0
# define CRYPTO_EX_INDEX_SSL_CTX          1
# define CRYPTO_EX_INDEX_SSL_SESSION      2
# define CRYPTO_EX_INDEX_X509             3
# define CRYPTO_EX_INDEX_X509_STORE       4
# define CRYPTO_EX_INDEX_X509_STORE_CTX   5
# define CRYPTO_EX_INDEX_DH               6
# define CRYPTO_EX_INDEX_DSA              7
# define CRYPTO_EX_INDEX_EC_KEY           8
# define CRYPTO_EX_INDEX_RSA              9
# define CRYPTO_EX_INDEX_ENGINE          10
# define CRYPTO_EX_INDEX_UI              11
# define CRYPTO_EX_INDEX_BIO             12
# define CRYPTO_EX_INDEX_APP             13
# define CRYPTO_EX_INDEX_UI_METHOD       14
# define CRYPTO_EX_INDEX_RAND_DRBG       15
# define CRYPTO_EX_INDEX_DRBG            CRYPTO_EX_INDEX_RAND_DRBG
# define CRYPTO_EX_INDEX_OSSL_LIB_CTX    16
# define CRYPTO_EX_INDEX_EVP_PKEY        17
# define CRYPTO_EX_INDEX__COUNT          18

typedef void CRYPTO_EX_new (void *parent, void *ptr, CRYPTO_EX_DATA *ad,
                           int idx, long argl, void *argp);
typedef void CRYPTO_EX_free (void *parent, void *ptr, CRYPTO_EX_DATA *ad,
                             int idx, long argl, void *argp);
typedef int CRYPTO_EX_dup (CRYPTO_EX_DATA *to, const CRYPTO_EX_DATA *from,
                           void **from_d, int idx, long argl, void *argp);
__owur int CRYPTO_get_ex_new_index(int class_index, long argl, void *argp,
                                   CRYPTO_EX_new *new_func,
                                   CRYPTO_EX_dup *dup_func,
                                   CRYPTO_EX_free *free_func);
/* No longer use an index. */
int CRYPTO_free_ex_index(int class_index, int idx);

/*
 * Initialise/duplicate/free CRYPTO_EX_DATA variables corresponding to a
 * given class (invokes whatever per-class callbacks are applicable)
 */
int CRYPTO_new_ex_data(int class_index, void *obj, CRYPTO_EX_DATA *ad);
int CRYPTO_dup_ex_data(int class_index, CRYPTO_EX_DATA *to,
                       const CRYPTO_EX_DATA *from);

void CRYPTO_free_ex_data(int class_index, void *obj, CRYPTO_EX_DATA *ad);

/* Allocate a single item in the CRYPTO_EX_DATA variable */
int CRYPTO_alloc_ex_data(int class_index, void *obj, CRYPTO_EX_DATA *ad,
                         int idx);

/*
 * Get/set data in a CRYPTO_EX_DATA variable corresponding to a particular
 * index (relative to the class type involved)
 */
int CRYPTO_set_ex_data(CRYPTO_EX_DATA *ad, int idx, void *val);
void *CRYPTO_get_ex_data(const CRYPTO_EX_DATA *ad, int idx);

# ifndef OPENSSL_NO_DEPRECATED_1_1_0
/*
 * This function cleans up all "ex_data" state. It mustn't be called under
 * potential race-conditions.
 */
# define CRYPTO_cleanup_all_ex_data() while(0) continue

/*
 * The old locking functions have been removed completely without compatibility
 * macros. This is because the old functions either could not properly report
 * errors, or the returned error values were not clearly documented.
 * Replacing the locking functions with no-ops would cause race condition
 * issues in the affected applications. It is far better for them to fail at
 * compile time.
 * On the other hand, the locking callbacks are no longer used.  Consequently,
 * the callback management functions can be safely replaced with no-op macros.
 */
#  define CRYPTO_num_locks()            (1)
#  define CRYPTO_set_locking_callback(func)
#  define CRYPTO_get_locking_callback()         (NULL)
#  define CRYPTO_set_add_lock_callback(func)
#  define CRYPTO_get_add_lock_callback()        (NULL)

/*
 * These defines where used in combination with the old locking callbacks,
 * they are not called anymore, but old code that's not called might still
 * use them.
 */
#  define CRYPTO_LOCK             1
#  define CRYPTO_UNLOCK           2
#  define CRYPTO_READ             4
#  define CRYPTO_WRITE            8

/* This structure is no longer used */
typedef struct crypto_threadid_st {
    int dummy;
} CRYPTO_THREADID;
/* Only use CRYPTO_THREADID_set_[numeric|pointer]() within callbacks */
#  define CRYPTO_THREADID_set_numeric(id, val)
#  define CRYPTO_THREADID_set_pointer(id, ptr)
#  define CRYPTO_THREADID_set_callback(threadid_func)   (0)
#  define CRYPTO_THREADID_get_callback()                (NULL)
#  define CRYPTO_THREADID_current(id)
#  define CRYPTO_THREADID_cmp(a, b)                     (-1)
#  define CRYPTO_THREADID_cpy(dest, src)
#  define CRYPTO_THREADID_hash(id)                      (0UL)

#  ifndef OPENSSL_NO_DEPRECATED_1_0_0
#   define CRYPTO_set_id_callback(func)
#   define CRYPTO_get_id_callback()                     (NULL)
#   define CRYPTO_thread_id()                           (0UL)
#  endif /* OPENSSL_NO_DEPRECATED_1_0_0 */

#  define CRYPTO_set_dynlock_create_callback(dyn_create_function)
#  define CRYPTO_set_dynlock_lock_callback(dyn_lock_function)
#  define CRYPTO_set_dynlock_destroy_callback(dyn_destroy_function)
#  define CRYPTO_get_dynlock_create_callback()          (NULL)
#  define CRYPTO_get_dynlock_lock_callback()            (NULL)
#  define CRYPTO_get_dynlock_destroy_callback()         (NULL)
# endif /* OPENSSL_NO_DEPRECATED_1_1_0 */

typedef void *(*CRYPTO_malloc_fn)(size_t num, const char *file, int line);
typedef void *(*CRYPTO_realloc_fn)(void *addr, size_t num, const char *file,
                                   int line);
typedef void (*CRYPTO_free_fn)(void *addr, const char *file, int line);
int CRYPTO_set_mem_functions(CRYPTO_malloc_fn malloc_fn,
                             CRYPTO_realloc_fn realloc_fn,
                             CRYPTO_free_fn free_fn);
void CRYPTO_get_mem_functions(CRYPTO_malloc_fn *malloc_fn,
                              CRYPTO_realloc_fn *realloc_fn,
                              CRYPTO_free_fn *free_fn);

OSSL_CRYPTO_ALLOC void *CRYPTO_malloc(size_t num, const char *file, int line);
OSSL_CRYPTO_ALLOC void *CRYPTO_zalloc(size_t num, const char *file, int line);
OSSL_CRYPTO_ALLOC void *CRYPTO_aligned_alloc(size_t num, size_t align,
                                             void **freeptr, const char *file,
                                             int line);
OSSL_CRYPTO_ALLOC void *CRYPTO_memdup(const void *str, size_t siz, const char *file, int line);
OSSL_CRYPTO_ALLOC char *CRYPTO_strdup(const char *str, const char *file, int line);
OSSL_CRYPTO_ALLOC char *CRYPTO_strndup(const char *str, size_t s, const char *file, int line);
void CRYPTO_free(void *ptr, const char *file, int line);
void CRYPTO_clear_free(void *ptr, size_t num, const char *file, int line);
void *CRYPTO_realloc(void *addr, size_t num, const char *file, int line);
void *CRYPTO_clear_realloc(void *addr, size_t old_num, size_t num,
                           const char *file, int line);

int CRYPTO_secure_malloc_init(size_t sz, size_t minsize);
int CRYPTO_secure_malloc_done(void);
OSSL_CRYPTO_ALLOC void *CRYPTO_secure_malloc(size_t num, const char *file, int line);
OSSL_CRYPTO_ALLOC void *CRYPTO_secure_zalloc(size_t num, const char *file, int line);
void CRYPTO_secure_free(void *ptr, const char *file, int line);
void CRYPTO_secure_clear_free(void *ptr, size_t num,
                              const char *file, int line);
int CRYPTO_secure_allocated(const void *ptr);
int CRYPTO_secure_malloc_initialized(void);
size_t CRYPTO_secure_actual_size(void *ptr);
size_t CRYPTO_secure_used(void);

void OPENSSL_cleanse(void *ptr, size_t len);

# ifndef OPENSSL_NO_CRYPTO_MDEBUG
/*
 * The following can be used to detect memory leaks in the library. If
 * used, it turns on malloc checking
 */
# define CRYPTO_MEM_CHECK_OFF     0x0   /* Control only */
# define CRYPTO_MEM_CHECK_ON      0x1   /* Control and mode bit */
# define CRYPTO_MEM_CHECK_ENABLE  0x2   /* Control and mode bit */
# define CRYPTO_MEM_CHECK_DISABLE 0x3   /* Control only */

/* max allowed length for value of OPENSSL_MALLOC_FAILURES env var. */
#  define CRYPTO_MEM_CHECK_MAX_FS 256

void CRYPTO_get_alloc_counts(int *mcount, int *rcount, int *fcount);
#  ifndef OPENSSL_NO_DEPRECATED_3_0
#    define OPENSSL_mem_debug_push(info) \
         CRYPTO_mem_debug_push(info, OPENSSL_FILE, OPENSSL_LINE)
#    define OPENSSL_mem_debug_pop() \
         CRYPTO_mem_debug_pop()
#  endif
#  ifndef OPENSSL_NO_DEPRECATED_3_0
OSSL_DEPRECATEDIN_3_0 int CRYPTO_set_mem_debug(int flag);
OSSL_DEPRECATEDIN_3_0 int CRYPTO_mem_ctrl(int mode);
OSSL_DEPRECATEDIN_3_0 int CRYPTO_mem_debug_push(const char *info,
                                                const char *file, int line);
OSSL_DEPRECATEDIN_3_0 int CRYPTO_mem_debug_pop(void);
OSSL_DEPRECATEDIN_3_0 void CRYPTO_mem_debug_malloc(void *addr, size_t num,
                                                   int flag,
                                                   const char *file, int line);
OSSL_DEPRECATEDIN_3_0 void CRYPTO_mem_debug_realloc(void *addr1, void *addr2,
                                                    size_t num, int flag,
                                                    const char *file, int line);
OSSL_DEPRECATEDIN_3_0 void CRYPTO_mem_debug_free(void *addr, int flag,
                                                 const char *file, int line);
OSSL_DEPRECATEDIN_3_0
int CRYPTO_mem_leaks_cb(int (*cb)(const char *str, size_t len, void *u),
                        void *u);
#  endif
#  ifndef OPENSSL_NO_STDIO
#  ifndef OPENSSL_NO_DEPRECATED_3_0
OSSL_DEPRECATEDIN_3_0 int CRYPTO_mem_leaks_fp(FILE *);
#  endif
#  endif
# ifndef OPENSSL_NO_DEPRECATED_3_0
OSSL_DEPRECATEDIN_3_0 int CRYPTO_mem_leaks(BIO *bio);
# endif
# endif /* OPENSSL_NO_CRYPTO_MDEBUG */

/* die if we have to */
ossl_noreturn void OPENSSL_die(const char *assertion, const char *file, int line);
# ifndef OPENSSL_NO_DEPRECATED_1_1_0
#  define OpenSSLDie(f,l,a) OPENSSL_die((a),(f),(l))
# endif
# define OPENSSL_assert(e) \
    (void)((e) ? 0 : (OPENSSL_die("assertion failed: " #e, OPENSSL_FILE, OPENSSL_LINE), 1))

int OPENSSL_isservice(void);

void OPENSSL_init(void);
# ifdef OPENSSL_SYS_UNIX
#  ifndef OPENSSL_NO_DEPRECATED_3_0
OSSL_DEPRECATEDIN_3_0 void OPENSSL_fork_prepare(void);
OSSL_DEPRECATEDIN_3_0 void OPENSSL_fork_parent(void);
OSSL_DEPRECATEDIN_3_0 void OPENSSL_fork_child(void);
#  endif
# endif

struct tm *OPENSSL_gmtime(const time_t *timer, struct tm *result);
int OPENSSL_gmtime_adj(struct tm *tm, int offset_day, long offset_sec);
int OPENSSL_gmtime_diff(int *pday, int *psec,
                        const struct tm *from, const struct tm *to);

/*
 * CRYPTO_memcmp returns zero iff the |len| bytes at |a| and |b| are equal.
 * It takes an amount of time dependent on |len|, but independent of the
 * contents of |a| and |b|. Unlike memcmp, it cannot be used to put elements
 * into a defined order as the return value when a != b is undefined, other
 * than to be non-zero.
 */
int CRYPTO_memcmp(const void * in_a, const void * in_b, size_t len);

/* Standard initialisation options */
# define OPENSSL_INIT_NO_LOAD_CRYPTO_STRINGS 0x00000001L
# define OPENSSL_INIT_LOAD_CRYPTO_STRINGS    0x00000002L
# define OPENSSL_INIT_ADD_ALL_CIPHERS        0x00000004L
# define OPENSSL_INIT_ADD_ALL_DIGESTS        0x00000008L
# define OPENSSL_INIT_NO_ADD_ALL_CIPHERS     0x00000010L
# define OPENSSL_INIT_NO_ADD_ALL_DIGESTS     0x00000020L
# define OPENSSL_INIT_LOAD_CONFIG            0x00000040L
# define OPENSSL_INIT_NO_LOAD_CONFIG         0x00000080L
# define OPENSSL_INIT_ASYNC                  0x00000100L
# define OPENSSL_INIT_ENGINE_RDRAND          0x00000200L
# define OPENSSL_INIT_ENGINE_DYNAMIC         0x00000400L
# define OPENSSL_INIT_ENGINE_OPENSSL         0x00000800L
# define OPENSSL_INIT_ENGINE_CRYPTODEV       0x00001000L
# define OPENSSL_INIT_ENGINE_CAPI            0x00002000L
# define OPENSSL_INIT_ENGINE_PADLOCK         0x00004000L
# define OPENSSL_INIT_ENGINE_AFALG           0x00008000L
/* FREE:                                     0x00010000L */
# define OPENSSL_INIT_ATFORK                 0x00020000L
/* OPENSSL_INIT_BASE_ONLY                    0x00040000L */
# define OPENSSL_INIT_NO_ATEXIT              0x00080000L
/* OPENSSL_INIT flag range 0x03f00000 reserved for OPENSSL_init_ssl() */
/* FREE: 0x04000000L */
/* FREE: 0x08000000L */
/* FREE: 0x10000000L */
/* FREE: 0x20000000L */
/* FREE: 0x40000000L */
/* FREE: 0x80000000L */
/* Max OPENSSL_INIT flag value is 0x80000000 */

/* openssl and dasync not counted as builtin */
# define OPENSSL_INIT_ENGINE_ALL_BUILTIN \
    (OPENSSL_INIT_ENGINE_RDRAND | OPENSSL_INIT_ENGINE_DYNAMIC \
    | OPENSSL_INIT_ENGINE_CRYPTODEV | OPENSSL_INIT_ENGINE_CAPI | \
    OPENSSL_INIT_ENGINE_PADLOCK)

/* Library initialisation functions */
void OPENSSL_cleanup(void);
int OPENSSL_init_crypto(uint64_t opts, const OPENSSL_INIT_SETTINGS *settings);
int OPENSSL_atexit(void (*handler)(void));
void OPENSSL_thread_stop(void);
void OPENSSL_thread_stop_ex(OSSL_LIB_CTX *ctx);

/* Low-level control of initialization */
OPENSSL_INIT_SETTINGS *OPENSSL_INIT_new(void);
# ifndef OPENSSL_NO_STDIO
int OPENSSL_INIT_set_config_filename(OPENSSL_INIT_SETTINGS *settings,
                                     const char *config_filename);
void OPENSSL_INIT_set_config_file_flags(OPENSSL_INIT_SETTINGS *settings,
                                        unsigned long flags);
int OPENSSL_INIT_set_config_appname(OPENSSL_INIT_SETTINGS *settings,
                                    const char *config_appname);
# endif
void OPENSSL_INIT_free(OPENSSL_INIT_SETTINGS *settings);

# if defined(OPENSSL_THREADS) && !defined(CRYPTO_TDEBUG)
#  if defined(_WIN32)
#   if defined(BASETYPES) || defined(_WINDEF_H)
/* application has to include <windows.h> in order to use this */
typedef DWORD CRYPTO_THREAD_LOCAL;
typedef DWORD CRYPTO_THREAD_ID;

typedef LONG CRYPTO_ONCE;
#    define CRYPTO_ONCE_STATIC_INIT 0
#   endif
#  else
#   if defined(__TANDEM) && defined(_SPT_MODEL_)
#    define  SPT_THREAD_SIGNAL 1
#    define  SPT_THREAD_AWARE 1
#    include <spthread.h>
#   else
#    include <pthread.h>
#   endif
typedef pthread_once_t CRYPTO_ONCE;
typedef pthread_key_t CRYPTO_THREAD_LOCAL;
typedef pthread_t CRYPTO_THREAD_ID;

#   define CRYPTO_ONCE_STATIC_INIT PTHREAD_ONCE_INIT
#  endif
# endif

# if !defined(CRYPTO_ONCE_STATIC_INIT)
typedef unsigned int CRYPTO_ONCE;
typedef unsigned int CRYPTO_THREAD_LOCAL;
typedef unsigned int CRYPTO_THREAD_ID;
#  define CRYPTO_ONCE_STATIC_INIT 0
# endif

int CRYPTO_THREAD_run_once(CRYPTO_ONCE *once, void (*init)(void));

int CRYPTO_THREAD_init_local(CRYPTO_THREAD_LOCAL *key, void (*cleanup)(void *));
void *CRYPTO_THREAD_get_local(CRYPTO_THREAD_LOCAL *key);
int CRYPTO_THREAD_set_local(CRYPTO_THREAD_LOCAL *key, void *val);
int CRYPTO_THREAD_cleanup_local(CRYPTO_THREAD_LOCAL *key);

CRYPTO_THREAD_ID CRYPTO_THREAD_get_current_id(void);
int CRYPTO_THREAD_compare_id(CRYPTO_THREAD_ID a, CRYPTO_THREAD_ID b);

OSSL_LIB_CTX *OSSL_LIB_CTX_new(void);
OSSL_LIB_CTX *OSSL_LIB_CTX_new_from_dispatch(const OSSL_CORE_HANDLE *handle,
                                             const OSSL_DISPATCH *in);
OSSL_LIB_CTX *OSSL_LIB_CTX_new_child(const OSSL_CORE_HANDLE *handle,
                                     const OSSL_DISPATCH *in);
int OSSL_LIB_CTX_load_config(OSSL_LIB_CTX *ctx, const char *config_file);
void OSSL_LIB_CTX_free(OSSL_LIB_CTX *);
OSSL_LIB_CTX *OSSL_LIB_CTX_get0_global_default(void);
OSSL_LIB_CTX *OSSL_LIB_CTX_set0_default(OSSL_LIB_CTX *libctx);
int OSSL_LIB_CTX_get_conf_diagnostics(OSSL_LIB_CTX *ctx);
void OSSL_LIB_CTX_set_conf_diagnostics(OSSL_LIB_CTX *ctx, int value);

void OSSL_sleep(uint64_t millis);


void *OSSL_LIB_CTX_get_data(OSSL_LIB_CTX *ctx, int index);

# ifdef  __cplusplus
}
# endif
#endif
