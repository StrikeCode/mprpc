# set(SRC_LIST calluserservice.cc ../user.pb.cc)
set(SRC_LIST callfriendservice.cc ../friend.pb.cc)
# provider是目标文件，后面都是要链接的库 -lmprpc -lprotobuf
add_executable(consumer ${SRC_LIST})
target_link_libraries(consumer mprpc protobuf)