// Generated by WebF TSDL, don't edit this file directly.
// Generate command: node scripts/generate_binding_code.js
/*
* Copyright (C) 2022-present The WebF authors. All rights reserved.
*/
use std::ffi::*;
use crate::*;
#[repr(C)]
pub struct AnimationEventRustMethods {
  pub version: c_double,
  pub event: EventRustMethods,
  pub animation_name: extern "C" fn(ptr: *const OpaquePtr) -> *const c_char,
  pub dup_animation_name: extern "C" fn(ptr: *const OpaquePtr) -> *const c_char,
  pub elapsed_time: extern "C" fn(ptr: *const OpaquePtr) -> c_double,
  pub pseudo_element: extern "C" fn(ptr: *const OpaquePtr) -> *const c_char,
  pub dup_pseudo_element: extern "C" fn(ptr: *const OpaquePtr) -> *const c_char,
}
pub struct AnimationEvent {
  pub event: Event,
  method_pointer: *const AnimationEventRustMethods,
}
impl AnimationEvent {
  pub fn initialize(ptr: *const OpaquePtr, context: *const ExecutingContext, method_pointer: *const AnimationEventRustMethods, status: *const RustValueStatus) -> AnimationEvent {
    unsafe {
      AnimationEvent {
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
  pub fn animation_name(&self) -> String {
    let value = unsafe {
      ((*self.method_pointer).animation_name)(self.ptr())
    };
    let value = unsafe { std::ffi::CStr::from_ptr(value) };
    value.to_str().unwrap().to_string()
  }
  pub fn elapsed_time(&self) -> f64 {
    let value = unsafe {
      ((*self.method_pointer).elapsed_time)(self.ptr())
    };
    value
  }
  pub fn pseudo_element(&self) -> String {
    let value = unsafe {
      ((*self.method_pointer).pseudo_element)(self.ptr())
    };
    let value = unsafe { std::ffi::CStr::from_ptr(value) };
    value.to_str().unwrap().to_string()
  }
}
pub trait AnimationEventMethods: EventMethods {
  fn animation_name(&self) -> String;
  fn elapsed_time(&self) -> f64;
  fn pseudo_element(&self) -> String;
  fn as_animation_event(&self) -> &AnimationEvent;
}
impl AnimationEventMethods for AnimationEvent {
  fn animation_name(&self) -> String {
    self.animation_name()
  }
  fn elapsed_time(&self) -> f64 {
    self.elapsed_time()
  }
  fn pseudo_element(&self) -> String {
    self.pseudo_element()
  }
  fn as_animation_event(&self) -> &AnimationEvent {
    self
  }
}
impl EventMethods for AnimationEvent {
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
