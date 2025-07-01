

#include <iostream>
#include "fstream"
#include <algorithm>
#include <semaphore.h>

#include "edge_interface.h"

#include "json.h"   //读取配置文件时用到了
#include "base64.h" //调用了Bash64Encode(byte_to_encode, byte_length),用于对传入的字符串进行编码
#include "mosquitto.h" //使用mqtt协议进行通信
#include "kafka_producer.h" // kafka生产者

#define DGEINTERFACE_VERSION_MAJOR 0
#define DGEINTERFACE_VERSION_MINOR 4
#define DGEINTERFACE_VERSION_PATCH 6

// #define ALGORITHM_CONFIG_JSON   "algorithm_config.json"
#define ALGORITHM_CONFIG_JSON "peripheral_config.json"
#define AlGORITHM_LABELS_TXT "labels.txt"
#define GLOBAL_CONFIG_JSON "global_config.json"

#define MQTT_KEEP_ALIVE 60
#define MQTT_EDGE_TOPIC "/edge/detect/alarm_message"

enum InputType
{
	CAMERA_V4L2 = 1,
	URI = 2,
	MULTI_URI = 3,
	RTSP = 4,
	CAMERA_CSI = 5
};

struct EdgeInterface::Impl {  // 实现了对edge_interface.h中的Impl的实现
    public:
        void InitEdgeI(const std::string & algorithm_config_path, const std::string & global_config_path); //初始化函数实现
        EdgeInterfaceData GetEdgeIData(); //读取配置参数并赋值
        
        std::string GetEdgeIBase64Encode(unsigned char const *byte_to_encode, unsigned int byte_length); //对字符串进行编码

        bool SendEdgeIMqttMessage(const std::string & mqtt_message); // 发送消息， 是message格式
        
        bool InitEdgeIkafka(const std::string &brokers, const std::string &topic, int partition); // 初始化kafka

        bool SendEdgeIKafkaMessage(const std::string &kafka_message, const std::string &key); // 通过kafka发送消息


    private:
        void ParseAlgorithmConfigJson(); //算法参数

        void ParseGlobalConfigJson(const std::string & global_config_path); //全局参数 

        std::vector<std::string> ReadLabels(const std::string & label_filename); //读取标签文件到labels_string中

        std::string algorithm_config_path; // [InitEdgeI()得到，传入的参数]  

        std::string algorithm_labels_path; // [InitEdgeI()得到，传入的参数]

        std::string global_config_path; // [InitEdgeI()得到]    EdgeInterfaceData中只有一个algorithm_config_path

        mosquitto *p_mqtt_ = nullptr; //设置一个mqtt指针

        EdgeInterfaceData edge_interface_data; //边缘信息结构体，用于初始化中的中间存储，最后传递给GetEdgeIData()函数

        std::shared_ptr<KafkaProducer> p_producer_; // kafka生产者
};
