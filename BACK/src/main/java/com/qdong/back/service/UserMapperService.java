package com.qdong.back.service;

import com.qdong.back.mapper.UserMapper;
import com.qdong.back.object.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class UserMapperService{
    @Autowired
    private UserMapper userMapper;
    public boolean login(String userName, String userPassword) {
        return !userMapper.login(userName, userPassword).isEmpty();
    }
    public List<Fan> getFan(){
        return userMapper.getFan();
    }
    public List<Window> getWindow(){
        return userMapper.getWindow();
    }
    public List<LED> getLED(){
        return userMapper.getLED();
    }
    public List<Bump> getBump(int o_i){
        return userMapper.getBump(o_i);
    }
    public void insertBump(int State, int Switch, int Time, int Interval, int StartTime){
        userMapper.insertBump(State, Switch, Time, Interval, StartTime);
    }
    public void updateFan(int State, int Switch, int Temperature){
        userMapper.updateFan(State, Switch, Temperature);
    }
    public void updateWindow(int State, int Switch, int Temperature){
        userMapper.updateWindow(State, Switch, Temperature);
    }
    public void updateLED(int State, int Switch, int Condition){
        userMapper.updateLED(State, Switch, Condition);
    }
    public void updateBump(int State, int Switch, int Time, int Interval, int StartTime, int o_i){
        userMapper.updateBump(State, Switch, Time, Interval, StartTime, o_i);
    }
}
