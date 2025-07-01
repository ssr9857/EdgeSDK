#include <iostream>
#include "edge_interface.h"
using namespace std;


int main()
{
    std::shared_ptr<EdgeInterface>  p_edge_interface = std::make_shared<EdgeInterface>();
    p_edge_interface->InitEdgeI("./", "./");
}

// 执行流程：
    // mkdir build
    // cd build
    // cmake ..
    // make -j8
    // make install 
    // cd ..
    // ./run.sh




// export LD_LIBRARY_PATH=/home/firefly/Documents/Seaway/SeawayEdgeSDK/lib/:$LD_LIBRARY_PATH  添加库文件搜索路径

//g++ demo.cpp -lseaway_sdk -o demo 编译，链接用到的库文件

// 注意：直接调用run.sh 用来给_SEAWAYOS_APP_赋值，否则会报错
