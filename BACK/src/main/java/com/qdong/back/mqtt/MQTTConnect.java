package com.qdong.back.mqtt;

import org.eclipse.paho.client.mqttv3.*;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class MQTTConnect {

    private final String HOST = "tcp://localhost:1883"; //mqtt服务器的地址和端口号
    private final String clientId = "DC1";

    private final String userName;
    private final String userPassword;
    private MqttClient mqttClient;

    private Callback callback;
    public MQTTConnect(String userName, String userPassword) {
        this.userName = userName;
        this.userPassword = userPassword;
    }
    public void setMqttClient() throws MqttException {
        MqttConnectOptions options = mqttConnectOptions();
        if (callback == null) {
            mqttClient.setCallback(new Callback());
        } else {
            mqttClient.setCallback(callback);
        }
        mqttClient.connect(options);
    }
    private MqttConnectOptions mqttConnectOptions() throws MqttException {
        mqttClient = new MqttClient(HOST, clientId, new MemoryPersistence());
        MqttConnectOptions options = new MqttConnectOptions();
        options.setUserName(this.userName);
        options.setPassword(this.userPassword.toCharArray());
        options.setConnectionTimeout(30);///默认：30
        options.setAutomaticReconnect(true);//默认：false
        options.setCleanSession(false);//默认：true
        options.setKeepAliveInterval(60);//默认：60
        return options;
    }
    public void close() throws MqttException {
        mqttClient.disconnect();
        mqttClient.close();
    }
    public void pub(String topic, String msg) throws MqttException {
        MqttMessage mqttMessage = new MqttMessage();
        mqttMessage.setQos(0);
        mqttMessage.setPayload(msg.getBytes());
        MqttTopic mqttTopic = mqttClient.getTopic(topic);
        MqttDeliveryToken token = mqttTopic.publish(mqttMessage);
        token.waitForCompletion();
    }
    public void pub(String topic, String msg, int qos) throws MqttException {
        MqttMessage mqttMessage = new MqttMessage();
        mqttMessage.setQos(qos);
        mqttMessage.setPayload(msg.getBytes());
        MqttTopic mqttTopic = mqttClient.getTopic(topic);
        MqttDeliveryToken token = mqttTopic.publish(mqttMessage);
        token.waitForCompletion();
    }
    public void sub(String topic) throws MqttException {
        mqttClient.subscribe(topic);
    }
    public void sub(String topic, int qos) throws MqttException {
        mqttClient.subscribe(topic, qos);
    }
}

