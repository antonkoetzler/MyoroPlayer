import 'package:flutter_test/flutter_test.dart';
import 'package:myoro_player/shared/blocs/model_resolver_bloc/model_resolver_bloc.dart';
import 'package:myoro_player/shared/blocs/model_resolver_bloc/model_resolver_event.dart';
import 'package:myoro_player/shared/blocs/model_resolver_bloc/model_resolver_state.dart';
import 'package:myoro_player/shared/enums/bloc_status_enum.dart';

void main() {
  test('ModelResolverBloc.ExecuteRequestEvent error case', () {
    final bloc = ModelResolverBloc<String>();

    expectLater(
      bloc.stream,
      emitsInOrder([
        ModelResolverState<String>(
          status: BlocStatusEnum.loading,
        ),
        ModelResolverState<String>(
          status: BlocStatusEnum.error,
          snackBarMessage: '[ModelResolverBloc.ExecuteRequestEvent]: Error executing [request] provided.',
        ),
      ]),
    );

    bloc.add(ExecuteRequestEvent(() async => throw Exception()));
  });

  test('ModelResolverBloc.ExecuteRequestEvent passing case', () {
    final bloc = ModelResolverBloc<String>();

    expectLater(
      bloc.stream,
      emitsInOrder([
        ModelResolverState<String>(
          status: BlocStatusEnum.loading,
        ),
        ModelResolverState<String>(
          model: 'Response',
          status: BlocStatusEnum.completed,
        ),
      ]),
    );

    bloc.add(ExecuteRequestEvent(() async => 'Response'));
  });
}
