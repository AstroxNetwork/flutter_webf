/*
 * Copyright (C) 2019-2022 The Kraken authors. All rights reserved.
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */

#ifndef BRIDGE_QJS_PATCH_H
#define BRIDGE_QJS_PATCH_H

#pragma warning(push)
#pragma warning(disable : 4200)

#include <quickjs/list.h>
/* added support for BigInt */
#include <quickjs/quickjs.h>
#ifdef CONFIG_BIGNUM
#include <quickjs/libbf.h>
/* added support for BigInt */
#endif
#include "foundation/string_view.h"

struct JSString {
  JSRefCountHeader header; /* must come first, 32-bit */
  uint32_t len : 31;
  uint8_t is_wide_char : 1; /* 0 = 8 bits, 1 = 16 bits characters */
  /* for JS_ATOM_TYPE_SYMBOL: hash = 0, atom_type = 3,
     for JS_ATOM_TYPE_PRIVATE: hash = 1, atom_type = 3
     XXX: could change encoding to have one more bit in hash */
  uint32_t hash : 30;
  uint8_t atom_type : 2; /* != 0 if atom, JS_ATOM_TYPE_x */
  uint32_t hash_next;    /* atom_index for JS_ATOM_TYPE_SYMBOL */
#ifdef DUMP_LEAKS
  struct list_head link; /* string list */
#endif
  union {
    uint8_t str8[0]; /* 8 bit strings will get an extra null terminator */
    uint16_t str16[0];
  } u;
};

/* added support for BigInt */
enum OPCodeEnum {
#define FMT(f)
#define DEF(id, size, n_pop, n_push, f) OP_##id,
#define def(id, size, n_pop, n_push, f)
#include <quickjs/quickjs-opcode.h>
#undef def
#undef DEF
#undef FMT
  OP_COUNT, /* excluding temporary opcodes */
  /* temporary opcodes : overlap with the short opcodes */
  OP_TEMP_START = OP_nop + 1,
  OP___dummy = OP_TEMP_START - 1,
#define FMT(f)
#define DEF(id, size, n_pop, n_push, f)
#define def(id, size, n_pop, n_push, f) OP_##id,
#include <quickjs/quickjs-opcode.h>
#undef def
#undef DEF
#undef FMT
  OP_TEMP_END,
};

typedef enum OPCodeEnum OPCodeEnum;

#ifdef CONFIG_BIGNUM
/* function pointers are used for numeric operations so that it is
   possible to remove some numeric types */
typedef struct {
  JSValue (*to_string)(JSContext* ctx, JSValueConst val);
  JSValue (*from_string)(JSContext* ctx, const char* buf, int radix, int flags, slimb_t* pexponent);
  int (*unary_arith)(JSContext* ctx, JSValue* pres, OPCodeEnum op, JSValue op1);
  int (*binary_arith)(JSContext* ctx, OPCodeEnum op, JSValue* pres, JSValue op1, JSValue op2);
  int (*compare)(JSContext* ctx, OPCodeEnum op, JSValue op1, JSValue op2);
  /* only for bigfloat: */
  JSValue (*mul_pow10_to_float64)(JSContext* ctx, const bf_t* a, int64_t exponent);
  int (*mul_pow10)(JSContext* ctx, JSValue* sp);
} JSNumericOperations;
#endif
/* added support for BigInt */

typedef enum {
  JS_GC_PHASE_NONE,
  JS_GC_PHASE_DECREF,
  JS_GC_PHASE_REMOVE_CYCLES,
} JSGCPhaseEnum;

enum {
  /* classid tag        */ /* union usage   | properties */
  JS_CLASS_OBJECT = 1,     /* must be first */
  JS_CLASS_ARRAY,          /* u.array       | length */
  JS_CLASS_ERROR,
  JS_CLASS_NUMBER,           /* u.object_data */
  JS_CLASS_STRING,           /* u.object_data */
  JS_CLASS_BOOLEAN,          /* u.object_data */
  JS_CLASS_SYMBOL,           /* u.object_data */
  JS_CLASS_ARGUMENTS,        /* u.array       | length */
  JS_CLASS_MAPPED_ARGUMENTS, /*               | length */
  JS_CLASS_DATE,             /* u.object_data */
  JS_CLASS_MODULE_NS,
  JS_CLASS_C_FUNCTION,          /* u.cfunc */
  JS_CLASS_BYTECODE_FUNCTION,   /* u.func */
  JS_CLASS_BOUND_FUNCTION,      /* u.bound_function */
  JS_CLASS_C_FUNCTION_DATA,     /* u.c_function_data_record */
  JS_CLASS_GENERATOR_FUNCTION,  /* u.func */
  JS_CLASS_FOR_IN_ITERATOR,     /* u.for_in_iterator */
  JS_CLASS_REGEXP,              /* u.regexp */
  JS_CLASS_ARRAY_BUFFER,        /* u.array_buffer */
  JS_CLASS_SHARED_ARRAY_BUFFER, /* u.array_buffer */
  JS_CLASS_UINT8C_ARRAY,        /* u.array (typed_array) */
  JS_CLASS_INT8_ARRAY,          /* u.array (typed_array) */
  JS_CLASS_UINT8_ARRAY,         /* u.array (typed_array) */
  JS_CLASS_INT16_ARRAY,         /* u.array (typed_array) */
  JS_CLASS_UINT16_ARRAY,        /* u.array (typed_array) */
  JS_CLASS_INT32_ARRAY,         /* u.array (typed_array) */
  JS_CLASS_UINT32_ARRAY,        /* u.array (typed_array) */
#ifdef CONFIG_BIGNUM
  JS_CLASS_BIG_INT64_ARRAY,  /* u.array (typed_array) */
  JS_CLASS_BIG_UINT64_ARRAY, /* u.array (typed_array) */
#endif
  JS_CLASS_FLOAT32_ARRAY, /* u.array (typed_array) */
  JS_CLASS_FLOAT64_ARRAY, /* u.array (typed_array) */
  JS_CLASS_DATAVIEW,      /* u.typed_array */
#ifdef CONFIG_BIGNUM
  JS_CLASS_BIG_INT,      /* u.object_data */
  JS_CLASS_BIG_FLOAT,    /* u.object_data */
  JS_CLASS_FLOAT_ENV,    /* u.float_env */
  JS_CLASS_BIG_DECIMAL,  /* u.object_data */
  JS_CLASS_OPERATOR_SET, /* u.operator_set */
#endif
  JS_CLASS_MAP,                      /* u.map_state */
  JS_CLASS_SET,                      /* u.map_state */
  JS_CLASS_WEAKMAP,                  /* u.map_state */
  JS_CLASS_WEAKSET,                  /* u.map_state */
  JS_CLASS_MAP_ITERATOR,             /* u.map_iterator_data */
  JS_CLASS_SET_ITERATOR,             /* u.map_iterator_data */
  JS_CLASS_ARRAY_ITERATOR,           /* u.array_iterator_data */
  JS_CLASS_STRING_ITERATOR,          /* u.array_iterator_data */
  JS_CLASS_REGEXP_STRING_ITERATOR,   /* u.regexp_string_iterator_data */
  JS_CLASS_GENERATOR,                /* u.generator_data */
  JS_CLASS_PROXY,                    /* u.proxy_data */
  JS_CLASS_PROMISE,                  /* u.promise_data */
  JS_CLASS_PROMISE_RESOLVE_FUNCTION, /* u.promise_function_data */
  JS_CLASS_PROMISE_REJECT_FUNCTION,  /* u.promise_function_data */
  JS_CLASS_ASYNC_FUNCTION,           /* u.func */
  JS_CLASS_ASYNC_FUNCTION_RESOLVE,   /* u.async_function_data */
  JS_CLASS_ASYNC_FUNCTION_REJECT,    /* u.async_function_data */
  JS_CLASS_ASYNC_FROM_SYNC_ITERATOR, /* u.async_from_sync_iterator_data */
  JS_CLASS_ASYNC_GENERATOR_FUNCTION, /* u.func */
  JS_CLASS_ASYNC_GENERATOR,          /* u.async_generator_data */

  JS_CLASS_INIT_COUNT, /* last entry for predefined classes */
};

#ifdef __cplusplus
extern "C" {
#endif

static inline bool __JS_AtomIsConst(JSAtom v) {
#if defined(DUMP_LEAKS) && DUMP_LEAKS > 1
  return (int32_t)v <= 0;
#else
  return (int32_t)v < JS_ATOM_END;
#endif
}

uint16_t* JS_ToUnicode(JSContext* ctx, JSValueConst value, uint32_t* length);
JSValue JS_NewUnicodeString(JSContext* ctx, const uint16_t* code, uint32_t length);
JSValue JS_NewRawUTF8String(JSContext* ctx, const uint8_t* code, uint32_t length);
JSAtom JS_NewUnicodeAtom(JSContext* ctx, const uint16_t* code, uint32_t length);
JSClassID JSValueGetClassId(JSValue);
bool JS_IsProxy(JSValue value);
bool JS_IsPromise(JSValue value);
bool JS_IsArrayBuffer(JSValue value);
bool JS_IsArrayBufferView(JSValue value);
bool JS_HasClassId(JSRuntime* runtime, JSClassID classId);
int JS_AtomIs8Bit(JSRuntime* runtime, JSAtom atom);
const uint8_t* JS_AtomRawCharacter8(JSRuntime* runtime, JSAtom atom);
const uint16_t* JS_AtomRawCharacter16(JSRuntime* runtime, JSAtom atom);
int JS_FindCharacterInAtom(JSRuntime* runtime, JSAtom atom, bool (*CharacterMatchFunction)(char));
int JS_FindWCharacterInAtom(JSRuntime* runtime, JSAtom atom, bool (*CharacterMatchFunction)(uint16_t));
JSValue JS_GetProxyTarget(JSValue value);
JSGCPhaseEnum JS_GetEnginePhase(JSRuntime* runtime);

static inline bool JS_AtomIsTaggedInt(JSAtom v) {
  return (v & JS_ATOM_TAG_INT) != 0;
}

static inline JSAtom JS_AtomFromUInt32(uint32_t v) {
  return v | JS_ATOM_TAG_INT;
}

static inline uint32_t JS_AtomToUInt32(JSAtom atom) {
  return atom & ~JS_ATOM_TAG_INT;
}

#ifdef __cplusplus
}
#endif

webf::StringView JSAtomToStringView(JSRuntime* runtime, JSAtom atom);

#endif  // BRIDGE_QJS_PATCH_H
