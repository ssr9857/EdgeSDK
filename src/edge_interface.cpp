#include "edge_interface.h"
#include "edge_interface_impl.h"


// 功能：构造函数
EdgeInterface::EdgeInterface()
{
    p_impl_ = std::make_shared<Impl>();  // std::make_shared 是一个模板函数，用于创建一个 std::shared_ptr 实例
}

// 功能：析构函数
EdgeInterface::~EdgeInterface() = default;

// 功能：初始化边缘设备信息，包括算法和全局参数的配置
void EdgeInterface::InitEdgeI(const std::string & algorithm_config_path, const std::string & algorithm_labels_path)
{
    return p_impl_->InitEdgeI(algorithm_config_path, algorithm_labels_path);
}

// 功能：获取初始化过程读取的peripheral_config.json中的数据，到EdgeInterfaceDate结构体实例中
EdgeInterfaceData EdgeInterface::GetEdgeIData()
{
    return p_impl_->GetEdgeIData();
}

// 功能：进行base64位编码
std::string EdgeInterface::GetEdgeIBase64Encode(unsigned char const *byte_to_encode, unsigned int byte_length)
{
    return p_impl_->GetEdgeIBase64Encode(byte_to_encode, byte_length);
}

// 功能：通过mqtt发送消息
bool EdgeInterface::SendEdgeIMqttMessage(const std::string & mqtt_message)
{
    return p_impl_->SendEdgeIMqttMessage(mqtt_message);
}

// 功能：初始化kafka
bool EdgeInterface::InitEdgeIkafka(const std::string &brokers, const std::string &topic, int partition)
{
    return p_impl_->InitEdgeIkafka(brokers, topic, partition);
}

// 功能：通过kafka发送消息
bool EdgeInterface::SendEdgeIKafkaMessage(const std::string &kafka_message, const std::string &key)
{
    return p_impl_->SendEdgeIKafkaMessage(kafka_message, key);
}