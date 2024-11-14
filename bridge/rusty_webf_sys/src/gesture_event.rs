// Generated by WebF TSDL, don't edit this file directly.
// Generate command: node scripts/generate_binding_code.js
/*
* Copyright (C) 2022-present The WebF authors. All rights reserved.
*/
use std::ffi::*;
use crate::*;
#[repr(C)]
pub struct GestureEventRustMethods {
  pub version: c_double,
  pub event: EventRustMethods,
  pub state: extern "C" fn(ptr: *const OpaquePtr) -> *const c_char,
  pub dup_state: extern "C" fn(ptr: *const OpaquePtr) -> *const c_char,
  pub direction: extern "C" fn(ptr: *const OpaquePtr) -> *const c_char,
  pub dup_direction: extern "C" fn(ptr: *const OpaquePtr) -> *const c_char,
  pub delta_x: extern "C" fn(ptr: *const OpaquePtr) -> c_double,
  pub delta_y: extern "C" fn(ptr: *const OpaquePtr) -> c_double,
  pub velocity_x: extern "C" fn(ptr: *const OpaquePtr) -> c_double,
  pub velocity_y: extern "C" fn(ptr: *const OpaquePtr) -> c_double,
  pub scale: extern "C" fn(ptr: *const OpaquePtr) -> c_double,
  pub rotation: extern "C" fn(ptr: *const OpaquePtr) -> c_double,
}
pub struct GestureEvent {
  pub event: Event,
  method_pointer: *const GestureEventRustMethods,
}
impl GestureEvent {
  pub fn initialize(ptr: *const OpaquePtr, context: *const ExecutingContext, method_pointer: *const GestureEventRustMethods, status: *const RustValueStatus) -> GestureEvent {
    unsafe {
      GestureEvent {
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
  pub fn state(&self) -> String {
    let value = unsafe {
      ((*self.method_pointer).state)(self.ptr())
    };
    let value = unsafe { std::ffi::CStr::from_ptr(value) };
    value.to_str().unwrap().to_string()
  }
  pub fn direction(&self) -> String {
    let value = unsafe {
      ((*self.method_pointer).direction)(self.ptr())
    };
    let value = unsafe { std::ffi::CStr::from_ptr(value) };
    value.to_str().unwrap().to_string()
  }
  pub fn delta_x(&self) -> f64 {
    let value = unsafe {
      ((*self.method_pointer).delta_x)(self.ptr())
    };
    value
  }
  pub fn delta_y(&self) -> f64 {
    let value = unsafe {
      ((*self.method_pointer).delta_y)(self.ptr())
    };
    value
  }
  pub fn velocity_x(&self) -> f64 {
    let value = unsafe {
      ((*self.method_pointer).velocity_x)(self.ptr())
    };
    value
  }
  pub fn velocity_y(&self) -> f64 {
    let value = unsafe {
      ((*self.method_pointer).velocity_y)(self.ptr())
    };
    value
  }
  pub fn scale(&self) -> f64 {
    let value = unsafe {
      ((*self.method_pointer).scale)(self.ptr())
    };
    value
  }
  pub fn rotation(&self) -> f64 {
    let value = unsafe {
      ((*self.method_pointer).rotation)(self.ptr())
    };
    value
  }
}
pub trait GestureEventMethods: EventMethods {
  fn state(&self) -> String;
  fn direction(&self) -> String;
  fn delta_x(&self) -> f64;
  fn delta_y(&self) -> f64;
  fn velocity_x(&self) -> f64;
  fn velocity_y(&self) -> f64;
  fn scale(&self) -> f64;
  fn rotation(&self) -> f64;
  fn as_gesture_event(&self) -> &GestureEvent;
}
impl GestureEventMethods for GestureEvent {
  fn state(&self) -> String {
    self.state()
  }
  fn direction(&self) -> String {
    self.direction()
  }
  fn delta_x(&self) -> f64 {
    self.delta_x()
  }
  fn delta_y(&self) -> f64 {
    self.delta_y()
  }
  fn velocity_x(&self) -> f64 {
    self.velocity_x()
  }
  fn velocity_y(&self) -> f64 {
    self.velocity_y()
  }
  fn scale(&self) -> f64 {
    self.scale()
  }
  fn rotation(&self) -> f64 {
    self.rotation()
  }
  fn as_gesture_event(&self) -> &GestureEvent {
    self
  }
}
impl EventMethods for GestureEvent {
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
