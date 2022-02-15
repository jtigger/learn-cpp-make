add_library(adder src/adder.cpp)

target_include_directories(adder PUBLIC include)

install(TARGETS adder DESTINATION lib)
install(FILES include/adder.h DESTINATION include)