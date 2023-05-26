# set(SRC_LIST userservice.cc ../user.pb.cc)
set(SRC_LIST friendservice.cc ../friend.pb.cc)
# provider是目标文件，后面都是要链接的库 -lmprpc -lprotobuf
add_executable(provider ${SRC_LIST})
target_link_libraries(provider mprpc protobuf)
