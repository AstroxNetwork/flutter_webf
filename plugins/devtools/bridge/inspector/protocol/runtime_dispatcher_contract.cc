/*
 * Copyright (C) 2020-present The Kraken authors. All rights reserved.
 */

#include "inspector/protocol/runtime_dispatcher_contract.h"
#include "inspector/protocol/runtime_dispatcher_impl.h"

namespace kraken {
namespace debugger {
void RuntimeDispatcherContract::wire(kraken::debugger::UberDispatcher *uber,
                                     kraken::debugger::RuntimeBackend *backend) {
  std::unique_ptr<RuntimeDispatcherImpl> dispatcher(new RuntimeDispatcherImpl(uber->channel(), backend));
  uber->setupRedirects(dispatcher->redirects());
  uber->registerBackend("Runtime", std::move(dispatcher));
}
} // namespace debugger
} // namespace kraken
