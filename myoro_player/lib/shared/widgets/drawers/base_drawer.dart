import 'package:flutter/material.dart';
import 'package:myoro_player/shared/design_system/color_design_system.dart';
import 'package:myoro_player/shared/design_system/decoration_design_system.dart';
import 'package:myoro_player/shared/enums/image_size_enum.dart';
import 'package:myoro_player/shared/extensions/build_context_extension.dart';
import 'package:myoro_player/shared/widgets/buttons/icon_text_hover_button.dart';

final class BaseDrawer extends StatelessWidget {
  final String? title;
  final bool showCloseButton;
  final Widget child;

  const BaseDrawer({
    super.key,
    this.title,
    this.showCloseButton = true,
    required this.child,
  });

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.all(10),
      child: Drawer(
        shape: RoundedRectangleBorder(
          borderRadius: DecorationDesignSystem.borderRadius,
          side: BorderSide(
            width: 2,
            color: ColorDesignSystem.onBackground(context),
          ),
        ),
        child: Padding(
          padding: const EdgeInsets.all(10),
          child: Column(
            children: [
              Row(
                children: [
                  if (title != null)
                    Text(
                      title!,
                      style: context.textTheme.titleSmall,
                    ),
                  const Spacer(),
                  if (showCloseButton)
                    IconTextHoverButton(
                      icon: Icons.close,
                      iconSize: ImageSizeEnum.small.size - 10,
                      onTap: () => Navigator.of(context).pop(),
                    ),
                ],
              ),
              child,
            ],
          ),
        ),
      ),
    );
  }
}
