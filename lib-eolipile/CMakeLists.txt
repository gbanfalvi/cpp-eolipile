add_library(lib-eolipile STATIC src/Engine.cpp src/Engine.h src/EngineDimension.cpp src/EngineDimension.h src/EngineInputListener.cpp src/EngineInputListener.h src/EngineItem.cpp src/EngineItem.h src/EngineItemState.cpp src/EngineItemState.h src/EngineSprite.cpp src/EngineSprite.h src/EngineWorld.cpp src/EngineWorld.h)
target_include_directories(lib-eolipile PUBLIC src)

set(LINKED_LIBS LINK_PUBLIC lib-geometry)

if(APPLE)
    include_directories("lib/macos")

    find_library(SDL2_LIBRARY SDL2)
    find_library(SDL2_IMAGE_LIBRARY SDL2_image)

    set(EXTRA_LIBS ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
    set(LINKED_LIBS ${LINKED_LIBS} ${EXTRA_LIBS})

    add_definitions(-DMACOSX)
endif(APPLE)

target_link_libraries(lib-eolipile ${LINKED_LIBS})