add_subdirectory(ai)

add_executable(${PROJECT_NAME} main.c context.c world.c simulation.c dummy.c physicsBody.c radar.c)

target_link_libraries(${PROJECT_NAME}
  csfml-graphics
  csfml-window
  csfml-system
  csfml-network
  csfml-audio
  ai
)