set( CMAKE_VERBOSE_MAKEFILE on )

add_library(lib-eolipile STATIC
        src/SDLLibs.h
        src/Engine.cpp src/Engine.h
        src/EngineWorld.cpp src/EngineWorld.h
        src/EngineItem.cpp src/EngineItem.h
        src/EngineItemState.cpp src/EngineItemState.h
        src/EngineSprite.cpp src/EngineSprite.h
        src/EngineDimension.cpp src/EngineDimension.h
        src/EngineInputListener.cpp src/EngineInputListener.h
        )

target_include_directories(lib-eolipile PUBLIC src)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

    set(CMAKE_FRAMEWORK_PATH ${CMAKE_CURRENT_LIST_DIR}lib/macos)

    include_directories(
            lib/macos/SDL2.framework
            lib/macos/SDL2_image.framework)

    find_library(SDL2 NAMES SDL2)
    find_library(SDL2IMG NAMES SDL2_image)

    target_link_libraries(lib-eolipile lib-geometry)
    target_link_libraries(lib-eolipile ${SDL2} ${SDL2IMG})

    add_definitions(-DMACOSX)

endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


