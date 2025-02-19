import 'package:device_client/components/app_drawer.dart';
import 'package:device_client/components/display.dart';
import 'package:device_client/components/keypad.dart';
import 'package:device_client/components/nav_bar.dart';
import 'package:device_client/model/app_data.dart';
import 'package:device_client/view/current_data_page.dart';
import 'package:device_client/view/files_page.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
// import 'package:web/web.dart' as html;
// TODO: Figure out how to link to website without having interference with Flutter widget tests

class MyHomePage extends StatefulWidget {
  const MyHomePage({required this.title, super.key});

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  Widget appBody(BuildContext context) {
    return Center(
      child: Column(
        children: <Widget>[
          Display(context: context),
          Flexible(
            child: Keypad(context: context),
          ),
        ],
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    final List<Widget> children = [
      appBody(context),
      CurrentData(context: context),
      Files(context: context),
    ];
    return Consumer<AppData>(
      builder: (context, appData, child) {
        return Scaffold(
          appBar: AppBar(
            title: Text(
              '${widget.title}: ${appData.currentTank.name}',
            ),
            // actions: [
            //   _tankMonitorRedirect(),
            // ],
          ),
          drawer: AppDrawer(context: context),
          body: children[appData.currentIndex],
          bottomNavigationBar: NavBar(context: context),
        );
      },
    );
  }

  //   Padding _tankMonitorRedirect() {
  //   return Padding(
  //     padding: const EdgeInsets.only(right: 8.0),
  //     child: TextButton(
  //       onPressed: () {
  //         const tankMonitorUrl = 'https://oap.cs.wallawalla.edu/';
  //         html.window.open(tankMonitorUrl, '_self');
  //       },
  //       child: Row(
  //         mainAxisSize: MainAxisSize.min,
  //         children: const [
  //           Text(
  //             'Go to Tank Monitor',
  //             style: TextStyle(fontWeight: FontWeight.bold),
  //           ),
  //           SizedBox(width: 8),
  //           Icon(Icons.swap_horiz),
  //         ],
  //       ),
  //     ),
  //   );
  // }
}
