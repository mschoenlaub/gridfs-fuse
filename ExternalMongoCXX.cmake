include(ExternalProject)

set_property(DIRECTORY PROPERTY EP_BASE ${PROJECT_BINARY_DIR}/external)


ExternalProject_Add(
    mongo-cxx-driver
    URL https://github.com/mongodb/mongo-cxx-driver/archive/legacy-1.0.0.tar.gz
    BUILD_IN_SOURCE true
    BUILD_ALWAYS false
    CONFIGURE_COMMAND ""
    BUILD_COMMAND scons 
    INSTALL_COMMAND scons install --prefix=<INSTALL_DIR>
)

ExternalProject_Get_Property(mongo-cxx-driver install_dir)
set(MONGOCXX_LIBS ${install_dir}/lib/libmongoclient${CMAKE_STATIC_LIBRARY_SUFFIX})
set(MONGOCXX_INCLUDE_DIRS ${install_dir}/include)