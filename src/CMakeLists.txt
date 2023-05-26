#aux_source_directory(. SRC_LIST)
set(SRC_LIST
    mprpcapplication.cc
    mprpcconfig.cc
    rpcheader.pb.cc
    rpcprovider.cc
    mprpcchannel.cc
    mprpccontroller.cc
    logger.cc)
# 由于muduo库是静态库，编译时索性就生成静态库
add_library(mprpc ${SRC_LIST})
target_link_libraries(mprpc muduo_net muduo_base pthread)