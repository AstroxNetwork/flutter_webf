// Generated by WebF TSDL, don't edit this file directly.
// Generate command: node scripts/generate_binding_code.js
// clang-format off
/*
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */
#ifndef WEBF_CORE_WEBF_API_PLUGIN_API_GESTURE_EVENT_INIT_H_
#define WEBF_CORE_WEBF_API_PLUGIN_API_GESTURE_EVENT_INIT_H_
#include <stdint.h>
#include "webf_value.h"
namespace webf {
struct WebFGestureEventInit {
  int32_t bubbles;
  int32_t cancelable;
  int32_t composed;
  const char* state;
  const char* direction;
  double delta_x;
  double delta_y;
  double velocity_x;
  double velocity_y;
  double scale;
  double rotation;
};
}  // namespace webf
#endif  // WEBF_CORE_WEBF_API_PLUGIN_API_GESTURE_EVENT_INIT_H_
