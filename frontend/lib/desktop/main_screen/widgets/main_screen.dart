import 'package:flutter/material.dart';
import 'package:frontend/desktop/main_screen/widgets/main_screen_app_bar.dart';
import 'package:frontend/desktop/main_screen/widgets/main_screen_body/main_screen_body.dart';
import 'package:frontend/shared/widgets/scaffolds/base_scaffold.dart';

final class MainScreen extends StatelessWidget {
  const MainScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return const BaseScaffold(
      appBar: MainScreenAppBar(),
      body: MainScreenBody(),
    );
  }
}
