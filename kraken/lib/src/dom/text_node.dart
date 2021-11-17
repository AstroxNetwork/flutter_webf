/*
 * Copyright (C) 2019-present Alibaba Inc. All rights reserved.
 * Author: Kraken Team.
 */

import 'dart:ffi';

import 'package:flutter/rendering.dart';
import 'package:kraken/bridge.dart';
import 'package:kraken/css.dart';
import 'package:kraken/dom.dart';
import 'package:kraken/rendering.dart';

final RegExp _whiteSpaceReg = RegExp(r'\s+');
const String WHITE_SPACE_CHAR = ' ';
const String NEW_LINE_CHAR = '\n';
const String RETURN_CHAR = '\r';
const String TAB_CHAR = '\t';

class TextNode extends Node {
  TextNode(int targetId, Pointer<NativeEventTarget> nativeEventTarget, this._data, ElementManager elementManager)
      : super(NodeType.TEXT_NODE, targetId, nativeEventTarget, elementManager);

  RenderTextBox? _renderTextBox;

  static const String NORMAL_SPACE = '\u0020';
  // The text string.
  String? _data;
  String get data {
    String? _d = _data;

    if (_d == null || _d.isEmpty) return '';

    WhiteSpace whiteSpace = CSSText.getWhiteSpace(parentElement!.style);

    /// https://drafts.csswg.org/css-text-3/#propdef-white-space
    /// The following table summarizes the behavior of the various white-space values:
    //
    //       New lines / Spaces and tabs / Text wrapping / End-of-line spaces
    // normal    Collapse  Collapse  Wrap     Remove
    // nowrap    Collapse  Collapse  No wrap  Remove
    // pre       Preserve  Preserve  No wrap  Preserve
    // pre-wrap  Preserve  Preserve  Wrap     Hang
    // pre-line  Preserve  Collapse  Wrap     Remove
    // break-spaces  Preserve  Preserve  Wrap  Wrap
    if (whiteSpace == WhiteSpace.pre ||
        whiteSpace == WhiteSpace.preLine ||
        whiteSpace == WhiteSpace.preWrap ||
        whiteSpace == WhiteSpace.breakSpaces) {
      return whiteSpace == WhiteSpace.preLine ? _collapseWhitespace(_d) : _d;
    } else {
      String collapsedData = _collapseWhitespace(_d);
      // TODO:
      // Remove the leading space while prev element have space too:
      //   <p><span>foo </span> bar</p>
      // Refs:
      //   https://github.com/WebKit/WebKit/blob/6a970b217d59f36e64606ed03f5238d572c23c48/Source/WebCore/layout/inlineformatting/InlineLineBuilder.cpp#L295

      if (previousSibling == null) {
        collapsedData = collapsedData.trimLeft();
      }

      if (nextSibling == null) {
        collapsedData = collapsedData.trimRight();
      }

      return collapsedData;
    }
  }

  set data(String? newData) {
    assert(newData != null);

    String lastData = _data!;
    _data = newData;

    // Empty string of textNode should not attach to the render tree.
    if (lastData != '' && newData == '') {
      detach();
    } else if (lastData == '' && newData != '') {
      attachTo(parentElement!);
    }

    updateTextStyle();
  }

  @override
  String get nodeName => '#text';

  @override
  RenderObject? get renderer => _renderTextBox;

  void updateTextStyle() {
    if (isRendererAttached) {
      _updateTextStyle();
    }
  }

  @override
  handleJSCall(String method, List argv) {}

  void _setTextSizeType(BoxSizeType width, BoxSizeType height) {
    RenderTextBox? renderTextBox = _renderTextBox;
    if (renderTextBox == null) return;

    // migrate element's size type to RenderTextBox
    renderTextBox.widthSizeType = width;
    renderTextBox.heightSizeType = height;
  }

  void _updateTextStyle() {
    Element _parentElement = parentElement!;
    RenderTextBox renderTextBox = _renderTextBox!;

    // parentNode must be an element.
    renderTextBox.style = _parentElement.style;
    renderTextBox.text = CSSTextMixin.createTextSpan(data, parentElement: parentElement);
    // Update paragraph line height
    KrakenRenderParagraph renderParagraph = renderTextBox.child as KrakenRenderParagraph;
    renderParagraph.lineHeight = (_parentElement.renderBoxModel?.renderStyle.lineHeight);
    renderParagraph.markNeedsLayout();

    _setTextNodeProperties(_parentElement.style);
    RenderBoxModel? parentRenderBoxModel = _parentElement.renderBoxModel;
    _setTextSizeType(parentRenderBoxModel!.widthSizeType, parentRenderBoxModel.heightSizeType);
  }

  void _setTextNodeProperties(CSSStyleDeclaration style) {
    Element _parentElement = parentElement!;
    RenderTextBox renderTextBox = _renderTextBox!;

    renderTextBox.whiteSpace = CSSText.getWhiteSpace(_parentElement.style);
    renderTextBox.overflow = CSSText.getTextOverflow(style: _parentElement.style);
    renderTextBox.maxLines = CSSText.getLineClamp(_parentElement.style);
  }

  // Attach renderObject of current node to parent
  @override
  void attachTo(Element parent, { RenderBox? after }) {
    if (_data != '') {
      willAttachRenderer();

      RenderLayoutBox? parentRenderLayoutBox;
      if (parent.scrollingContentLayoutBox != null) {
        parentRenderLayoutBox = parent.scrollingContentLayoutBox!;
      } else {
        parentRenderLayoutBox = (parent.renderBoxModel as RenderLayoutBox?)!;
      }

      RenderTextBox renderTextBox = _renderTextBox!;

      parentRenderLayoutBox.insert(renderTextBox, after: after);
      _setTextSizeType(parentRenderLayoutBox.widthSizeType, parentRenderLayoutBox.heightSizeType);

      didAttachRenderer();
    }
  }

  // Detach renderObject of current node from parent
  @override
  void detach() {
    willDetachRenderer();

    if (isRendererAttached) {
      RenderTextBox renderTextBox = _renderTextBox!;
      ContainerRenderObjectMixin parent = renderTextBox.parent as ContainerRenderObjectMixin;
      parent.remove(renderTextBox);
    }

    didDetachRenderer();
    _renderTextBox = null;
  }

  @override
  void willAttachRenderer() {
    createRenderer();
    Element _parentElement = parentElement!;
    RenderTextBox renderTextBox = _renderTextBox!;

    CSSStyleDeclaration parentStyle = _parentElement.style;
    // Text node whitespace collapse relate to siblings,
    // so text should update when appending
    renderTextBox.text = CSSTextMixin.createTextSpan(data, parentElement: parentElement);
    // TextNode's style is inherited from parent style
    renderTextBox.style = parentStyle;
    // Update paragraph line height
    KrakenRenderParagraph renderParagraph = renderTextBox.child as KrakenRenderParagraph;
    renderParagraph.lineHeight = (_parentElement.renderBoxModel?.renderStyle.lineHeight);

    _setTextNodeProperties(_parentElement.style);
  }

  @override
  RenderObject createRenderer() {
    if (renderer != null) {
      return renderer!;
    }

    InlineSpan text = CSSTextMixin.createTextSpan(_data!, parentElement: parentElement);
    RenderTextBox renderTextBox = _renderTextBox = RenderTextBox(text,
      style: null,
    );
    return renderTextBox;
  }

  @override
  void dispose() {
    super.dispose();

    detach();

    assert(_renderTextBox == null);
  }
}

// '  a b  c   \n' => ' a b c '
String _collapseWhitespace(String string) {
  return string.replaceAll(_whiteSpaceReg, WHITE_SPACE_CHAR);
}
