package com.qdong.back.service;

import com.qdong.back.mapper.UserMapper;
import com.qdong.back.object.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class UserMapperService{
    @Autowired
    UserMapper userMapper;
    public void InsertIntiandi(){
        userMapper.InsertIntiandi();
    }
    public void InsertOuttiandi(){
        userMapper.InsertOuttiandi();
    }
    public String InFanTemperature(){
        return Integer.toString(userMapper.InFanTemperature());
    }
    public String InFanSwitch(){
        return Integer.toString(userMapper.InFanSwitch());
    }
    public String InFanState(){
        return Integer.toString(userMapper.InFanState());
    }
    public String InWindowTemperature(){
        return Integer.toString(userMapper.InWindowTemperature());
    }
    public String InWindowSwitch(){
        return Integer.toString(userMapper.InWindowSwitch());
    }
    public String InWindowState(){
        return Integer.toString(userMapper.InWindowState());
    }
    public String InLEDCondition(){
        return Integer.toString(userMapper.InLEDCondition());
    }
    public String InLEDSwitch(){
        return Integer.toString(userMapper.InLEDSwitch());
    }
    public String InLEDState(){
        return Integer.toString(userMapper.InLEDState());
    }
    public String InBumpStartTime(){
        return Integer.toString(userMapper.InBumpStartHour()*60+userMapper.InBumpStartMinute());
    }
    public String InBumpInterval(){
        return Integer.toString(userMapper.InBumpInterval());
    }
    public String InBumpTime(){
        return Integer.toString(userMapper.InBumpTime());
    }
    public String InBumpSwitch(){
        return Integer.toString(userMapper.InBumpSwitch());
    }
    public String InBumpState(){
        return Integer.toString(userMapper.InBumpState());
    }
    public String OutBumpStartTime(){
        return Integer.toString(userMapper.OutBumpStartHour()*60+userMapper.OutBumpStartMinute());
    }
    public String OutBumpInterval(){
        return Integer.toString(userMapper.OutBumpInterval());
    }
    public String OutBumpTime(){
        return Integer.toString(userMapper.OutBumpTime());
    }
    public String OutBumpSwitch(){
        return Integer.toString(userMapper.OutBumpSwitch());
    }
    public String OutBumpState(){
        return Integer.toString(userMapper.OutBumpState());
    }
    public void Inside_AirHumidity(int kongqishidu, int tiandisId){
        userMapper.Inside_AirHumidity(kongqishidu, tiandisId);
    }
    public void Inside_Flume(int shuicaoshuiwei, int tiandisId){
        userMapper.Inside_Flume(shuicaoshuiwei, tiandisId);
    }
    public void Inside_LightIntensity(int gzqiangdu, int tiandisId){
        userMapper.Inside_LightIntensity(gzqiangdu, tiandisId);
    }
    public void Inside_Temperature(int wendu, int tiandisId){
        userMapper.Inside_Temperature(wendu, tiandisId);
    }
    public void Inside_WaterTank(int shuiwei, int tiandisId){
        userMapper.Inside_WaterTank(shuiwei, tiandisId);
    }
    public void Outside_AirHumidity(int kongqishidu, int tiandisId){
        userMapper.Outside_AirHumidity(kongqishidu, tiandisId);
    }
    public void Outside_AtomPre(int qiya, int tiandisId){
        userMapper.Outside_AtomPre(qiya, tiandisId);
    }
    public void Outside_BatteryLevel(int dianchidianliang, int tiandisId){
        userMapper.Outside_BatteryLevel(dianchidianliang, tiandisId);
    }
    public void Outside_Rain(int jiangyuliang, int tiandisId){
        userMapper.Outside_Rain(jiangyuliang, tiandisId);
    }
    public void Outside_Humidity(int turangshidu, int tiandisId){
        userMapper.Outside_Humidity(turangshidu, tiandisId);
    }
    public void Outside_Voltage(double dianchidianya, int tiandisId){
        userMapper.Outside_Voltage(dianchidianya, tiandisId);
    }
    public void Outside_Temperature(int wendu, int tiandisId){
        userMapper.Outside_Temperature(wendu, tiandisId);
    }
    public boolean searchId(int userId,int tiandisId){
        if(userMapper.searchId(userId,tiandisId).isEmpty()){
            userMapper.addId(userId,tiandisId);
        }
        return userMapper.searchId(userId,tiandisId).isEmpty();
    }
    public void register(String userName, String userPassword){
        userMapper.register(userName, userPassword);
    }
    public FarmData[] getFarmDatas(int userId){
        return userMapper.getFarmDatas(userId);
    }
    public void openLED(int Switch){
        userMapper.openLED(Switch);
    }
    public void updateLED(int Condition){
        userMapper.updateLED(Condition);
    }
    public void openWin(int Switch){
        userMapper.openWin(Switch);
    }
    public void openFan(int Switch){
        userMapper.openFan(Switch);
    }
    public void updateFan(int Temperature){
        userMapper.updateFan(Temperature);
    }
    public void updateWindow(int Temperature){
        userMapper.updateWindow(Temperature);
    }
    public void updateBump(int Interval, int StartHour, int StartMinute, int o_i){
        userMapper.updateBump(Interval, StartHour, StartMinute, o_i);
    }
    public void OpenPump(int OpenPump, int o_i){
        userMapper.OpenPump(OpenPump, o_i);
    }
    public FarmData getFarmData(int tiandiId){
        return userMapper.getFarmData(tiandiId);
    }
    public int[] getTiandisId(int userId){
        return userMapper.getTiandisId(userId);
    }
    public boolean login(String userName, String userPassword) {
        return !userMapper.login(userName, userPassword).isEmpty();
    }

    public int getUserId(String userName) {
        return userMapper.getUserId(userName);
    }
}
