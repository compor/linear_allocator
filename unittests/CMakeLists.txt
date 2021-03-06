# cmake file

# requirements

if(PRJ_SKIP_TESTS)
  message(WARNING "Testing is disabled; skipping unit tests")

  return()
endif()


find_package(GTest)

if(NOT GTEST_FOUND)
  message(WARNING "Could not find GTest; skipping unit tests")

  return()
endif()

find_package(Threads REQUIRED)

# configuration

# aggregate unit test targets under a pseudo-target
add_custom_target(unittests)

set(PRJ_UNIT_TEST_BINS "")

list(APPEND PRJ_TEST_NAMES "test_private_memory_arena")
list(APPEND PRJ_TEST_NAMES "test_linear_private_allocator")
list(APPEND PRJ_TEST_NAMES "test_linear_shared_allocator")

foreach(prj_test_name ${PRJ_TEST_NAMES})
  set(TEST_SOURCES "${prj_test_name}.cpp")

  add_executable(${prj_test_name} ${TEST_SOURCES})

  set_target_properties(${prj_test_name} PROPERTIES 
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CMAKE_CXX_EXTENSIONS OFF)

  target_include_directories(${prj_test_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_include_directories(${prj_test_name} PUBLIC ${GTEST_INCLUDE_DIRS})
  target_include_directories(${prj_test_name} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include/>)
  target_include_directories(${prj_test_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>)

  target_link_libraries(${prj_test_name} PUBLIC GTest::GTest GTest::Main)  

  set_property(TARGET ${prj_test_name} APPEND_STRING PROPERTY 
    LINK_FLAGS " -Wl,--warn-unresolved-symbols")

  # setup dependency between unit test targets and their production code
  add_dependencies(${prj_test_name} ${TESTEE_LIB})

  # exclude unit test targets from main build
  set_target_properties(${prj_test_name} PROPERTIES EXCLUDE_FROM_ALL TRUE)

  add_dependencies(unittests ${prj_test_name})

  get_property(PRJ_UNIT_TEST_BIN TARGET ${prj_test_name} PROPERTY NAME)
  set(PRJ_UNIT_TEST_BINS "./${PRJ_UNIT_TEST_BIN} && ${PRJ_UNIT_TEST_BINS}")
endforeach()

set(PRJ_UNIT_TEST_BINS "${PRJ_UNIT_TEST_BINS} true")

set(PRJ_UNIT_TESTS_SCRIPT "run_unit_tests.sh")
get_property(PRJ_UNIT_TESTS_TARGET TARGET unittests PROPERTY NAME)

configure_file("${PRJ_UNIT_TESTS_SCRIPT}.in" 
  "${CMAKE_BINARY_DIR}/${PRJ_UNIT_TESTS_SCRIPT}"
  @ONLY)

