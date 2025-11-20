set(CMAKE_C_STANDARD 11)

add_library(libaii SHARED aii.c)

install( FILES aii.h DESTINATION include )
install( TARGETS libaii
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)