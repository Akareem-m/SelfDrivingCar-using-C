add_library(ai AI.c genome.c)

target_include_directories(ai PUBLIC ../../external/csfml/include PUBLIC ../../include)