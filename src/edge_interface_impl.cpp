

#include "edge_interface_impl.h"
#include <iostream>
/**
 * @file edge_interface_impl.cpp
 * @author sushenran
 * 
 */

// 功能：初始化，配置所有参数
void EdgeInterface::Impl::InitEdgeI(const std::string & algorithm_config_path, const std::string & algorithm_labels_path)
{
    
    std::cout << "EdgeInterface Version: " << DGEINTERFACE_VERSION_MAJOR <<"."<< DGEINTERFACE_VERSION_MINOR <<"."<< DGEINTERFACE_VERSION_PATCH <<std::endl;
    // std::stringstream 是一个输入/输出流类，用于在内存中读写字符串数据
    std::stringstream edge_interface_version;
    edge_interface_version << DGEINTERFACE_VERSION_MAJOR <<"."<< DGEINTERFACE_VERSION_MINOR <<"."<< DGEINTERFACE_VERSION_PATCH ; 
    this->edge_interface_data.edge_interface_version = edge_interface_version.str(); 

    
    // F_OK 用于检查文件是否存在，R_OK、W_OK 和 X_OK，分别用于检查读、写和执行权限。
    if(access(algorithm_config_path.c_str(), F_OK) == -1)
    {
        std::cout << "File EdgeInterface Init ERROR" << algorithm_config_path << ",not exist!" <<std::endl;
        exit(0);
    }
    std::cout << "algorithm_config.json path = " << algorithm_config_path << std::endl;
    this->algorithm_config_path = algorithm_config_path;  
    this->edge_interface_data.algorithm_config_path = algorithm_config_path; 
    this->algorithm_labels_path = algorithm_labels_path; 
    do
    {
        this->ParseAlgorithmConfigJson();   // 调用算法（外设）参数配置
        sleep(1);
    }while(this->edge_interface_data.camera_url.empty());
    std::cout << "ParseAlgorithmConfigJson success" << std::endl;

    this->global_config_path = algorithm_config_path; 
    if(access(global_config_path.c_str(), F_OK) == -1)
    {
        std::cout << "FileEdgeInterface Init ERROR " << global_config_path << ",not exist!" <<std::endl;
        this->edge_interface_data.global_config_enable = false; 
    }
    this->edge_interface_data.global_config_enable = true; 

    std::cout << "global_config.json path" << global_config_path << std::endl;
    this->ParseGlobalConfigJson(global_config_path); // 调用全局参数配置
    std::cout << "ParseGlobalConfigJson success" << std::endl;

}

// 功能：读取算法参数配置  
void EdgeInterface::Impl::ParseAlgorithmConfigJson()
{
    
    std::string algorithm_config_relative_path = this->algorithm_config_path + ALGORITHM_CONFIG_JSON; 
    std::string algorithm_labels_relative_path = this->algorithm_labels_path + AlGORITHM_LABELS_TXT; 

    if((algorithm_config_relative_path.find(".json") == std::string::npos) || (access(algorithm_config_relative_path.c_str(),F_OK|R_OK) == -1))
    {
        std::cout << "algorithm_config file is not exist!" << algorithm_config_relative_path << std::endl;
        return;
    }

    //即从文件中读取数据
    std::ifstream config(algorithm_config_relative_path, std::ios::in);
    if(!config.is_open())
    {
        std::cout << "algorithm_config.json file is not open!" << algorithm_config_relative_path << std::endl;
    }
    Json::Reader reader;
    Json::Value root;
    
    // getenv 获取指定环境变量的值。它接受一个字符串参数并返回指针。
    this->edge_interface_data.algorithm_deployname = getenv("_OS_APP_"); 
    this->edge_interface_data.algorithm_namespace = getenv("_OS_NAMESPACE_");

    std::string output_mount_url = "/mainstream";
    std::cout << "output_mount_url = " << output_mount_url << std::endl;
    this->edge_interface_data.output_mount_url = output_mount_url;
    std::vector<std::string> labels_converted = ReadLabels(algorithm_labels_relative_path);
    //clear仅仅是删除元素，空间并未释放，而swap不仅仅清空，而空间也缩减为0. 
    std::vector<std::string>().swap(this->edge_interface_data.camera_url); 

    if(reader.parse(config, root))
    { 
        std::cout << "camrea size：" << root["links"].size() << std::endl; 
        try{
            for(unsigned int input_index = 0; input_index < root["links"].size(); input_index++ )
            {
                Json::Value camera_id = root["links"][input_index]["device"]["id"];
                this->edge_interface_data.camera_id.push_back(camera_id.asString());  

                Json::Value camera_name = root["links"][input_index]["device"]["name"];
                this->edge_interface_data.camera_name.push_back(camera_name.asString());

                Json::Value camera_url = root["links"][input_index]["device"]["url"];
                this->edge_interface_data.camera_url.push_back(camera_url.asString());

                std::cout<< "camera_id：" << camera_id.asString() << "camera_name：" << camera_name.asString() << "input_url：" << camera_url.asString() << std::endl;


                // 处理真实值配置参数
                if(!root["links"][input_index]["setting"]["roi"].empty()) 
                {
                    Json::Value camera_roi = root["links"][input_index]["setting"]["roi"];
                    this->edge_interface_data.camera_roi.push_back(camera_roi.asString());
                    for(auto label_thresh : labels_converted)
                    {
                        std::cout<< "label_thresh: " << label_thresh << std::endl; 
                        if(root["links"][input_index]["setting"].isMember(label_thresh))
                        {
                            Json::Value label_thresh_value = root["links"][input_index]["setting"][label_thresh];
                            std::map<std::string, float> label_thresh_map = {{label_thresh,label_thresh_value.asFloat()}};
                            this->edge_interface_data.labels_thresh.insert(std::pair<int, std::map<std::string, float>>(input_index,label_thresh_map));
                            // 赋值json中的xxxThreshold给labels_thresh
                        }
                    }

                    // 报警开启时间设置 
                    Json::Value camera_statistics_start_time = root["links"][input_index]["setting"]["statisticsStartTime"];
                    this->edge_interface_data.camera_statistics_start_time.push_back(camera_statistics_start_time.asString());
                    //赋值json中的statisticsStartTime给camera_statistics_start_time
                    // （前者是配置文件中对应内容，后者是EdgeData中对应的变量）
                    
                    // 报警停止时间设置
                    Json::Value camera_statistics_end_time = root["links"][input_index]["setting"]["StatisticsEndTime"];
                    this->edge_interface_data.camera_statistics_end_time.push_back(camera_statistics_end_time.asString());
                    //赋值StatisticsEndTime给camera_statistics_end_time

                    // conf阈值设置
                    Json::Value camera_conf_config_threshold = root["links"][input_index]["setting"]["confThreshold"];
                    this->edge_interface_data.camera_conf_config_threshold.push_back(camera_conf_config_threshold.asFloat());
                    //赋值json中的confThreshold给camera_conf_config_threshold
                    
                    // NMS阈值设置
                    Json::Value camera_nms_config_threshold = root["links"][input_index]["setting"]["nmsThreshold"];
                    this->edge_interface_data.camera_nms_config_threshold.push_back(camera_nms_config_threshold.asFloat());
                    //赋值nmsThreshold给camera_nms_config_threshold

                    // 是否开启当前视频源本地显示
                    Json::Value camera_frame_show_local = root["links"][input_index]["setting"]["FrameShowLocal"]; 
                    this->edge_interface_data.camera_frame_show_local.push_back(camera_frame_show_local.asBool());
                    //赋值FrameShowLocal给camera_frame_show_local

                    // 是否开启首次报警上报
                    Json::Value camera_alarm_smooth = root["links"][input_index]["setting"]["AlarmSmooth"];
                    this->edge_interface_data.camera_alarm_smooth.push_back(camera_alarm_smooth.asBool());
                    //赋值AlarmSmooth给camera_alarm_smooth

                    // 报警间隔帧数设置
                    Json::Value camera_alarm_interval = root["links"][input_index]["setting"]["AlarmInterval"];
                    this->edge_interface_data.camera_alarm_interval.push_back(camera_alarm_interval.asInt());
                    //赋值AlarmInterval给camera_alarm_interval

                    // // 识别间隔帧数设置
                    Json::Value camera_frame_interval = root["links"][input_index]["setting"]["FrameInterval"];
                    this->edge_interface_data.camera_frame_interval.push_back(camera_frame_interval.asInt());
                    //赋值FrameInterval给camera_frame_interval


                }
                else //设置默认值
                {
                    Json::Value camera_roi = "POLYGON((0.0 0.0,1.0 0.0,1.0 1.0,0.0 1.0,0.0 0.0))";
                    this->edge_interface_data.camera_roi.push_back(camera_roi.asString());
                    for(auto label_thresh : labels_converted)
                    {
                        Json::Value label_thresh_value = 0.6; // 标签阈值的默认值
                        std::map<std::string, float> label_thresh_map = {{label_thresh, label_thresh_value.asFloat()}};
                        this->edge_interface_data.labels_thresh.insert(std::pair<int, std::map<std::string, float>>(input_index, label_thresh_map));
                    }

                    Json::Value camera_statistics_start_time = "00:00:00";
                    this->edge_interface_data.camera_statistics_start_time.push_back(camera_statistics_start_time.asString());
                    
                    Json::Value camera_statistics_end_time = "23:59:59";
                    this->edge_interface_data.camera_statistics_end_time.push_back(camera_statistics_end_time.asString());

                    Json::Value camera_conf_config_threshold = 0.4;
                    this->edge_interface_data.camera_conf_config_threshold.push_back(camera_conf_config_threshold.asFloat());
                    
                    Json::Value camera_nms_config_threshold = 0.4;
                    this->edge_interface_data.camera_nms_config_threshold.push_back(camera_nms_config_threshold.asFloat());

                    Json::Value camera_frame_show_local = false; // 本地显示
                    this->edge_interface_data.camera_frame_show_local.push_back(camera_frame_show_local.asBool());

                    Json::Value camera_alarm_smooth = false; // 警告首次上报
                    this->edge_interface_data.camera_alarm_smooth.push_back(camera_alarm_smooth.asBool());

                    Json::Value camera_alarm_interval = 0; // 警告间隔
                    this->edge_interface_data.camera_alarm_interval.push_back(camera_alarm_interval.asInt());

                    Json::Value camera_frame_interval = 0; // 帧间隔
                    this->edge_interface_data.camera_frame_interval.push_back(camera_frame_interval.asInt());


                }
                std::cout << "config for camera " << camera_id.asString() << " is:" << "input_index : " << input_index << std::endl;
                for(auto label_thresh : labels_converted) 
                {
                    if(root["links"][input_index]["setting"].isMember(label_thresh)) //输出例：CarThreshold = 0.6
                    {
                        std::cout<< label_thresh << " = " << root["links"][input_index]["setting"][label_thresh].asFloat() << std::endl;
                    }
                    else{
                        std::cout<< label_thresh << " = null " << std::endl;
                    }
                }
                std::cout << "   StatisticsStartTime   = " << this->edge_interface_data.camera_statistics_start_time[input_index] << std::endl;
                std::cout << "   StatisticsEndTime     = " << this->edge_interface_data.camera_statistics_end_time[input_index] << std::endl;
                std::cout << "   confThreshold         = " << this->edge_interface_data.camera_conf_config_threshold[input_index] << std::endl;
                std::cout << "   nmsThreshold          = " << this->edge_interface_data.camera_nms_config_threshold[input_index] << std::endl;

                std::cout << "   FrameShowLocal        = " << this->edge_interface_data.camera_frame_show_local[input_index] << std::endl;
                std::cout << "   AlarmSmooth           = " << this->edge_interface_data.camera_alarm_smooth[input_index] << std::endl;

                std::cout << "   AlarmInterval         = " << this->edge_interface_data.camera_alarm_interval[input_index] << std::endl;
                std::cout << "   FrameInterval         = " << this->edge_interface_data.camera_frame_interval[input_index] << std::endl;
                
            }
        }catch(std::string error){
            config.close();
            std::cout << "config:<" << algorithm_config_relative_path << "> context ERROR:" << error << "!!" << std::endl;
        }
    }else{
        std::cout << "config:<" << algorithm_config_relative_path << "> Json file parse ERROR" << std::endl;
    }
}

// 功能：全局参数配置
void EdgeInterface::Impl::ParseGlobalConfigJson(const std::string & global_config_path)
{
    std::string global_config_relative_path = this->global_config_path + GLOBAL_CONFIG_JSON; 
    
    if((global_config_relative_path.find(".json") == std::string::npos) || access(global_config_relative_path.c_str(), F_OK|R_OK) == -1)
    {
        std::cout << "global config file is not exist" << global_config_relative_path << std::endl;
        return;
    }

    std::ifstream config(global_config_relative_path, std::ios::in);
    if(!config.is_open())
    {
        std::cout << "global config file is not open" << global_config_relative_path << std::endl;
    }

    Json::Reader reader;
    Json::Value root;

    if(reader.parse(config, root))
    {
        try{
            this->edge_interface_data.global_encode_frame_rate = root["global_encode_frame_rate"].asInt(); // 往rstp服务器推送的帧率

            this->edge_interface_data.global_nvr_enable        = root["global_nvr_enable"].asBool(); // nvr设备配置（海康威视摄像头）
            this->edge_interface_data.global_nvr_ip            = root["global_nvr_ip"].asString();
            this->edge_interface_data.global_nvr_port          = root["global_nvr_port"].asInt();
            this->edge_interface_data.global_nvr_user           = root["global_nvr_user"].asString(); 
            this->edge_interface_data.global_nvr_password       = root["global_nvr_password"].asString(); 
            this->edge_interface_data.global_nvr_duration       = root["global_nvr_duration"].asInt();

            this->edge_interface_data.global_minio_server       = root["global_minio_server"].asString(); // minio配置，存储视频数据
            this->edge_interface_data.global_minio_access_key   = root["global_minio_access_key"].asString();
            this->edge_interface_data.global_minio_secret_key   = root["global_minio_secret_key"].asString();

            this->edge_interface_data.global_kafka_broker       = root["global_kafka_broker"].asString(); // fafka消息通信
            this->edge_interface_data.global_kafka_topic        = root["global_kafka_topic"].asString();

            this->edge_interface_data.global_osd_enable         = root["global_osd_enable"].asBool(); // 本地OSD展示，视频画面上叠加显示文本


        }catch(std::string error){
            config.close();
            std::cout << "    config" << global_config_relative_path << "> context ERROR:" << error << "!!" << std::endl;
        }
        std::cout << "         global_encode_frame_rate  = " << this->edge_interface_data.global_encode_frame_rate << std::endl; 

        std::cout << "         global_nvr_enable         = " << this->edge_interface_data.global_nvr_enable << std::endl;
        std::cout << "         global_nvr_ip             = " << this->edge_interface_data.global_nvr_ip << std::endl;
        std::cout << "         global_nvr_port           = " << this->edge_interface_data.global_nvr_port << std::endl;
        std::cout << "         global_nvr_user           = " << this->edge_interface_data.global_nvr_user << std::endl;
        std::cout << "         global_nvr_password       = " << this->edge_interface_data.global_nvr_password << std::endl;
        std::cout << "         global_nvr_duration       = " << this->edge_interface_data.global_nvr_duration << std::endl;

        std::cout << "         global_minio_server       = " << this->edge_interface_data.global_minio_server << std::endl;
        std::cout << "         global_minio_access_key   = " << this->edge_interface_data.global_minio_access_key << std::endl;
        std::cout << "         global_minio_secret_key   = " << this->edge_interface_data.global_minio_secret_key << std::endl;

        std::cout << "         global_kafka_broker       = " << this->edge_interface_data.global_kafka_broker << std::endl;
        std::cout << "         global_kafka_topic        = " << this->edge_interface_data.global_kafka_topic << std::endl;

        std::cout << "         global_osd_enable         = " << this->edge_interface_data.global_osd_enable << std::endl;
    }
    else{
        std::cout << "    config<" << global_config_relative_path << "> Json file parse ERROR!" << std::endl;
    }


}

// 功能：用于获取赋值后的参数信息体
EdgeInterfaceData EdgeInterface::Impl::GetEdgeIData()
{
    return this->edge_interface_data;
}

// 功能：读取标签文件 labels.txt 存入（传入的是该文件的直接地址,不是路径）
std::vector<std::string> EdgeInterface::Impl::ReadLabels(const std::string & labels_filename) 
{
    
    std::ifstream labels_file(labels_filename, std::ios::in);
    if(!labels_file.is_open()){
        std::cout << "label file is not open " << labels_filename << std::endl;
    }
    std::vector<std::string> labels_converted;
    std::string line; 
    while(getline(labels_file, line))
    {
        this->edge_interface_data.labels_string.push_back(line); 
        line = line + "Threshold";
        labels_converted.push_back(line.c_str());
        std::cout<< "get thresh: " << line << std::endl;
    }

    return labels_converted;
}

// 功能：对字符串进行编码
std::string EdgeInterface::Impl::GetEdgeIBase64Encode(unsigned char const *byte_to_encode, unsigned  byte_length) 
{
    return Base64Encode(byte_to_encode, byte_length);
}

// 功能：通过mqtt发送消息（用于轻量级，高延迟，低带宽设备的消息传输协议）
bool EdgeInterface::Impl::SendEdgeIMqttMessage(const std::string & mqtt_message)
{
    int error_code = 0; //用于存储MQTT操作返回的错误码

    if(p_mqtt_ == nullptr)
    {
        std::cout << "SetEdgeIMqttInit" << std::endl;

        const char* mqtt_host;
        int mqtt_port;
        const char* kubernetesHost = std::getenv("KUBERNETES_SERVICE_HOST");
        //MQTT服务器设置
        if (kubernetesHost != nullptr) {
            // 环境变量 KUBERNETES_SERVICE_HOST 存在
            mqtt_host = "mosquitto.default";
            mqtt_port = 1883;
            std::cout << "mqtt_host: " << mqtt_host << std::endl;
            std::cout << "mqtt_port: " << mqtt_port << std::endl;
        } else {
            // 环境变量 KUBERNETES_SERVICE_HOST 不存在
            mqtt_host = "localhost";
            mqtt_port = 9883;
            std::cout << "mqtt_host: " << mqtt_host << std::endl;
            std::cout << "mqtt_port: " << mqtt_port << std::endl;
        }
        // MQTT库初始化
        error_code = mosquitto_lib_init();
        if (error_code < 0){
            printf("mosquitto lib int fail...");
        }
        // 创建MQTT客户端实例
        p_mqtt_ = mosquitto_new(NULL, true, NULL);
        if (p_mqtt_ == NULL){
            printf("create client failed...\n");
            error_code = -1;
        }
        // 链接MQTT服务器
        error_code = mosquitto_connect(p_mqtt_, mqtt_host, mqtt_port, MQTT_KEEP_ALIVE); //默认值为60
        if (error_code < 0){
            printf("connect fail");
        }
        // 启动客户端网络循环，用于接受消息
        error_code = mosquitto_loop_start(p_mqtt_);
        if(error_code != MOSQ_ERR_SUCCESS){ //默认值为0
            printf("mosquitto loop error\n");
        }
        std::cout << "mosquitto loop init success" << std::endl;
    }

    error_code = mosquitto_publish(p_mqtt_, NULL, MQTT_EDGE_TOPIC, mqtt_message.length(), mqtt_message.c_str(), 0, 0);
    if(error_code == MOSQ_ERR_SUCCESS)
        return true;
    else
    {
        std::cout << "SendEdgeIMqttMessage mosquitto_publish return error_code = " << strerror(error_code) << std::endl;
        return false;
    }
}

// 功能：对kafka库进行初始化
bool EdgeInterface::Impl::InitEdgeIkafka(const std::string & brokers, const std::string & topic, int partition)
{
    std::cout << "InitEdgeIKafka" << std::endl;
    p_producer_ = std::make_shared<KafkaProducer>(brokers, topic, partition);
    return true;
}

// 功能：生产者发送消息
bool EdgeInterface::Impl::SendEdgeIKafkaMessage(const std::string & kafka_message, const std::string & key)
{
    p_producer_->pushMessage(kafka_message, key);
    return true;
}













  