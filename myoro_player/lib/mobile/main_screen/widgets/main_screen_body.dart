import 'package:flutter/material.dart';
import 'package:flutter_bloc/flutter_bloc.dart';
import 'package:myoro_player/shared/blocs/playlist_listing_bloc/playlist_listing_bloc.dart';
import 'package:myoro_player/shared/blocs/playlist_listing_bloc/playlist_listing_state.dart';

import '../../../shared/widgets/screens/main_screen/song_listing.dart';

final class MainScreenBody extends StatelessWidget {
  const MainScreenBody({super.key});

  @override
  Widget build(BuildContext context) {
    return BlocListener<PlaylistListingBloc, PlaylistListingState>(
      listener: (context, state) => PlaylistListingBloc.handleSnackBars(context, state),
      child: const SongListing(),
    );
  }
}
