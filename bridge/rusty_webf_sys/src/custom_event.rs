// Generated by WebF TSDL, don't edit this file directly.
// Generate command: node scripts/generate_binding_code.js
/*
* Copyright (C) 2022-present The WebF authors. All rights reserved.
*/
use std::ffi::*;
use crate::*;
#[repr(C)]
pub struct CustomEventRustMethods {
  pub version: c_double,
  pub event: EventRustMethods,
  pub detail: extern "C" fn(ptr: *const OpaquePtr) -> RustValue<ScriptValueRefRustMethods>,
  pub init_custom_event: extern "C" fn(ptr: *const OpaquePtr, *const c_char, i32, i32, *const OpaquePtr, exception_state: *const OpaquePtr) -> c_void,
}
pub struct CustomEvent {
  pub event: Event,
  method_pointer: *const CustomEventRustMethods,
}
impl CustomEvent {
  pub fn initialize(ptr: *const OpaquePtr, context: *const ExecutingContext, method_pointer: *const CustomEventRustMethods, status: *const RustValueStatus) -> CustomEvent {
    unsafe {
      CustomEvent {
        event: Event::initialize(
          ptr,
          context,
          &(method_pointer).as_ref().unwrap().event,
          status,
        ),
        method_pointer,
      }
    }
  }
  pub fn ptr(&self) -> *const OpaquePtr {
    self.event.ptr()
  }
  pub fn context<'a>(&self) -> &'a ExecutingContext {
    self.event.context()
  }
  pub fn detail(&self) -> ScriptValueRef {
    let value = unsafe {
      ((*self.method_pointer).detail)(self.ptr())
    };
    ScriptValueRef::initialize(value.value, self.context(), value.method_pointer)
  }
  pub fn init_custom_event(&self, type_: &str, can_bubble: bool, cancelable: bool, detail: &ScriptValueRef, exception_state: &ExceptionState) -> Result<(), String> {
    unsafe {
      ((*self.method_pointer).init_custom_event)(self.ptr(), CString::new(type_).unwrap().as_ptr(), i32::from(can_bubble), i32::from(cancelable), detail.ptr, exception_state.ptr);
    };
    if exception_state.has_exception() {
      return Err(exception_state.stringify(self.context()));
    }
    Ok(())
  }
}
pub trait CustomEventMethods: EventMethods {
  fn detail(&self) -> ScriptValueRef;
  fn init_custom_event(&self, type_: &str, can_bubble: bool, cancelable: bool, detail: &ScriptValueRef, exception_state: &ExceptionState) -> Result<(), String>;
  fn as_custom_event(&self) -> &CustomEvent;
}
impl CustomEventMethods for CustomEvent {
  fn detail(&self) -> ScriptValueRef {
    self.detail()
  }
  fn init_custom_event(&self, type_: &str, can_bubble: bool, cancelable: bool, detail: &ScriptValueRef, exception_state: &ExceptionState) -> Result<(), String> {
    self.init_custom_event(type_, can_bubble, cancelable, detail, exception_state)
  }
  fn as_custom_event(&self) -> &CustomEvent {
    self
  }
}
impl EventMethods for CustomEvent {
  fn bubbles(&self) -> bool {
    self.event.bubbles()
  }
  fn cancel_bubble(&self) -> bool {
    self.event.cancel_bubble()
  }
  fn set_cancel_bubble(&self, value: bool, exception_state: &ExceptionState) -> Result<(), String> {
    self.event.set_cancel_bubble(value, exception_state)
  }
  fn cancelable(&self) -> bool {
    self.event.cancelable()
  }
  fn current_target(&self) -> EventTarget {
    self.event.current_target()
  }
  fn default_prevented(&self) -> bool {
    self.event.default_prevented()
  }
  fn src_element(&self) -> EventTarget {
    self.event.src_element()
  }
  fn target(&self) -> EventTarget {
    self.event.target()
  }
  fn is_trusted(&self) -> bool {
    self.event.is_trusted()
  }
  fn time_stamp(&self) -> f64 {
    self.event.time_stamp()
  }
  fn type_(&self) -> String {
    self.event.type_()
  }
  fn init_event(&self, type_: &str, bubbles: bool, cancelable: bool, exception_state: &ExceptionState) -> Result<(), String> {
    self.event.init_event(type_, bubbles, cancelable, exception_state)
  }
  fn prevent_default(&self, exception_state: &ExceptionState) -> Result<(), String> {
    self.event.prevent_default(exception_state)
  }
  fn stop_immediate_propagation(&self, exception_state: &ExceptionState) -> Result<(), String> {
    self.event.stop_immediate_propagation(exception_state)
  }
  fn stop_propagation(&self, exception_state: &ExceptionState) -> Result<(), String> {
    self.event.stop_propagation(exception_state)
  }
  fn as_event(&self) -> &Event {
    &self.event
  }
}
