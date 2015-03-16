cmake_minimum_required(VERSION 2.8.4)

project(GRIDFS_FUSE)

include(ExternalMongoCXX.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost REQUIRED COMPONENTS thread filesystem system regex)

find_package (Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(FUSE REQUIRED)

add_definitions(${FUSE_DEFINITIONS})

include_directories(${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} ${FUSE_INCLUDE_DIRS} ${MONGOCXX_INCLUDE_DIRS})

set(SOURCE_FILES
    local_gridfile.cpp
    local_gridfile.h
    main.cpp
    operations.cpp
    operations.h
    ops_dir.cpp
    ops_file.cpp
    ops_link.cpp
    ops_metadata.cpp
    ops_xattr.cpp
    options.cpp
    options.h
    utils.h)

add_executable(mount_gridfs ${SOURCE_FILES})


add_dependencies(mount_gridfs mongo-cxx-driver)

target_link_libraries(mount_gridfs ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${OpenSSL_LIBRARIES} ${FUSE_LIBRARIES} ${MONGOCXX_LIBS})
