# mprpc
A distributed network communication framework based on the Muduo



## mprpc框架使用方法

我们只需要有`libmprpc.a`这个静态库和对应头文件，`protobuf`库、`zookeeper_mt`库、`pthread`库即可：

测试的目录结构如下：

```cpp
jyhlinux@ubuntu:~/share/mprpc/test/mprpcexample$ tree
.
├── callfriendservice.cc
├── friend.pb.cc
├── friend.pb.h
├── lib
│   ├── include
│   │   ├── lockqueue.h
│   │   ├── logger.h
│   │   ├── mprpcapplication.h
│   │   ├── mprpcchannel.h
│   │   ├── mprpcconfig.h
│   │   ├── mprpccontroller.h
│   │   ├── rpcheader.pb.h
│   │   ├── rpcprovider.h
│   │   └── zookeeperutil.h
│   └── libmprpc.a
└── test.conf

```

进行编译生成可执行文件

```sh
g++ callfriendservice.cc  friend.pb.cc -o consumer -I lib/include/ -L lib/ -L /usr/local/lib/ -lprotobuf -lmprpc -lzookeeper_mt -pthread
```

