import 'package:flutter/material.dart';
import 'package:log_file_client/pages/home_page.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Tank Monitor',
      theme: ThemeData(
        scaffoldBackgroundColor: const Color.fromARGB(255, 215, 215, 215),
        colorScheme: ColorScheme.fromSeed(
          seedColor: const Color.fromARGB(255, 21, 98, 231),
        ),
        useMaterial3: true,
      ),
      home: const HomePage(),
    );
  }
}
