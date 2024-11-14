// Generated by WebF TSDL, don't edit this file directly.
// Generate command: node scripts/generate_binding_code.js
/*
* Copyright (C) 2022-present The WebF authors. All rights reserved.
*/
use std::ffi::*;
use crate::*;
#[repr(C)]
pub struct GestureEventInit {
  pub bubbles: i32,
  pub cancelable: i32,
  pub composed: i32,
  pub state: *const c_char,
  pub direction: *const c_char,
  pub delta_x: c_double,
  pub delta_y: c_double,
  pub velocity_x: c_double,
  pub velocity_y: c_double,
  pub scale: c_double,
  pub rotation: c_double,
}
