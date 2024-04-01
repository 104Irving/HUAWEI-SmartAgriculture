package com.qdong.back.mapper;

import com.qdong.back.object.*;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;
import org.springframework.stereotype.Repository;

import java.util.List;

@Mapper
@Repository
public interface UserMapper {
    @Select("select userName,userPassword from user where userName = #{userName} and userPassword = #{userPassword}")
    List<User> login(String userName, String userPassword);
    @Select("select State, Switch, Temperature from fan where id = 1")
    List<Fan> getFan();
    @Select("select State, Switch, Temperature from window where id = 1")
    List<Window> getWindow();
    @Select("select State, Switch, Condition from led where id = 1")
    List<LED> getLED();
    @Select("select State,Switch,Time,Interval,StartTime from bump where o_i = #{o_i}")
    List<Bump> getBump(int o_i);
    @Insert("insert into bump(State, Switch, Time, Interval, StartTime) values(#{State}, #{Switch}, #{Time}, #{Interval}, #{StartTime})")
    void insertBump(int State, int Switch, int Time, int Interval, int StartTime);
    @Update("update fan set State = #{State}, Switch = #{Switch}, Temperature = #{Temperature} where id = 1")
    void updateFan(int State, int Switch, int Temperature);
    @Update("update window set State = #{State}, Switch = #{Switch}, Temperature = #{Temperature} where id = 1")
    void updateWindow(int State, int Switch, int Temperature);
    @Update("update ledel set State = #{State}, Switch = #{Switch}, Condition = #{Condition} where id = 1")
    void updateLED(int State, int Switch, int Condition);
    @Update("update bump set State = #{State}, Switch = #{Switch}, Time = #{Time}, Interval = #{Interval}, StartTime = #{StartTime} where o_i = #{o_i}")
    void updateBump(int State, int Switch, int Time, int Interval, int StartTime, int o_i);
}
