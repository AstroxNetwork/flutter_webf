/*
 * Copyright (C) 2019-2022 The Kraken authors. All rights reserved.
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */
import 'dart:ui' as ui;

import 'package:flutter/rendering.dart';
import 'package:webf/rendering.dart';

mixin RenderOpacityMixin on RenderBoxModelBase {
  bool opacityAlwaysNeedsCompositing() => alpha != 0 && alpha != 255;

  int? _alpha;

  int get alpha {
    _alpha ??= ui.Color.getAlphaFromOpacity(renderStyle.opacity);
    return _alpha ?? ui.Color.getAlphaFromOpacity(1.0);
  }

  set alpha(int? value) {
    _alpha = value;
  }

  final LayerHandle<OpacityLayer> _opacityLayer = LayerHandle<OpacityLayer>();

  void disposeOpacityLayer() {
    _opacityLayer.layer = null;
  }

  void paintOpacity(PaintingContext context, Offset offset, PaintingContextCallback callback) {
    if (alpha == 255) {
      _opacityLayer.layer = null;
      // No need to keep the layer. We'll create a new one if necessary.
      callback(context, offset);
      return;
    }

    _opacityLayer.layer = context.pushOpacity(offset, alpha, callback, oldLayer: _opacityLayer.layer);
  }

  void debugOpacityProperties(DiagnosticPropertiesBuilder properties) {
    if (alpha != 0 && alpha != 255) properties.add(DiagnosticsProperty('alpha', alpha));
  }
}
