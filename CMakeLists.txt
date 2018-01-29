cmake_minimum_required(VERSION 2.8)
project(YseEngine)
include(CTest)

#Version Number
set (YseEngine_VERSION_MAJOR 1)
set (YseEngine_VERSION_MINOR 0)


#there will likely be a lot of things wrong with this file 


#does this system provide these methods we should have?
include(${CMAKE_ROOT}/Modues/CheckMethodExists.cmake)

check_function_exists(method_1 HAVE_METHOD_1)
check_function_exists(method_2 HAVE_METHOD_2)

#choice to use custom libraries 
option (USE_MYLIBRARY
		 "Use custom [x] implementation" ON)


# Header file config to pass to source
configure_file(	
	"${PROJECT_SOURCE_DIR}/YseEngineConfig.h.in"
	"${PROJECT_BINARY_DIR}/YseEngineConfig.h"
	)

# Add binary tree to search path for includes
# to find YseEngineConfig.h
include_directories("{$PROJECT_BINARY_DIR}")

#if adding SomeLIbrary
if (USE_MYLIBRARY)
	include_directories ("${PROJECT_SOURCE_DIR}/SomeLibrary")
	add_subdirectory (SomeLibrary)
	set (EXTRA)LIBS ${EXTRALIBS} SomeLIbrary)
endif (USE_MYLIBRARY)

#add the executable (again?)
add_executable(YseEngine YseEngine.cxx)
target_link_libraries(YseEngine ${EXTRA_LIBS})

#add install targets
install (TARGETS YseEngine DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/YseEngineConfig.h"
		 DESTINATION include)


#does the application run
add_test(YseEngineRuns YseEngine SomethingToTest)

#define a macro to simplify adding tests, then use it
macro(do_test arg result)
		add_test(YseEngineTest{arg} YseEngine ${arg})
		set_tests_properties(YseEngineTest${arg}
			PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro(do_test)

#a bunch of result based tests
do_test(YseEngine "This should be the output")
do_test(SomethingToTest "Some true statement that YseEngine should do properly")
do_test(SpecialCase "This is how YseEngine should handle this case")
do_test(DifferentCase "This should be handled or calculated in this way")

###############################################
# should this be a different file altogether? #
###############################################

#making a generated source file
#first add executable that generates a table, for example
add_executable(MakeTable MakeTable.cxx)

#add the command to generate the source code
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
	COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
	DEPENDS MakeTable
	)

#add the binary tree directory to the search path for include files 
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#add the main library
add_library(SomeLibrary sourceFile ${CMAKE_CURRENT_BINARY_DIR}/Table.h)

install(TARGETS SomeLibrary DESTINATION bin)
install(FILES SomeLibrary.h DESTINATION include)

#build a CPack driven installer package
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE
	"${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${YseEngine_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${YseEngine_VERSION_MINOR}")
include(Cpack)

#where to add this? run in terminal?
#cpack --config CPackConfig.cmake
#cpack --config CpackSourceConfig.cmake


#enable dashboard scripting
include(CTest)
set(CTEST_PROJECT_NAME "YseEngine")


#what about the rest of this? the following is commented 
#because I dont know if it should exist or not

# Add the executable
#add_executable(YseEngine YseEngine.cxx)

# Add library
#add_library(SomeLibrary sourceFile.cxx)

#include_directories ("${PROJECT_SOURCE_DIR}/SomeLibrary")
#add_subdirectory (SomeLibrary)

# Add the executable (again? ask)
#add_executable(YseEngine YseEngine.cxx)

#target_link_libraries (YseEngine SomeLibrary)



#macro shortens the following tests to the above (do_test) from the below (add/set test(s))

#does it do [X] thing it's supposed to
#add_test(YseEngineDoesX YseEngine SomethingToTest)
#set_tests_properties(YseEngineDoesX PROPERTIES PASS_REGULAR_EXPRESSION 
	#"Some true statement that YseEngine should do properly")
#does it properly handle these sort of potential errors?
#add_test(YseEnginePotentialErrorHandling YseEngine SpecialCase)
#set_tests_properties(YseEnginePotentialErrorHandling PROPERTIES PASS_REGULAR_EXPRESSION
#	"This is how YseEngine should handle this case")
#does it handle this case as it should or does it incorrectly compute/handle this case
#add_test(YseEnginePotentialMisconduct YseEngine DifferentCase)
#set_tests_properties(YseEnginePotentialMisconduct PROPERTIES PASS_REGULAR_EXPRESSION
#	"This should be handled or calculated in this way")
#does this other thing we want YseEngine to do work the way we want it?
#add_test(YseEngineDesiredOutput YseEngine)
#set_tests_properties(YseEngineDesiredOutput PROPERTIES PASS_REGULAR_EXPRESSION 
#	"This should be the output")


