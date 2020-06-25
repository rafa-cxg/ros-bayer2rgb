# http://ros.org/doc/groovy/api/catkin/html/user_guide/supposed.html
cmake_minimum_required(VERSION 2.8.3)
project(cxg_camera)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
find_package(OpenCV REQUIRED)
find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs image_transport camera_info_manager dynamic_reconfigure driver_base tf dynamic_reconfigure cv_bridge std_msgs)
catkin_package(
    CATKIN_DEPENDS roscpp sensor_msgs image_transport camera_info_manager dynamic_reconfigure driver_base tf  cv_bridge std_msgs
    INCLUDE_DIRS
    LIBRARIES
)

include_directories(include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} )



add_executable(cxg main.cpp)

target_link_libraries(cxg ${catkin_LIBRARIES} ${OpenCV_LIBS})
add_dependencies(cxg ${PROJECT_NAME}_gencfg)
