// Generated by WebF TSDL, don't edit this file directly.
// Generate command: node scripts/generate_binding_code.js
// clang-format off
/*
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */
#ifndef WEBF_CORE_WEBF_API_PLUGIN_API_FOCUS_EVENT_H_
#define WEBF_CORE_WEBF_API_PLUGIN_API_FOCUS_EVENT_H_
#include <stdint.h>
#include "rust_readable.h"
#include "script_value_ref.h"
#include "ui_event.h"
namespace webf {
class EventTarget;
typedef struct EventTargetPublicMethods EventTargetPublicMethods;
class SharedExceptionState;
class ExecutingContext;
class FocusEvent;
typedef struct ScriptValueRef ScriptValueRef;
using PublicFocusEventGetRelatedTarget = WebFValue<EventTarget, EventTargetPublicMethods> (*)(FocusEvent*);
struct FocusEventPublicMethods : public WebFPublicMethods {
  static WebFValue<EventTarget, EventTargetPublicMethods> RelatedTarget(FocusEvent* focus_event);
  double version{1.0};
  UIEventPublicMethods ui_event;
  PublicFocusEventGetRelatedTarget focus_event_get_related_target{RelatedTarget};
};
}  // namespace webf
#endif  // WEBF_CORE_WEBF_API_PLUGIN_API_FOCUS_EVENT_H_
