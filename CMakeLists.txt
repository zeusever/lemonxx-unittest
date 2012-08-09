lemon_c_cxx_files(SRC)

lemon_unittest_project(unittest-lemonxx ${SRC})

target_link_libraries(unittest-lemonxx lemon-sys)