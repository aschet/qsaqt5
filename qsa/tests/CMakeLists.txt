if(Qt6_FOUND)
    find_package(Qt6 REQUIRED COMPONENTS Test)
else()
    find_package(Qt5 5.15 REQUIRED COMPONENTS Test)
endif()

function(qsa_add_test name)
    set(source ${name})
    if(ARGC GREATER 1)
        set(source ${ARGV1})
    endif()
    add_executable(${name} ${source}.cpp)
    target_link_libraries(${name} PRIVATE qsa Qt::Test)
    add_test(NAME ${name} COMMAND ${name})
    set_tests_properties(${name} PROPERTIES ENVIRONMENT QT_QPA_PLATFORM=offscreen)
    if(WIN32 AND Qt5_FOUND)
        # the offscreen platform of Qt 5 finds no fonts on Windows, widgets that use text crash without them
        set_property(TEST ${name} APPEND PROPERTY ENVIRONMENT "QT_QPA_FONTDIR=$ENV{WINDIR}/Fonts")
    endif()
    if(WIN32 AND NOT QSA_NO_DLL)
        # a qsa.dll that is found through PATH must not shadow the one that is tested
        add_custom_command(TARGET ${name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:qsa> $<TARGET_FILE_DIR:${name}>)
    endif()
endfunction()

qsa_add_test(tst_language)
qsa_add_test(tst_interpreter)
qsa_add_test(tst_bridge)
qsa_add_test(tst_types)

# the same tests for a host with a project and a host with a plain interpreter
qsa_add_test(tst_host_project tst_host)
target_compile_definitions(tst_host_project PRIVATE QSA_HOST_THREAD_AWARE=false)
qsa_add_test(tst_host_plain tst_host)
target_compile_definitions(tst_host_plain PRIVATE QSA_HOST_THREAD_AWARE=true)
qsa_add_test(tst_project)

qsa_add_test(tst_utils)
add_executable(copy_stdin copy_stdin.cpp)
add_dependencies(tst_utils copy_stdin)
target_compile_definitions(tst_utils PRIVATE
    QSA_TEST_CMAKE="${CMAKE_COMMAND}"
    QSA_TEST_COPY_STDIN="$<TARGET_FILE:copy_stdin>")

qsa_add_test(tst_ui)
target_compile_definitions(tst_ui PRIVATE
    QSA_EXAMPLES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../examples")

qsa_add_test(tst_examples)
target_compile_definitions(tst_examples PRIVATE
    QSA_EXAMPLES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../examples")

if(NOT QSA_NO_EDITOR AND QSA_NEW_EDITOR)
    qsa_add_test(tst_editor)
endif()
