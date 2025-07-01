
# local env vs docker env
if [ $_OS_APP_ ];then
	echo "_OS_APP_" = $_OS_APP_
else
	export _OS_APP_=test$_OS_APP_
	echo "_OS_APP_ is not exist, set _OS_APP_ as test"
fi
if [ $_OS_NAMESPACE_ ];then
	echo "_OS_NAMESPACE_" = $_OS_APP_
else
	export _OS_NAMESPACE_=test$_OS_NAMESPACE_
	echo "_OS_NAMESPACE_ is not exist, set _OS_NAMESPACE_ as test"
fi



echo $_OS_APP_
echo $_OS_NAMESPACE_
# local env vs docker env

export LD_LIBRARY_PATH=./3rd/mqtt/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=./3rd/jsoncpp/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=./3rd/rdkafka/lib:$LD_LIBRARY_PATH

export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH

# demo 程序可能依赖于位于 ./3rd/mqtt/lib、./3rd/jsoncpp/lib、./3rd/rdkafka/lib  这些目录下的共享库。
# 如果这些库不在系统的默认库搜索路径中（如 /usr/lib 或 /usr/local/lib），那么动态链接器就无法找到它们，从而导致 demo 程序运行失败.

# 只要是在cmake中demo链接了上面这些共享库，只需要对全局变量设置之后即可执行demo

exec ./demo


