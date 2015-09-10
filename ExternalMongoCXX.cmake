include(ExternalProject)

set_property(DIRECTORY PROPERTY EP_BASE ${PROJECT_BINARY_DIR}/external)


ExternalProject_Add(
    mongo-cxx-driver
    GIT_REPOSITORY git@github.com:mongodb/mongo-cxx-driver.git
    GIT_TAG 835204df79f036fdc4f8e6b8339125745b6512a2
    BUILD_IN_SOURCE true
    BUILD_ALWAYS true
)

ExternalProject_Get_Property(mongo-cxx-driver install_dir)
set(CMAKE_PREFIX_PATH ${install_dir})
