PROJECT(MyoroPlayer)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

if (WIN32)
  SET(wxWidgets_ROOT_DIR "C:/wxWidgets-3.1.5")
  SET(wxWidgets_CONFIGURATION mswu)
endif (WIN32)

FIND_PACKAGE(wxWidgets REQUIRED core base media)

AUX_SOURCE_DIRECTORY(./src/ SRC)
INCLUDE_DIRECTORIES(./include/)
INCLUDE("${wxWidgets_USE_FILE}")

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})

# Linux library configuration
if (UNIX)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
endif (UNIX)

# Windows library configuration
if (WIN32)
  SET(WX_LIBS_DIR "C:/wxWidgets-3.1.5/lib/gcc_lib")
  TARGET_LINK_LIBRARIES(
	  ${PROJECT_NAME}
	  ${WX_LIBS_DIR}/libwxmsw31u_media.a
	  ${WX_LIBS_DIR}/libwxmsw31u_core.a
	  ${WX_LIBS_DIR}/libwxbase31u.a
	  ${WX_LIBS_DIR}/libwxpng.a
	  ${WX_LIBS_DIR}/libwxtiff.a
	  ${WX_LIBS_DIR}/libwxjpeg.a
	  ${WX_LIBS_DIR}/libwxzlib.a
	  ${WX_LIBS_DIR}/libwxregexu.a
	  ${WX_LIBS_DIR}/libwxexpat.a
	  winmm
	  comctl32
	  uuid
	  oleacc
	  uxtheme
	  rpcrt4
	  shlwapi
	  version
	  wsock32
  )
endif (WIN32)
