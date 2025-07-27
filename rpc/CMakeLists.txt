find_package(Protobuf REQUIRED)
find_package(Threads REQUIRED)
find_library(BRPC_LIBRARY NAMES brpc)
find_library(GFLAGS_LIBRARY NAMES gflags)
find_library(SSL_LIBRARY NAMES ssl)
find_library(CRYPTO_LIBRARY NAMES crypto)
find_library(LEVELDB_LIBRARY NAMES leveldb)
find_library(DL_LIBRARY NAMES dl)


add_executable(client ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cc)
target_include_directories(client  
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${Protobuf_INCLUDE_DIRS}
)
target_link_libraries(client 
  PRIVATE 
  message 
  monitor 
  ${BRPC_LIBRARY}
  ${Protobuf_LIBRARIES}
  ${GFLAGS_LIBRARY}
  ${SSL_LIBRARY}
  ${CRYPTO_LIBRARY}
  ${LEVELDB_LIBRARY}
  ${DL_LIBRARY}
  ${CMAKE_THREAD_LIBS_INIT}
)


add_executable(server ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cc)
target_include_directories(server 
  PRIVATE ${Protobuf_INCLUDE_DIRS}
)
target_link_libraries(server 
  PRIVATE 
  message 
  monitor 
  ${BRPC_LIBRARY}
  ${Protobuf_LIBRARIES}
  ${GFLAGS_LIBRARY}
  ${SSL_LIBRARY}
  ${CRYPTO_LIBRARY}
  ${LEVELDB_LIBRARY}
  ${DL_LIBRARY}
  ${CMAKE_THREAD_LIBS_INIT}
)