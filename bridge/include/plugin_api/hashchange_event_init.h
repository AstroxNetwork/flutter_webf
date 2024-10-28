// Generated by WebF TSDL, don't edit this file directly.
// Generate command: node scripts/generate_binding_code.js
// clang-format off
/*
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */
#ifndef WEBF_CORE_WEBF_API_PLUGIN_API_HASHCHANGE_EVENT_INIT_H_
#define WEBF_CORE_WEBF_API_PLUGIN_API_HASHCHANGE_EVENT_INIT_H_
#include <stdint.h>
#include "webf_value.h"
namespace webf {
struct WebFHashchangeEventInit {
  int32_t bubbles;
  int32_t cancelable;
  int32_t composed;
  const char* old_url;
  const char* new_url;
};
}  // namespace webf
#endif  // WEBF_CORE_WEBF_API_PLUGIN_API_HASHCHANGE_EVENT_INIT_H_
