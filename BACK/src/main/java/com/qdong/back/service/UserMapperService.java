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
    public List<FarmData> getFarmDatas(int userId){
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
    public List<FarmData> getFarmData(int userId){
        return userMapper.getFarmDatas(userId);
    }
    public FarmData getFarmData(int tiandisId, int userId){
        return userMapper.getFarmData(tiandisId, userId);
    }
    public int getUserId(String userName){
        return userMapper.getUserId(userName);
    }
    public List<Integer> getTiandisId(int userId){
        return userMapper.getTiandisId(userId);
    }
    public boolean login(String userName, String userPassword) {
        return !userMapper.login(userName, userPassword).isEmpty();
    }
}
