package com.qdong.back.mqtt;

import org.eclipse.paho.client.mqttv3.*;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class MQTTConnect {

    private final String HOST = "tcp://47.108.250.206:1883"; //mqtt服务器的地址和端口号
    private final String clientId = "DC" + (int) (Math.random() * 100000000);

    private final String userName;
    private final String userPassword;
    private MqttClient mqttClient;

    public MQTTConnect(String userName, String userPassword) {
        this.userName = userName;
        this.userPassword = userPassword;
    }
    public void setMqttClient(MqttCallback mqttCallback) throws MqttException {
        MqttConnectOptions options = mqttConnectOptions();
        if (mqttCallback == null) {
            mqttClient.setCallback(new Callback());
        } else {
            mqttClient.setCallback(mqttCallback);
        }
        mqttClient.connect(options);
    }

    /**
     * MQTT连接参数设置
     */
    private MqttConnectOptions mqttConnectOptions() throws MqttException {
        mqttClient = new MqttClient(HOST, clientId, new MemoryPersistence());
        MqttConnectOptions options = new MqttConnectOptions();
        options.setUserName(this.userName);
        options.setPassword(this.userPassword.toCharArray());
        options.setConnectionTimeout(10);///默认：30
        options.setAutomaticReconnect(true);//默认：false
        options.setCleanSession(false);//默认：true
        //options.setKeepAliveInterval(20);//默认：60
        return options;
    }

    /**
     * 关闭MQTT连接
     */
    public void close() throws MqttException {
        mqttClient.disconnect();
        mqttClient.close();
    }

    /**
     * 向某个主题发布消息 默认qos：1
     *
     * @param topic:发布的主题
     * @param msg：发布的消息
     */
    public void pub(String topic, String msg) throws MqttException {
        MqttMessage mqttMessage = new MqttMessage();
        mqttMessage.setQos(0);
        mqttMessage.setPayload(msg.getBytes());
        MqttTopic mqttTopic = mqttClient.getTopic(topic);
        MqttDeliveryToken token = mqttTopic.publish(mqttMessage);
        token.waitForCompletion();
    }

    /**
     * 向某个主题发布消息
     *
     * @param topic: 发布的主题
     * @param msg:   发布的消息
     * @param qos:   消息质量    Qos：0、1、2
     */
    public void pub(String topic, String msg, int qos) throws MqttException {
        MqttMessage mqttMessage = new MqttMessage();
        mqttMessage.setQos(qos);
        mqttMessage.setPayload(msg.getBytes());
        MqttTopic mqttTopic = mqttClient.getTopic(topic);
        MqttDeliveryToken token = mqttTopic.publish(mqttMessage);
        token.waitForCompletion();
    }

    /**
     * 订阅某一个主题 ，此方法默认的的Qos等级为：1
     *
     * @param topic 主题
     */
    public void sub(String topic) throws MqttException {
        mqttClient.subscribe(topic);
    }

    /**
     * 订阅某一个主题，可携带Qos
     *
     * @param topic 所要订阅的主题
     * @param qos   消息质量：0、1、2
     */
    public void sub(String topic, int qos) throws MqttException {
        mqttClient.subscribe(topic, qos);
    }
}

