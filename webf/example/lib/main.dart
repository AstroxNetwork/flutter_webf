/*
 * Copyright (C) 2019-2022 The Kraken authors. All rights reserved.
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */
import 'dart:developer' as dev;

import 'package:flutter/material.dart';
import 'package:webf/webf.dart';
import 'package:webf/devtools.dart';
import 'package:webf_callf/webf_callf.dart';
import 'package:media_kit/media_kit.dart';
import 'package:webf_websocket/webf_websocket.dart';
import 'package:webf_audio_player/webf_audio_player.dart';

void main() {
  WebFCallF.register({});
  WebFWebSocket.initialize();
  MediaKit.ensureInitialized();
  AudioPlayerModule.register();

  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Kraken Browser',
      // theme: ThemeData.dark(),
      debugShowCheckedModeBanner: false,
      home: MyBrowser(),
    );
  }
}

class MyBrowser extends StatefulWidget {
  MyBrowser({Key? key, this.title}) : super(key: key);

  // This widget is the home page of your application. It is stateful, meaning
  // that it has a State object (defined below) that contains fields that affect
  // how it looks.

  // This class is the configuration for the state. It holds the values (in this
  // case the title) provided by the parent (in this case the App widget) and
  // used by the build method of the State. Fields in a Widget subclass are
  // always marked "final".

  final String? title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyBrowser> {
  final TextEditingController textEditingController = TextEditingController();
  OutlineInputBorder outlineBorder = OutlineInputBorder(
    borderSide: BorderSide(color: Colors.transparent, width: 0.0),
    borderRadius: const BorderRadius.all(
      Radius.circular(20.0),
    ),
  );

  void print(Object msg, {Object? e, StackTrace? s, int level = 0}) {
    dev.log(msg.toString(), name: 'example', error: e, stackTrace: s, level: level);
  }

  @override
  Widget build(BuildContext context) {
    final MediaQueryData queryData = MediaQuery.of(context);

    WebF? _kraken;
    AppBar appBar = AppBar(
      backgroundColor: Colors.black87,
      titleSpacing: 10.0,
      title: Container(
        height: 40.0,
        child: TextField(
          controller: textEditingController,
          onSubmitted: (value) {
            textEditingController.text = value;
            _kraken?.load(WebFBundle.fromUrl(value));
          },
          decoration: InputDecoration(
            hintText: 'Enter URL',
            hintStyle: TextStyle(color: Colors.black54, fontSize: 16.0),
            contentPadding: const EdgeInsets.all(10.0),
            filled: true,
            fillColor: Colors.grey,
            border: outlineBorder,
            focusedBorder: outlineBorder,
            enabledBorder: outlineBorder,
          ),
          style: TextStyle(color: Colors.black, fontSize: 16.0),
        ),
      ),
      // Here we take the value from the MyHomePage object that was created by
      // the App.build method, and use it to set our appbar title.
    );

    final Size viewportSize = queryData.size;
    return Scaffold(
      resizeToAvoidBottomInset: false,
      appBar: appBar,
      body: _kraken ??= WebF(
        resizeToAvoidBottomInsets: false,
        devToolsService: ChromeDevToolsService(),
        onControllerCreated: (controller) {
          controller.onJSLog = (l, s) {
            print('onJSLog: $s', level: l);
          };
          controller.onLoadError = (e, s) {
            print('onLoadError', e: e, s: s);
          };
        },
        viewportWidth: viewportSize.width - queryData.padding.horizontal,
        viewportHeight: viewportSize.height - appBar.preferredSize.height - queryData.padding.vertical,
        bundle: WebFBundle.fromUrl('assets:assets/bundle.html'),
        onJSError: (e) => print('onJSError', e: e),
      ),
    );
  }
}
