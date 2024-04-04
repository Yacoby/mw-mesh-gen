set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

FILE(GLOB es_sources ${MW_MESH_GEN_SOURCE_DIR}/es/*.cpp)
FILE(GLOB sources ${MW_MESH_GEN_SOURCE_DIR}/src/*.cpp)

add_executable (MWMeshGenTests SnapshotTest.cpp ${sources} ${es_sources})
target_compile_features(MWMeshGenTests PRIVATE cxx_std_17)
target_link_libraries (MWMeshGenTests ${Boost_LIBRARIES})

enable_testing()
add_test(NAME MWMeshGenTests COMMAND MWMeshGenTests WORKING_DIRECTORY ${MW_MESH_GEN_SOURCE_DIR}/tst)