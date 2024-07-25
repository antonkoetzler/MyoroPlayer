import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:myoro_player/core/widgets/loading/loading_circle.dart';
import 'package:myoro_player/core/widgets/model_resolvers/model_resolver.dart';

import '../../../base_test_widget.dart';

void main() {
  const text = 'Text';

  testWidgets('Successful request ModelResolver widget test.', (tester) async {
    await tester.pumpWidget(
      BaseTestWidget(
        child: ModelResolver<String>(
          request: () async => text,
          builder: (_, text) => Text(text ?? ''),
        ),
      ),
    );

    expect(find.byType(ModelResolver<String>), findsOneWidget);
    expect(find.byWidgetPredicate((w) => w is Center && w.child is LoadingCircle), findsOneWidget);
    await tester.pump();
    expect(find.byWidgetPredicate((w) => w is Text && w.data == text), findsOneWidget);
  });

  testWidgets('Faulty request ModelResolver widget test.', (tester) async {
    await tester.pumpWidget(
      BaseTestWidget(
        child: ModelResolver<String>(
          request: () async => throw Exception(),
          builder: (_, text) => Text(text ?? ''),
        ),
      ),
    );

    expect(find.byType(ModelResolver<String>), findsOneWidget);
    expect(find.byWidgetPredicate((w) => w is Center && w.child is LoadingCircle), findsOneWidget);
    await tester.pump();
    expect(find.text('[ModelResolverBloc.ExecuteRequestEvent]: Error executing [request] provided.'), findsOneWidget);
  });
}