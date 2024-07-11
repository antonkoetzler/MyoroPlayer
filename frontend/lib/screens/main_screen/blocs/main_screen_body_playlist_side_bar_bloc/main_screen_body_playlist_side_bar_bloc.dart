import 'package:flutter/foundation.dart';
import 'package:flutter_bloc/flutter_bloc.dart';
import 'package:kiwi/kiwi.dart';
import 'package:frontend/screens/main_screen/blocs/main_screen_body_playlist_side_bar_bloc/main_screen_body_playlist_side_bar_event.dart';
import 'package:frontend/screens/main_screen/blocs/main_screen_body_playlist_side_bar_bloc/main_screen_body_playlist_side_bar_state.dart';
import 'package:frontend/shared/enums/bloc_status_enum.dart';
import 'package:frontend/shared/extensions/string_extension.dart';
import 'package:frontend/shared/helpers/file_system_helper.dart';
import 'package:frontend/shared/models/playlist.dart';
import 'package:frontend/shared/services/playlist_service/playlist_service.dart';

final class MainScreenBodyPlaylistSideBarBloc extends Bloc<MainScreenBodyPlaylistSideBarEvent, MainScreenBodyPlaylistSideBarState> {
  late final FileSystemHelper _fileSystemHelper;
  late final PlaylistService _playlistService;

  MainScreenBodyPlaylistSideBarBloc() : super(const MainScreenBodyPlaylistSideBarState()) {
    final kiwiContainer = KiwiContainer();
    _fileSystemHelper = kiwiContainer.resolve<FileSystemHelper>();
    _playlistService = kiwiContainer.resolve<PlaylistService>();

    on<MainScreenBodyPlaylistSideBarEvent>((event, emit) async {
      emit(state.copyWith(status: BlocStatusEnum.loading));

      if (event is CreatePlaylistEvent || event is OpenPlaylistEvent) {
        late final String? folderPath;

        if (event is CreatePlaylistEvent) {
          folderPath = await _fileSystemHelper.createFolderDialogWindow();
        } else if (event is OpenPlaylistEvent) {
          folderPath = await _fileSystemHelper.openFolderDialogWindow(
            title: 'Choose the playlists you\'d like to add.',
          );
        }

        await _validateAndSavePlaylist(
          emit,
          folderPath,
          event is CreatePlaylistEvent,
        );
      }

      if (event is SetPlaylistImageEvent) {
        final String? imagePath = !event.removeImage ? await _fileSystemHelper.openImageDialogWindow() : null;
        if (!event.removeImage && imagePath == null) return;
        await _updatePlaylistImage(event.playlist, imagePath, emit);
      }

      if (event is RemovePlaylistFromMyoroPlayerEvent) {
        try {
          await _playlistService.delete(id: event.playlist.id!);

          emit(
            state.copyWith(
              status: BlocStatusEnum.completed,
              snackBarMessage: '${event.playlist.name} removed from MyoroPlayer successfully!',
            ),
          );
        } catch (error, stackTrace) {
          if (kDebugMode) {
            print('[MainScreenBodyPlaylistSideBarBloc.RemovePlaylistFromMyoroPlayerEvent]: Error deleting playlist: "$error"');
            print('Stack trace:\n$stackTrace');
          }

          emit(
            state.copyWith(
              status: BlocStatusEnum.error,
              snackBarMessage: 'Error removing ${event.playlist.name}.',
            ),
          );
        }
      }
    });
  }

  Future<void> _validateAndSavePlaylist(
    Emitter<MainScreenBodyPlaylistSideBarState> emit,
    String? folderPath,
    bool createFolder,
  ) async {
    // Openation cancelled by the user
    if (folderPath == null) return;

    final String folderName = folderPath.pathName;

    // Checking for invalid characters
    if (!folderName.isValidFolderName) {
      emit(
        state.copyWith(
          status: BlocStatusEnum.error,
          snackBarMessage: 'Playlist cannot contain these characters: \\/:*?"<>|',
        ),
      );

      return;
    }

    final Playlist? playlist = await _playlistService.create(
      data: Playlist(
        path: folderPath,
        name: folderName,
      ).toJson(),
    );

    if (playlist == null) {
      emit(
        state.copyWith(
          status: BlocStatusEnum.error,
          snackBarMessage: 'Playlist already exists in your local database.',
        ),
      );

      return;
    }

    emit(
      state.copyWith(
        status: BlocStatusEnum.completed,
        snackBarMessage: '${playlist.path} created successfully!',
      ),
    );

    _fileSystemHelper.createFolder(folderPath);
  }

  Future<void> _updatePlaylistImage(
    Playlist playlist,
    String? imagePath,
    Emitter<MainScreenBodyPlaylistSideBarState> emit,
  ) async {
    try {
      await _playlistService.update(
        id: playlist.id,
        data: {Playlist.imageJsonKey: imagePath},
      );

      emit(
        state.copyWith(
          status: BlocStatusEnum.completed,
          snackBarMessage: '${playlist.name}\'s image changed successfully!',
        ),
      );
    } catch (error, stackTrace) {
      if (kDebugMode) {
        print('[MainScreenBodyPlaylistSideBarBloc.SetPlaylistImageEvent]: Error updating the image on the database.');
        print('Stack trace:\n$stackTrace');
      }

      emit(
        state.copyWith(
          status: BlocStatusEnum.error,
          snackBarMessage: 'Error updating ${playlist.name}\'s image.',
        ),
      );
    }
  }
}
