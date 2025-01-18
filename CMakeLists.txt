cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(MuonID)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB MACRO_FILES
"*.mac"
)

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR}) ##Este comando copia todos los archivos macro que creamos en el folder de los projectos y los pega en el folder "build"  

include_directories(${PROJECT_SOURCE_DIR}/include
	             ${Geant4_INCLUDE_DIR})

add_executable(MuonID MuonID_sim.cc ${sources} ${headers})
target_link_libraries(MuonID ${Geant4_LIBRARIES})

##add_custom_target(Simulation DEPENDS sim)
