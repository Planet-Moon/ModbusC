
add_library(
    b
    b.h
    b.cpp
)

add_executable(
    template
    main.cpp
    templateTest.cpp
    templateTest.h
)
target_link_libraries(template b)
