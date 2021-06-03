# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(optimization)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs message_generation eval_funcs)

## Declare ROS messages and services
#add_message_files(FILES Num.msg)
#add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES beginner_tutorials
  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)
## Build talker and listener
include_directories(include/optimization ${catkin_INCLUDE_DIRS})

add_executable(optimization src/BinaryGA.cpp)
target_link_libraries(optimization ${catkin_LIBRARIES})
add_dependencies(optimization optimization_generate_messages_cpp
${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS}
)

# %EndTag(FULLTEXT)%
