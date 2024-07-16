import 'package:flutter/material.dart';
import 'package:myoro_player/shared/design_system/color_design_system.dart';
import 'package:myoro_player/shared/design_system/image_design_system.dart';
import 'package:myoro_player/shared/enums/image_size_enum.dart';
import 'package:myoro_player/shared/widgets/app_bars/base_app_bar.dart';
import 'package:myoro_player/shared/widgets/buttons/icon_text_hover_button.dart';
import 'package:myoro_player/shared/widgets/images/base_image.dart';

final class MainScreenAppBar extends StatelessWidget implements PreferredSizeWidget {
  const MainScreenAppBar({super.key});

  @override
  Size get preferredSize => const Size.fromHeight(kToolbarHeight);

  @override
  Widget build(BuildContext context) {
    return BaseAppBar(
      children: [
        Expanded(
          child: Stack(
            alignment: Alignment.center,
            children: [
              IconTextHoverButton(
                icon: Icons.menu,
                iconSize: ImageSizeEnum.small.size + 5,
                onTap: () => throw UnimplementedError(), // TODO
              ),
              Center(
                child: BaseImage(
                  svgPath: ImageDesignSystem.logo,
                  svgColor: ColorDesignSystem.onBackground(context),
                  size: ImageSizeEnum.small.size,
                ),
              ),
            ],
          ),
        ),
      ],
    );
  }
}
