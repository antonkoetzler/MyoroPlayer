PROJECT(MyoroPlayer)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# Setting wxWidgets directory on Windows
IF (WIN32)
  SET(wxWidgets_ROOT_DIR "C:/wxWidgets-3.1.5")
  SET(wxWidgets_CONFIGURATION mswu)
ENDIF (WIN32)

FIND_PACKAGE(wxWidgets REQUIRED core base media)

AUX_SOURCE_DIRECTORY(./src/ SRC)
INCLUDE_DIRECTORIES(./include/)

INCLUDE("${wxWidgets_USE_FILE}")

#add_link_options(-mwindows)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})

IF (WIN32)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${wxWidgets_LIBRARIES} "-static -mwindows")
ENDIF (WIN32)

IF (UNIX)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
ENDIF (UNIX)

