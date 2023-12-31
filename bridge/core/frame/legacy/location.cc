/*
 * Copyright (C) 2019-2022 The Kraken authors. All rights reserved.
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */
#include "location.h"
#include "core/executing_context.h"

namespace webf {

void Location::__webf_location_reload__(ExecutingContext* context, ExceptionState& exception_state) {
  if (context->dartMethodPtr()->reloadApp == nullptr) {
    exception_state.ThrowException(context->ctx(), ErrorType::InternalError,
                                   "Failed to execute 'reload': dart method (reloadApp) is not registered.");
    return;
  }

  context->FlushUICommand();
  context->dartMethodPtr()->reloadApp(context->contextId());
}

}  // namespace webf
