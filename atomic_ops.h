/**
 * This file is part of the atomic_ops project.
 *
 * For the full copyright and license information, please view the COPYING
 * file that was distributed with this source code.
 *
 * @copyright  (c) the atomic_ops project
 * @author     Luca Longinotti <chtekk@longitekk.com>
 * @license    BSD 2-clause
 * @version    $Id: atomic_ops.h 1098 2012-07-30 17:56:14Z llongi $
 */

#ifndef ATOMIC_OPS_H
#define ATOMIC_OPS_H 1

/*
 * Includes and defines
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Compiler define: align types to boundary X
#if !defined(ATTR_ALIGNED)
	#define ATTR_ALIGNED(X)
#endif

// Compiler define: always inline functions
#if !defined(ATTR_ALWAYSINLINE)
	#define ATTR_ALWAYSINLINE
#endif

// Suppress unused argument warnings, if needed
#define UNUSED_ARGUMENT(arg) (void)(arg)

/*
 * Type Definitions
 */

typedef struct { volatile  intptr_t v; } atomic_ops_int  ATTR_ALIGNED(sizeof( intptr_t));
typedef struct { volatile uintptr_t v; } atomic_ops_uint ATTR_ALIGNED(sizeof(uintptr_t));
#define ATOMIC_OPS_INT_INIT(X)  { (( intptr_t)(X)) }
#define ATOMIC_OPS_UINT_INIT(X) { ((uintptr_t)(X)) }

typedef struct { void * volatile v; } atomic_ops_ptr ATTR_ALIGNED(sizeof(void *));
#define ATOMIC_OPS_PTR_INIT(X) { ((void *)(X)) }

typedef struct { atomic_ops_ptr p; } atomic_ops_flagptr ATTR_ALIGNED(sizeof(void *));
#define ATOMIC_OPS_FLAGPTR_INIT(P, F) { (ATOMIC_OPS_PTR_INIT((void *)(((uintptr_t)(P)) | ((uintptr_t)(F))))) }

typedef enum {
	ATOMIC_OPS_FENCE_NONE    = (1 << 0), // Compiler barrier (don't let the compiler reorder)
	ATOMIC_OPS_FENCE_ACQUIRE = (1 << 1), // Acquire barrier (nothing from after is reordered before)
	ATOMIC_OPS_FENCE_RELEASE = (1 << 2), // Release barrier (nothing from before is reordered after)
	ATOMIC_OPS_FENCE_FULL    = (1 << 3), // Full barrier (nothing moves around, at all)
	ATOMIC_OPS_FENCE_READ    = (1 << 4), // Read barrier (order reads, like full but only wrt reads)
	ATOMIC_OPS_FENCE_WRITE   = (1 << 5), // Write barrier (order writes, like full but only wrt writes)
} ATOMIC_OPS_FENCE;

/*
 * Functions
 */

static inline intptr_t atomic_ops_int_load(const atomic_ops_int *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_int_store(atomic_ops_int *atomic, intptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_int_not(atomic_ops_int *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_int_and(atomic_ops_int *atomic, intptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_int_or(atomic_ops_int *atomic, intptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_int_xor(atomic_ops_int *atomic, intptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_int_add(atomic_ops_int *atomic, intptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_int_inc(atomic_ops_int *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_int_dec(atomic_ops_int *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline intptr_t atomic_ops_int_fetch_and_add(atomic_ops_int *atomic, intptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline intptr_t atomic_ops_int_fetch_and_inc(atomic_ops_int *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline intptr_t atomic_ops_int_fetch_and_dec(atomic_ops_int *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline intptr_t atomic_ops_int_casr(atomic_ops_int *atomic, intptr_t oldval, intptr_t newval, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline bool atomic_ops_int_cas(atomic_ops_int *atomic, intptr_t oldval, intptr_t newval, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline intptr_t atomic_ops_int_swap(atomic_ops_int *atomic, intptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;

static inline uintptr_t atomic_ops_uint_load(const atomic_ops_uint *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_uint_store(atomic_ops_uint *atomic, uintptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_uint_not(atomic_ops_uint *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_uint_and(atomic_ops_uint *atomic, uintptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_uint_or(atomic_ops_uint *atomic, uintptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_uint_xor(atomic_ops_uint *atomic, uintptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_uint_add(atomic_ops_uint *atomic, uintptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_uint_inc(atomic_ops_uint *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_uint_dec(atomic_ops_uint *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline uintptr_t atomic_ops_uint_fetch_and_add(atomic_ops_uint *atomic, uintptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline uintptr_t atomic_ops_uint_fetch_and_inc(atomic_ops_uint *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline uintptr_t atomic_ops_uint_fetch_and_dec(atomic_ops_uint *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline uintptr_t atomic_ops_uint_casr(atomic_ops_uint *atomic, uintptr_t oldval, uintptr_t newval, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline bool atomic_ops_uint_cas(atomic_ops_uint *atomic, uintptr_t oldval, uintptr_t newval, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline uintptr_t atomic_ops_uint_swap(atomic_ops_uint *atomic, uintptr_t val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;

static inline void * atomic_ops_ptr_load(const atomic_ops_ptr *atomic, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_ptr_store(atomic_ops_ptr *atomic, void *val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void * atomic_ops_ptr_casr(atomic_ops_ptr *atomic, void *oldval, void *newval, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline bool atomic_ops_ptr_cas(atomic_ops_ptr *atomic, void *oldval, void *newval, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void * atomic_ops_ptr_swap(atomic_ops_ptr *atomic, void *val, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;

static inline void atomic_ops_fence(ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;

static inline void atomic_ops_pause(void) ATTR_ALWAYSINLINE;

/*
 * Flag-Pointer Functions
 */

static inline void * atomic_ops_flagptr_load(const atomic_ops_flagptr *atomic, bool *flag, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void * atomic_ops_flagptr_load_full(const atomic_ops_flagptr *atomic, bool *flag, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void atomic_ops_flagptr_store(atomic_ops_flagptr *atomic, void *newptr, bool newflag, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void * atomic_ops_flagptr_casr(atomic_ops_flagptr *atomic, bool *flag, void *oldptr, bool oldflag, void *newptr, bool newflag, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline bool atomic_ops_flagptr_cas(atomic_ops_flagptr *atomic, void *oldptr, bool oldflag, void *newptr, bool newflag, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;
static inline void * atomic_ops_flagptr_swap(atomic_ops_flagptr *atomic, bool *flag, void *newptr, bool newflag, ATOMIC_OPS_FENCE fence) ATTR_ALWAYSINLINE;

/*
 * Implementations
 */

#include "atomic_ops/emulation.h"

#if defined(SYSTEM_CC_GNUCC)
	#if defined(SYSTEM_CPU_X86) || defined(SYSTEM_CPU_X86_64)
		#include "atomic_ops/gcc/x86-64.h"
	#elif defined(SYSTEM_CPU_SPARC)
		#include "atomic_ops/gcc/sparcv9.h"
	#elif defined(SYSTEM_CPU_IA64)
		#include "atomic_ops/gcc/ia64.h"
	#elif defined(SYSTEM_CPU_PPC)
		#include "atomic_ops/gcc/ppc.h"
	#elif defined(SYSTEM_CPU_ARM)
		#include "atomic_ops/gcc/armv7.h"
	#else
		#include "atomic_ops/gcc/sync_intrinsics.h"
	#endif
#else
	#error Compiler not supported.
#endif

#include "atomic_ops/flagptr.h"

#endif /* ATOMIC_OPS_H */
