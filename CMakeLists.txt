PROJECT(MyoroPlayer)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

IF (WIN32)
  SET(wxWidgets_ROOT_DIR "C:/wxWidgets-3.1.6")
  SET(wxWidgets_CONFIGURATION mswu)
ENDIF (WIN32)

FIND_PACKAGE(wxWidgets REQUIRED core base media)

AUX_SOURCE_DIRECTORY(./src/ SRC)
INCLUDE_DIRECTORIES(./include/)

INCLUDE("${wxWidgets_USE_FILE}")

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})

IF (UNIX)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${wxWidgets_LIBRARIES} "-no-pie")
ENDIF (UNIX)

IF (WIN32)
  SET(wxLibsDir "C:/wxWidgets-3.1.6/lib/gcc_lib")
  TARGET_LINK_LIBRARIES(
    ${PROJECT_NAME}
    ${wxLibsDir}/libwxmsw31u_media.a
    ${wxLibsDir}/libwxmsw31u_core.a
    ${wxLibsDir}/libwxbase31u.a
    ${wxLibsDir}/libwxpng.a
    ${wxLibsDir}/libwxtiff.a
    ${wxLibsDir}/libwxjpeg.a
    ${wxLibsDir}/libwxzlib.a
    ${wxLibsDir}/libwxregexu.a
    ${wxLibsDir}/libwxexpat.a
    winmm
    comctl32
    uuid
    oleacc
    uxtheme
    rpcrt4
    shlwapi
    version
    wsock32
    "-static -mwindows"
  )
ENDIF (WIN32)
