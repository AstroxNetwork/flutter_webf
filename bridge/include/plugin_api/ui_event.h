// Generated by WebF TSDL, don't edit this file directly.
// Generate command: node scripts/generate_binding_code.js
// clang-format off
/*
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */
#ifndef WEBF_CORE_WEBF_API_PLUGIN_API_UI_EVENT_H_
#define WEBF_CORE_WEBF_API_PLUGIN_API_UI_EVENT_H_
#include <stdint.h>
#include "rust_readable.h"
#include "script_value_ref.h"
#include "event.h"
namespace webf {
class Window;
typedef struct WindowPublicMethods WindowPublicMethods;
class SharedExceptionState;
class ExecutingContext;
class UIEvent;
typedef struct ScriptValueRef ScriptValueRef;
using PublicUIEventGetDetail = double (*)(UIEvent*);
using PublicUIEventGetView = WebFValue<Window, WindowPublicMethods> (*)(UIEvent*);
using PublicUIEventGetWhich = double (*)(UIEvent*);
struct UIEventPublicMethods : public WebFPublicMethods {
  static double Detail(UIEvent* ui_event);
  static WebFValue<Window, WindowPublicMethods> View(UIEvent* ui_event);
  static double Which(UIEvent* ui_event);
  double version{1.0};
  EventPublicMethods event;
  PublicUIEventGetDetail ui_event_get_detail{Detail};
  PublicUIEventGetView ui_event_get_view{View};
  PublicUIEventGetWhich ui_event_get_which{Which};
};
}  // namespace webf
#endif  // WEBF_CORE_WEBF_API_PLUGIN_API_UI_EVENT_H_
