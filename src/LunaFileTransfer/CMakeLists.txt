# CMake Version
CMAKE_MINIMUM_REQUIRED (VERSION 3.5.1)

# Project Name
PROJECT(LunaFileTransfer)

# Configuration
SET(LUNA_SW_PLATFORM ${CMAKE_CURRENT_SOURCE_DIR}/../dependency/Luna)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(
	./ 
	${LUNA_SW_PLATFORM}/src/Library/ccCore/include
	${LUNA_SW_PLATFORM}/src/Library/ccNetwork/include
	${LUNA_SW_PLATFORM}/src/Library/ccWebServer/include
	${LUNA_SW_PLATFORM}/src/FossLibrary/ccJsonParser/include
	${LUNA_SW_PLATFORM}/src/FossLibrary/ccWebsocketClient/include
)

link_directories(
	${LUNA_SW_PLATFORM}/build/lib
)

add_executable (LunaFileTransfer
    LunaFileTransfer.cpp
    FileReceivingClient.cpp
    FileSendingClient.cpp
)

TARGET_LINK_LIBRARIES(LunaFileTransfer
	ccWebsocketClient
	ccJsonParser
	ccWebServer
	ccNetwork
	ccCore
	pthread
)  
