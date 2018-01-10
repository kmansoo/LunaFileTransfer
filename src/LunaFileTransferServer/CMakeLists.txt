# CMake Version
CMAKE_MINIMUM_REQUIRED (VERSION 3.5.1)

# Project Name
PROJECT(LunaFileTransferServer)

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
	${LUNA_SW_PLATFORM}/src/ThirdPartyLibrary/ccMongooseServer/include
)

link_directories(
	${LUNA_SW_PLATFORM}/build/lib
)

add_executable (LunaFileTransferServer
    LunaFileTransferServer.cpp
    FileReceiver.cpp
    FileSender.cpp
		FileTransferSessionInfo.cpp
)

TARGET_LINK_LIBRARIES(LunaFileTransferServer
	ccMongooseServer
	ccWebsocketClient
	ccJsonParser
	ccWebServer
	ccNetwork
	ccCore
	pthread
)
