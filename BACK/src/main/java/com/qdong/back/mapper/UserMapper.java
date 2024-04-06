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
    @Update("update led set Switch = #{Switch} where id = 1")
    void openLED(int Switch);
    @Update("update led set Condition = #{Condition} where id = 1")
    void updateLED(int Condition);
    @Update("update win set Switch = #{Switch} where id = 1")
    void openWin(int Switch);
    @Update("update fan set Switch = #{Switch} where id = 1")
    void openFan(int Switch);
    @Update("update fan set Temperature = #{Temperature} where id = 1")
    void updateFan(int Temperature);
    @Update("update window set Temperature = #{Temperature} where id = 1")
    void updateWindow(int Temperature);
    @Update("update bump set State =2 Interval = #{Interval} StartHour = #{StartHour} StartMinute = #{StartMinute} o_i = #{o_i} where o_i = #{o_i}")
    void updateBump(int Interval, int StartHour, int StartMinute, int o_i);
    @Update("update bump set State =1 Switch = #{OpenPump} where o_i = #{o_i}")
    void OpenPump(int OpenPump, int o_i);
    @Select("select tiandiName,wendu,kongqishidu,CO2nongdu,gzqiangdu,turangshidu from tiandis where userId = #{userId} order by time DESC")
    List<FarmData> getFarmDatas(int userId);
    @Select("select tiandiName,wendu,kongqishidu,CO2nongdu,gzqiangdu,turangshidu from tiandis where tiandisId = #{tiandisId} and userId = #{userId}")
    FarmData getFarmData(int tiandisId, int userId);
    @Select("select userId from user where userName = #{userName}")
    int getUserId(String userName);
    @Select("select tiandisId from tiandis where userId = #{userId}")
    List<Integer> getTiandisId(int userId);
    @Select("select userName,userPassword from user where userName = #{userName} and userPassword = #{userPassword}")
    List<User> login(String userName, String userPassword);
}