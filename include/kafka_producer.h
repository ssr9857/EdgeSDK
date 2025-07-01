/**
 * @file kafka_producer.h
 * @author czhazha 
 * @brief 
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024 seaway
 */
#ifndef KAFKAPRODUCER_H
#define KAFKAPRODUCER_H

#pragma once  //
#include <string>
#include <iostream>
#include "rdkafkacpp.h"

class KafkaProducer  // 用于与Kafka消息队列交互
{
public:
	/**
	* @brief KafkaProducer
	* @param brokers
	* @param topic
	* @param partition
	*/
	explicit KafkaProducer(const std::string& brokers, const std::string& topic, int partition);
	/**
	* @brief push Message to Kafka
	* @param str, message data
	*/
	void pushMessage(const std::string& str, const std::string& key);
	~KafkaProducer();

private:
	std::string m_brokers;			// Broker列表，多个使用逗号分隔
	std::string m_topicStr;			// Topic名称
	int m_partition;				// 分区

	RdKafka::Conf* m_config;        // Kafka Conf对象
	RdKafka::Conf* m_topicConfig;   // Topic Conf对象
	RdKafka::Topic* m_topic;		// Topic对象
	RdKafka::Producer* m_producer;	// Producer对象

	/*只要看到Cb 结尾的类，要继承它然后实现对应的回调函数*/
	RdKafka::DeliveryReportCb* m_dr_cb;         // 处理消息的交付报告回调
	RdKafka::EventCb* m_event_cb;               // 用于处理生产者事件的回调，以便在生产者与kafka集群交互过程中进行相应的处理
	RdKafka::PartitionerCb* m_partitioner_cb;   // 根据消息的key值计算出该消息所属的分区编号
};

#endif

