package com.qdong.back.Threads;

import com.qdong.back.mqtt.MQTTConnect;
import com.qdong.back.object.*;
import com.qdong.back.service.UserMapperService;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;
import org.springframework.beans.factory.annotation.Autowired;

public class UserThread extends Thread{
    private UserMapperService userMapperService;
    private final String UserName;
    private final String UserPassword;
    private boolean flag = false;
    public UserThread(String name, String userPassword, UserMapperService userMapperService) {
        UserName=name;
        UserPassword = userPassword;
        this.userMapperService = userMapperService;
        System.out.println("Creating "+UserName );
    }
    @Override
    public void run() {
        System.out.println("Running "+UserName );
        MQTTConnect mqttConnect = new MQTTConnect(UserName, UserPassword);
        try{
            mqttConnect.setMqttClient(null);
            while(!flag){
                Data data = new Data(1,1,1,1,1,1,1,1,1,1,1,1);
                Fan fan = userMapperService.getFan().get(0);
                mqttConnect.sub("test", 0);
                mqttConnect.pub("test", data.toString()+fan.toString(), 0);
                Thread.sleep(1000);
            }
            mqttConnect.close();
        }catch (MqttException | InterruptedException e) {
            System.out.println("Thread " +  UserName + " interrupted.");
        }finally {
            System.out.println("Thread " +  UserName + " exiting.");
        }
        System.out.println("Thread " +UserName+ " exiting.");
    }
    public void exit(){
        flag = true;
    }
}
