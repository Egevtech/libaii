set(CMAKE_C_STANDARD 11)

add_library(libaii SHARED aii.c
        aim.c)

install( FILES aii.h DESTINATION include )
install( TARGETS libaii
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

#target_compile_options( libaii PUBLIC `pkg-config fuse3 --cflags --libs` )
target_compile_options( libaii PUBLIC -D_FILE_OFFSET_BITS=64)