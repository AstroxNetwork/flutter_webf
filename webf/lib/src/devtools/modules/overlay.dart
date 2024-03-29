/*
 * Copyright (C) 2019-2022 The Kraken authors. All rights reserved.
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */

import 'dart:ffi';
import 'package:webf/dom.dart';
import 'package:webf/devtools.dart';
import 'package:webf/launcher.dart';

class InspectOverlayModule extends UIInspectorModule {
  @override
  String get name => 'Overlay';

  Document get document => devtoolsService.controller!.view.document;
  WebFViewController get view => devtoolsService.controller!.view;
  InspectOverlayModule(DevToolsService devtoolsService) : super(devtoolsService);

  @override
  void receiveFromFrontend(int? id, String method, Map<String, dynamic>? params) {
    switch (method) {
      case 'highlightNode':
        onHighlightNode(id, params!);
        break;
      case 'hideHighlight':
        onHideHighlight(id);
        break;
    }
  }

  Element? _highlightElement;

  /// https://chromedevtools.github.io/devtools-protocol/tot/Overlay/#method-highlightNode
  void onHighlightNode(int? id, Map<String, dynamic> params) {
    _highlightElement?.debugHideHighlight();

    int nodeId = params['nodeId'];
    Element? element = view.getBindingObject<Element>(Pointer.fromAddress(nodeId));

    if (element != null) {
      element.debugHighlight();
      _highlightElement = element;
    }
    sendToFrontend(id, null);
  }

  void onHideHighlight(int? id) {
    _highlightElement?.debugHideHighlight();
    _highlightElement = null;
    sendToFrontend(id, null);
  }
}
