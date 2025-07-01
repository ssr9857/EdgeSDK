/**
 * @file kafka_producer.cpp
 * @author czhazha 
 * @brief 
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024 seaway
 */
#include "kafka_producer.h"

// 通过回调函数提供消息的交付报告，以便生产者能够了解消息是否成功发送到kafka服务器，并根据需要采取相应的处理措施
class ProducerDeliveryReportCb : public RdKafka::DeliveryReportCb
{
public:
	void dr_cb(RdKafka::Message &message)
	{
		if(message.err())
			std::cerr << "Message delivery failed: " << message.errstr() << std::endl;
		else
		{
			// Message delivered to topic test [0] at offset 135000
			std::cerr << "Message delivered to topic " << message.topic_name()
				<< " [" << message.partition() << "] at offset "
				<< message.offset() << std::endl;
		}
	}
};

// 通过回调函数提供对生产者与kafka集群交互过程中不同类型事件的处理逻辑，以便生产者能够根据具体情况进行相应的处理和记录
class ProducerEventCb : public RdKafka::EventCb
{
public:
	void event_cb(RdKafka::Event &event)
	{
		switch (event.type())
		{
            // 输出错误信息
		case RdKafka::Event::EVENT_ERROR:
			std::cout << "RdKafka::Event::EVENT_ERROR: " << RdKafka::err2str(event.err()) << std::endl;
			break;
            // 输出统计信息
		case RdKafka::Event::EVENT_STATS:
			//std::cout << "RdKafka::Event::EVENT_STATS: " << event.str() << std::endl;
			break;
            // 输出日志信息
		case RdKafka::Event::EVENT_LOG:
			std::cout << "RdKafka::Event::EVENT_LOG " << event.fac() << std::endl;
			break;
            // 输出节流信息
		case RdKafka::Event::EVENT_THROTTLE:
			std::cout << "RdKafka::Event::EVENT_THROTTLE " << event.broker_name() << std::endl;
			break;
		}
	}
};

/*
Partitioner Callback在kafka生产者发送信息时调用，它会根据指定的分区策略为每条信息选择一个合适的分区，
确保相同的key的消息总是被路由到同一个分区，从而保证消息的顺序性和一致性。
这里的HashPartitionerCb使用了Hash函数将key转换为一个整数，并对partition_cnt取模得到分区编号
*/
class HashPartitionerCb : public RdKafka::PartitionerCb
{
public:
	int32_t partitioner_cb(const RdKafka::Topic *topic, const std::string *key,
		int32_t partition_cnt, void *msg_opaque)
	{
		char msg[128] = { 0 };
		int32_t partition_id = generate_hash(key->c_str(), key->size()) % partition_cnt;
		//                          [topic][key][partition_cnt][partition_id] 
		//                          :[test][6419][2][1]
		sprintf(msg, "HashPartitionerCb:topic:[%s], key:[%s]partition_cnt:[%d], partition_id:[%d]", topic->name().c_str(),
			key->c_str(), partition_cnt, partition_id);
		std::cout << msg << std::endl;
		return partition_id;
	}
private:

	static inline unsigned int generate_hash(const char *str, size_t len)
	{
		unsigned int hash = 5381;
		for (size_t i = 0; i < len; i++)
			hash = ((hash << 5) + hash) + str[i];
		return hash;
	}
};

KafkaProducer::KafkaProducer(const std::string& brokers, const std::string& topic, int partition)
{
	m_brokers = brokers;
	m_topicStr = topic;
	m_partition = partition;

	/* 创建Kafka Conf对象 */
	m_config = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
	if(m_config==NULL)
		std::cout << "Create RdKafka Conf failed." << std::endl;

	/* 创建Topic Conf对象 */
	m_topicConfig = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
	if (m_topicConfig == NULL)
		std::cout << "Create RdKafka Topic Conf failed." << std::endl;

	/* 设置Broker属性 */
	RdKafka::Conf::ConfResult errCode;
	std::string errorStr;
	m_dr_cb = new ProducerDeliveryReportCb;
	// 设置dr_cb属性值
	errCode = m_config->set("dr_cb", m_dr_cb, errorStr);
	if (errCode != RdKafka::Conf::CONF_OK)
	{
		std::cout << "Conf set failed:" << errorStr << std::endl;
	}
	// 设置event_cb属性值
	m_event_cb = new ProducerEventCb;
	errCode = m_config->set("event_cb", m_event_cb, errorStr);
	if (errCode != RdKafka::Conf::CONF_OK)
	{
		std::cout << "Conf set failed:" << errorStr << std::endl;
	}
	// 自定义分区策略
	m_partitioner_cb = new HashPartitionerCb;
	errCode = m_topicConfig->set("partitioner_cb", m_partitioner_cb, errorStr);
	if (errCode != RdKafka::Conf::CONF_OK)
	{
		std::cout << "Conf set failed:" << errorStr << std::endl;
	}
	// 设置配置对象的属性值
	errCode = m_config->set("statistics.interval.ms", "10000", errorStr);
	if (errCode != RdKafka::Conf::CONF_OK)
	{
		std::cout << "Conf set failed:" << errorStr << std::endl;
	}
	errCode = m_config->set("message.max.bytes", "10240000", errorStr);
	if (errCode != RdKafka::Conf::CONF_OK)
	{
		std::cout << "Conf set failed:" << errorStr << std::endl;
	}
	errCode = m_config->set("bootstrap.servers", m_brokers, errorStr);
	if (errCode != RdKafka::Conf::CONF_OK)
	{
		std::cout << "Conf set failed:" << errorStr << std::endl;
	}

	/* 创建Producer */
	m_producer = RdKafka::Producer::create(m_config, errorStr);
	if (m_producer == NULL)
	{
		std::cout << "Create Producer failed:" << errorStr << std::endl;
	}

	/* 创建Topic对象 */
	m_topic = RdKafka::Topic::create(m_producer, m_topicStr, m_topicConfig, errorStr);
	if (m_topic == NULL)
	{
		std::cout << "Create Topic failed:" << errorStr << std::endl;
	}
}

KafkaProducer::~KafkaProducer()
{
	// while (m_producer->outq_len() > 0)
	// {
	// 	std::cerr << "Waiting for " << m_producer->outq_len() << std::endl;
	// 	m_producer->flush(5000);
	// }
	delete m_config;
	delete m_topicConfig;
	delete m_topic;
	delete m_producer;
	delete m_dr_cb;
	delete m_event_cb;
	delete m_partitioner_cb;
}

void KafkaProducer::pushMessage(const std::string& str, const std::string& key)
{
    /*
    1、首先，计算消息内容的长度，并将消息内容的指针转换为void*类型。
    2、调用m_producer->produce()方法将消息发送到指定的主题(m_topic)和分区(RdKafka::Topic::PARTITION_UA,即使用未指定分区的模式)
    3、在调用producer()方法后，通过调用m_producer->poll(0)来触发Kafka生产者的内部事件处理，确保消息得到发送。
    4、检查produce()方法的返回值errorcode是否为RdKafka::ERR_NO_ERROR，如果不是则表示消息发送失败。
    5、如果errorCode为Rdkafka::ERR_QUEUE_FULL，表示队列已满，此时再次调用m_producer->poll(100)来等待一段时间，以便给队列腾出空间。
    6、如果errorCode为其他错误，表示发送过程中出现了其他问题，将输出错误信息到标准错误流(std::cerr)。
    */
	int32_t len = str.length();
	void* payload = const_cast<void*>(static_cast<const void*>(str.data()));
	RdKafka::ErrorCode errorCode = m_producer->produce(
		m_topic,
		RdKafka::Topic::PARTITION_UA,
		RdKafka::Producer::RK_MSG_COPY,
		payload,
		len,
		&key,
		NULL);
	m_producer->poll(0);
	if (errorCode != RdKafka::ERR_NO_ERROR)
	{
		std::cerr << "Produce failed: " << RdKafka::err2str(errorCode) << std::endl;
		if (errorCode == RdKafka::ERR__QUEUE_FULL)
		{
			m_producer->poll(100);
		}
	}
    // else
    // {
    //     std::cout << "Produce success" << std::endl;
    // }
}
