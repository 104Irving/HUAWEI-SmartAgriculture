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
    @Insert("insert into tiandis(tiandisId, tiandiName,time) values(1,11,NOW())")
    void InsertIntiandi();
    @Insert("insert into tiandis(tiandisId, tiandiName,time) values(2,22,NOW())")
    void InsertOuttiandi();
    @Select("select Switch from fan where id=1")
    public int InFanSwitch();
    @Select("select Temperature from fan where id=1")
    public int InFanTemperature();
    @Select("select stt from fan where id=1")
    public int InFanState();
    @Select("select Temperature from win")
    public int InWindowTemperature();
    @Select("select Switch from win")
    public int InWindowSwitch();
    @Select("select zhuangtai from win")
    public int InWindowState();
    @Select("select condt from led where id=1")
    public int InLEDCondition();
    @Select("select Switch from led where id=1")
    public int InLEDSwitch();
    @Select("select stt from led where id=1")
    public int InLEDState();
    @Select("select StartMinute from bumps where o_i = 0")
    public int InBumpStartMinute();
    @Select("select StartHour from bumps where o_i = 0")
    public int InBumpStartHour();
    @Select("select val from bumps where o_i = 0")
    public int InBumpInterval();
    @Select("select timetime from bumps where o_i = 0")
    public int InBumpTime();
    @Select("select Switch from bumps where o_i = 0")
    public int InBumpSwitch();
    @Select("select stt from bumps where o_i = 0")
    public int InBumpState();
    @Select("select StartMinute from bumps where o_i = 1")
    public int OutBumpStartMinute();
    @Select("select StartHour from bumps where o_i = 1")
    public int OutBumpStartHour();
    @Select("select val from bumps where o_i = 1")
    public int OutBumpInterval();
    @Select("select timetime from bumps where o_i = 1")
    public int OutBumpTime();
    @Select("select Switch from bumps where o_i = 1")
    public int OutBumpSwitch();
    @Select("select stt from bumps where o_i = 1")
    public int OutBumpState();
    @Update("update tiandis set kongqishidu=#{kongqishidu} where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    void Inside_AirHumidity(int kongqishidu, int tiandisId);
    @Update("update tiandis set shuicaoshuiwei=#{shuicaoshuiwei} where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    void Inside_Flume(int shuicaoshuiwei, int tiandisId);
    @Update("update tiandis set gzqiangdu=#{gzqiangdu} where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    void Inside_LightIntensity(int gzqiangdu, int tiandisId);
    @Update("update tiandis set wendu=#{wendu} where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    void Inside_Temperature(int wendu, int tiandisId);
    @Update("update tiandis set shuiwei=#{shuiwei} where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    void Inside_WaterTank(int shuiwei, int tiandisId);
    @Update("update tiandis set kongqishidu=#{kongqishidu} where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    void Outside_AirHumidity(int kongqishidu, int tiandisId);
    @Update("update tiandis set qiya=#{qiya} where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    void Outside_AtomPre(int qiya, int tiandisId);
    @Update("update tiandis set dianchidianliang=#{dianchidianliang} where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    void Outside_BatteryLevel(int dianchidianliang, int tiandisId);
    @Update("update tiandis set jiangyuliang=#{jiangyuliang} where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    void Outside_Rain(int jiangyuliang, int tiandisId);
    @Update("update tiandis set turangshidu=#{turangshidu} where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    void Outside_Humidity(int turangshidu, int tiandisId);
    @Update("update tiandis set dianchidianya=#{dianchidianya} where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    void Outside_Voltage(double dianchidianya, int tiandisId);
    @Update("update tiandis set wendu=#{wendu} where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    void Outside_Temperature(int wendu, int tiandisId);
    @Insert("insert into tiandis(userId, tiandisId,tiandiName) values(#{userId}, #{taindisId},#{taindisId})")
    void addId(int userId,int tiandisId);
    @Select("select userId,tiandisId from tiandis where userId = #{userId} and tiandisId= #{tiandisId}")
    List<Id> searchId(int userId,int tiandisId);
    @Insert("insert into user(userName, userPassword) values(#{userName}, #{userPassword})")
    void register(String userName, String userPassword);
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
    @Update("update win set Temperature = #{Temperature} where id = 1")
    void updateWindow(int Temperature);
    @Update("update bump set stt =2,Interval = #{Interval},StartHour = #{StartHour},StartMinute = #{StartMinute}where o_i = #{o_i}")
    void updateBump(int Interval, int StartHour, int StartMinute, int o_i);
    @Update("update bumps set stt =1,Switch = #{OpenPump} where o_i = #{o_i}")
    void OpenPump(int OpenPump, int o_i);
    @Select("select tiandiName,wendu,kongqishidu,CO2nongdu,gzqiangdu,turangshidu,dianchidianya,qiya,shuiwei,shuicaoshuiwei,dianchidianliang,jiangyuliang from tiandis where userId = #{userId} order by time DESC")
    FarmData[] getFarmDatas(int userId);
    @Select("select tiandiName,wendu,kongqishidu,CO2nongdu,gzqiangdu,turangshidu,dianchidianya,qiya,shuiwei,shuicaoshuiwei,dianchidianliang,jiangyuliang from tiandis where tiandisId = #{tiandisId} order by time DESC LIMIT 1")
    FarmData getFarmData(int tiandisId);
    @Select("select userId from user where userName = #{userName}")
    int getUserId(String userName);
    @Select("select tiandisId from tiandis where userId = #{userId}")
    int[] getTiandisId(int userId);
    @Select("select userName,userPassword from user where userName = #{userName} and userPassword = #{userPassword}")
    List<User> login(String userName, String userPassword);
}