package com.qdong.back.Threads;

import com.qdong.back.mqtt.MQTTConnect;
import com.qdong.back.service.UserMapperService;

import java.time.Duration;
import java.time.LocalDateTime;

public class UserThread extends Thread{
    private final String UserName;
    private final String UserPassword;
    private final UserMapperService userMapperService;
    private boolean flag = false;
    public UserThread(String name, String userPassword, UserMapperService userMapperService) {
        UserName=name;
        UserPassword = userPassword;
        this.userMapperService = userMapperService;
        System.out.println("Creating "+UserName );
    }
    //"Control/Out/Bump/State",             //1:室外水泵控制模式
    //                         "Control/Out/Bump/Switch",            //2:室外水泵开关
    //                         "Control/Out/Bump/Time",              //3:室外水泵单次灌溉时长
    //                         "Control/Out/Bump/Interval",          //4:室外水泵灌溉间隔
    //                         "Control/Out/Bump/StartTime",         //5:室外水泵第一次启动时间差
    //                          "Control/In/Bump/State",         //5:室内水泵控制模式
    //                          "Control/In/Bump/Switch",        //6:室内水泵开关
    //                          "Control/In/Bump/Time",          //7:室内水泵单次灌溉时长
    //                          "Control/In/Bump/Interval",      //8:室内水泵灌溉间隔
    //                          "Control/In/Bump/StartTime",     //9:室内水泵第一次开启时间
    //                          "Control/In/LED/State",          //10:室内LED控制模式
    //                          "Control/In/LED/Switch",         //11:室内LED开关
    //                          "Control/In/LED/Condition",      //12:室内LED开启条件
    //                          "Control/In/Window/State",       //13:室内天窗控制模式
    //                          "Control/In/Window/Switch",      //14:室内天窗开关
    //                          "Control/In/Window/Temperature", //15:室内天窗开启条件
    //                          "Control/In/Fan/State",          //16:室内风扇控制模式
    //                          "Control/In/Fan/Switch",         //17:室内风扇开关
    //                          "Control/In/Fan/Temperature"};   //18:室内风扇开启条件
    @Override
    public void run() {
        System.out.println("Running "+UserName );
        MQTTConnect mqttConnect = new MQTTConnect(UserName, UserPassword);
        try{
            mqttConnect.setMqttClient();
            LocalDateTime starttime=LocalDateTime.now();
            while(!flag){
                mqttConnect.sub("Control/Out/Bump/State", 0);
                mqttConnect.pub("Control/Out/Bump/State", userMapperService.OutBumpState(), 0);
                mqttConnect.sub("Control/Out/Bump/Switch", 0);
                mqttConnect.pub("Control/Out/Bump/Switch", userMapperService.OutBumpSwitch(), 0);
                mqttConnect.sub("Control/Out/Bump/Time", 0);
                mqttConnect.pub("Control/Out/Bump/Time", userMapperService.OutBumpTime(), 0);
                mqttConnect.sub("Control/Out/Bump/Interval", 0);
                mqttConnect.pub("Control/Out/Bump/Interval", userMapperService.OutBumpInterval(), 0);
                mqttConnect.sub("Control/Out/Bump/StartTime", 0);
                mqttConnect.pub("Control/Out/Bump/StartTime", userMapperService.OutBumpStartTime(), 0);
                mqttConnect.sub("Control/In/Bump/State", 0);
                mqttConnect.pub("Control/In/Bump/State", userMapperService.InBumpState(), 0);
                mqttConnect.sub("Control/In/Bump/Switch", 0);
                mqttConnect.pub("Control/In/Bump/Switch", userMapperService.InBumpSwitch(), 0);
                mqttConnect.sub("Control/In/Bump/Time", 0);
                mqttConnect.pub("Control/In/Bump/Time", userMapperService.InBumpTime(), 0);
                mqttConnect.sub("Control/In/Bump/Interval", 0);
                mqttConnect.pub("Control/In/Bump/Interval", userMapperService.InBumpInterval(), 0);
                mqttConnect.sub("Control/In/Bump/StartTime", 0);
                mqttConnect.pub("Control/In/Bump/StartTime", userMapperService.InBumpStartTime(), 0);
                mqttConnect.sub("Control/In/LED/State", 0);
                mqttConnect.pub("Control/In/LED/State", userMapperService.InLEDState(), 0);
                mqttConnect.sub("Control/In/LED/State", 0);
                mqttConnect.pub("Control/In/LED/Switch", userMapperService.InLEDSwitch(), 0);
                mqttConnect.sub("Control/In/LED/Condition", 0);
                mqttConnect.pub("Control/In/LED/Condition", userMapperService.InLEDCondition(), 0);
                mqttConnect.sub("Control/In/Window/State", 0);
                mqttConnect.pub("Control/In/Window/State", userMapperService.InWindowState(), 0);
                mqttConnect.sub("Control/In/Window/Switch", 0);
                mqttConnect.pub("Control/In/Window/Switch", userMapperService.InWindowSwitch(), 0);
                mqttConnect.sub("Control/In/Window/Temperature", 0);
                mqttConnect.pub("Control/In/Window/Temperature", userMapperService.InWindowTemperature(), 0);
                mqttConnect.sub("Control/In/Fan/State", 0);
                mqttConnect.pub("Control/In/Fan/State", userMapperService.InFanState(), 0);
                mqttConnect.sub("Control/In/Fan/Switch", 0);
                mqttConnect.pub("Control/In/Fan/Switch", userMapperService.InFanSwitch(), 0);
                mqttConnect.sub("Control/In/Fan/Temperature", 0);
                mqttConnect.pub("Control/In/Fan/Temperature", userMapperService.InFanTemperature(), 0);
                LocalDateTime endtime=LocalDateTime.now();
                if(Duration.between(starttime,endtime).getSeconds()>=1800.0){
                    userMapperService.InsertIntiandi();
                    userMapperService.InsertOuttiandi();
                    starttime=LocalDateTime.now();
                }
                Thread.sleep(1000);
            }
            mqttConnect.close();
        }catch (Exception e) {
            System.out.println("Thread " +  UserName + " interrupted.");
            System.out.println(e);
        }finally {
            System.out.println("Thread " +  UserName + " exiting.");
        }
        System.out.println("Thread " +UserName+ " exiting.");
    }
    public void exit(){
        flag = true;
    }
}
