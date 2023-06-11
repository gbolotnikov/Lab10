cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(bulk_server VERSION ${PROJECT_VESRION})

find_package(Boost COMPONENTS COMPONENTS program_options REQUIRED)
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(bulk_server main.cpp
    Server.cpp
    Session.cpp
    StreamReader.cpp
    FileWriter.cpp
    CommandManager.cpp
 )

set_target_properties(bulk_server PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(bulk_server PRIVATE "${CMAKE_BINARY_DIR}")

if(WIN32)
target_link_libraries(bulk_server PRIVATE 
    ws2_32
    wsock32 
    ${Boost_LIBRARIES} 
    Boost::program_options 
    stdc++fs)
else()
target_link_libraries(bulk_server PRIVATE 
    ${Boost_LIBRARIES} 
    Boost::program_options 
    stdc++fs)
endif()



install(TARGETS bulk_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)