package com.qdong.back;


import com.qdong.back.Threads.UserThread;
import com.qdong.back.object.FarmData;
import com.qdong.back.object.UserData;
import com.qdong.back.service.UserMapperService;
import jakarta.servlet.http.HttpServletRequest;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@CrossOrigin
public class ALL {
    static UserThread userThread;
    @Autowired
    UserMapperService userMapperService;

    @RequestMapping("/Control/Out/Bump/State")
    public String OutBumpState(){
        return userMapperService.OutBumpState();
    }
    @RequestMapping("/Control/Out/Bump/Switch")
    public String OutBumpSwitch(){
        return userMapperService.OutBumpSwitch();
    }
    @RequestMapping("/Control/Out/Bump/Time")
    public String OutBumpTime(){
        return userMapperService.OutBumpTime();
    }
    @RequestMapping("/Control/Out/Bump/Interval")
    public String OutBumpInterval(){
        return userMapperService.OutBumpInterval();
    }
    @RequestMapping("/Control/Out/Bump/StartTime")
    public String OutBumpStartTime(){
        return userMapperService.OutBumpStartTime();
    }
    @RequestMapping("/Control/In/Bump/State")
    public String InBumpState(){
        return userMapperService.InBumpState();
    }
    @RequestMapping("/Control/In/Bump/Switch")
    public String InBumpSwitch(){
        return userMapperService.InBumpSwitch();
    }
    @RequestMapping("/Control/In/Bump/Time")
    public String InBumpTime(){
        return userMapperService.InBumpTime();
    }
    @RequestMapping("/Control/In/Bump/Interval")
    public String InBumpInterval(){
        return userMapperService.InBumpInterval();
    }
    @RequestMapping("/Control/In/Bump/StartTime")
    public String InBumpStartTime(){
        return userMapperService.InBumpStartTime();
    }
    @RequestMapping("/Control/In/LED/State")
    public String InLEDState(){
        return userMapperService.InLEDState();
    }
    @RequestMapping("/Control/In/LED/Switch")
    public String InLEDSwitch(){
        return userMapperService.InLEDSwitch();
    }
    @RequestMapping("/Control/In/LED/Condition")
    public String InLEDCondition(){
        return userMapperService.InLEDCondition();
    }
    @RequestMapping("/Control/In/Window/State")
    public String InWindowState(){
        return userMapperService.InWindowState();
    }
    @RequestMapping("/Control/In/Window/Switch")
    public String InWindowSwitch(){
        return userMapperService.InWindowSwitch();
    }
    @RequestMapping("/Control/In/Window/Temperature")
    public String InWindowTemperature(){
        return userMapperService.InWindowTemperature();
    }
    @RequestMapping("/Control/In/Fan/State")
    public String InFanState(){
        return userMapperService.InFanState();
    }
    @RequestMapping("/Control/In/Fan/Switch")
    public String InFanSwitch(){
        return userMapperService.InFanSwitch();
    }
    @RequestMapping("/Control/In/Fan/Temperature")
    public String InFanTemperature(){
        return userMapperService.InFanTemperature();
    }
    @RequestMapping("/Inside/AirHumidity")
    public void Data_Inside_AirHumidity(@RequestBody String string){
        String[] strings = string.split("\"");
        int kongqishidu = Integer.parseInt(strings[7]);
        int tiandisId = Integer.parseInt(strings[3]);
        userMapperService.Inside_AirHumidity(kongqishidu, tiandisId);
    }
    @RequestMapping("/Inside/Flume")
    public void Data_Inside_Flume(@RequestBody String string){
        String[] strings = string.split("\"");
        int shuicaoshuiwei = Integer.parseInt(strings[7]);
        int tiandisId = Integer.parseInt(strings[3]);
        userMapperService.Inside_Flume(shuicaoshuiwei, tiandisId);
    }
    @RequestMapping("/Inside/LightIntensity")
    public void Data_Inside_LightIntensity(@RequestBody String string){
        String[] strings = string.split("\"");
        int gzqiangdu = Integer.parseInt(strings[7]);
        int tiandisId = Integer.parseInt(strings[3]);
        userMapperService.Inside_LightIntensity(gzqiangdu, tiandisId);
    }
    @RequestMapping("/Inside/Temperature")
    public void Data_Inside_Temperature(@RequestBody String string){
        String[] strings = string.split("\"");
        int wendu = Integer.parseInt(strings[7]);
        int tiandisId = Integer.parseInt(strings[3]);
        userMapperService.Inside_Temperature(wendu, tiandisId);
    }
    @RequestMapping("/Inside/WaterTank")
    public void Data_Inside_WaterTank(@RequestBody String string){
        String[] strings = string.split("\"");
        int shuiwei = Integer.parseInt(strings[7]);
        int tiandisId = Integer.parseInt(strings[3]);
        userMapperService.Inside_WaterTank(shuiwei, tiandisId);
    }
    @RequestMapping("/Outside/AirHumidity")
    public void Data_Outside_AirHumidity(@RequestBody String string){
        String[] strings = string.split("\"");
        int kongqishidu = Integer.parseInt(strings[7]);
        int tiandisId = Integer.parseInt(strings[3]);
        userMapperService.Outside_AirHumidity(kongqishidu, tiandisId);
    }
    @RequestMapping("/Outside/AtomPre")
    public void Data_Outside_AtomPre(@RequestBody String string){
        String[] strings = string.split("\"");
        int qiya = Integer.parseInt(strings[7]);
        int tiandisId = Integer.parseInt(strings[3]);
        userMapperService.Outside_AtomPre(qiya, tiandisId);
    }
    @RequestMapping("/Outside/BatteryLevel")
    public void Data_Outside_BatteryLevel(@RequestBody String string){
        String[] strings = string.split("\"");
        int dianchidianliang = Integer.parseInt(strings[7]);
        int tiandisId = Integer.parseInt(strings[3]);
        userMapperService.Outside_BatteryLevel(dianchidianliang, tiandisId);
    }
    @RequestMapping("/Outside/Rain")
    public void Data_Outside_Rain(@RequestBody String string){
        String[] strings = string.split("\"");
        int jiangyuliang = Integer.parseInt(strings[7]);
        int tiandisId = Integer.parseInt(strings[3]);
        userMapperService.Outside_Rain(jiangyuliang, tiandisId);
    }
    @RequestMapping("/Outside/SoilMoisture")
    public void Data_Outside_Humidity(@RequestBody String string){
        String[] strings = string.split("\"");
        int turangshidu = Integer.parseInt(strings[7]);
        int tiandisId = Integer.parseInt(strings[3]);
        userMapperService.Outside_Humidity(turangshidu, tiandisId);
    }
    @RequestMapping("/Outside/Voltage")
    public void Data_Outside_Voltage(@RequestBody String string){
        String[] strings = string.split("\"");
        double dianchidianya = Double.parseDouble(strings[7]);
        int tiandisId = Integer.parseInt(strings[3]);
        userMapperService.Outside_Voltage(dianchidianya, tiandisId);
    }
    @RequestMapping("/Outside/Temperature")
    public void Data_Outside_Temperature(@RequestBody String string){
        String[] strings = string.split("\"");
        int wendu = Integer.parseInt(strings[7]);
        int tiandisId = Integer.parseInt(strings[3]);
        userMapperService.Outside_Temperature(wendu, tiandisId);
    }
    @RequestMapping("/AddFarm")
    public boolean addFarm(HttpServletRequest R){
        int userId=Integer.parseInt(R.getParameter("UserId"));
        int tiandisId=Integer.parseInt(R.getParameter("FarmId"));
        return userMapperService.searchId(userId,tiandisId);
    }
    @RequestMapping("/OpenLightSub")
    public void OpenLightSub(HttpServletRequest R){
        userMapperService.openLED(Integer.parseInt(R.getParameter("Switch")));
    }
    @RequestMapping("/LightSubPlan")
    public void LightSubPlan(HttpServletRequest R){
        userMapperService.updateLED(Integer.parseInt(R.getParameter("Condition")));
    }
    @RequestMapping("/OpenWin")
    public void openWin(HttpServletRequest R){
        userMapperService.openWin(Integer.parseInt(R.getParameter("Switch")));
    }
    @RequestMapping("/OpenFan")
    public void OpenFan(HttpServletRequest R){
        userMapperService.openFan(Integer.parseInt(R.getParameter("Switch")));
    }
    @RequestMapping("/VentilatePlan")
    public void VentilatePlan(HttpServletRequest R){
        userMapperService.updateFan(Integer.parseInt(R.getParameter("FanTemperature")));
        userMapperService.updateWindow(Integer.parseInt(R.getParameter("WinTemperature")));
    }

    @RequestMapping("/WaterPlan")
    public void WaterPlan(HttpServletRequest R){
        userMapperService.updateBump(Integer.parseInt(R.getParameter("Interval")), Integer.parseInt(R.getParameter("StartHour")), Integer.parseInt(R.getParameter("StartMinute")), Integer.parseInt(R.getParameter("o_i")));
    }
    @RequestMapping("/OpenPump")
    public void OpenPump(HttpServletRequest R){
        userMapperService.OpenPump(Integer.parseInt(R.getParameter("OpenPump")), Integer.parseInt(R.getParameter("o_i")));
    }
    @RequestMapping("/login")
    public boolean login(HttpServletRequest R) {
        String userName = R.getParameter("userName");
        String userPassword = R.getParameter("userPassword");

        boolean tf=userMapperService.login(userName, userPassword);
        return tf;
    }
    @RequestMapping("/GetFarmDataList")
    public FarmData[] GetFarmDataList(HttpServletRequest R){
        int UserId = userMapperService.getUserId(R.getParameter("userName"));
        return userMapperService.getFarmDatas(UserId);
    }
    @RequestMapping("/GetUserData")
    public UserData GetUserData(HttpServletRequest R){
        return new UserData(
                userMapperService.getUserId(R.getParameter("userName")),
                userMapperService.getTiandisId(userMapperService.getUserId(R.getParameter("userName")))
        );
    }
    @RequestMapping("/FarmData")
    public FarmData FarmData(HttpServletRequest R){
        int tiandiId= Integer.parseInt(R.getParameter("FarmID"));
        return userMapperService.getFarmData(tiandiId);
    }
    @RequestMapping("/exit")
    public boolean exit(){
        userThread.exit();
        return true;
    }
    @RequestMapping("/Register")
    public boolean register(HttpServletRequest R){
        String userName = R.getParameter("userName");
        String userPassword = R.getParameter("userPassword");
        boolean tf=userMapperService.login(userName, userPassword);
        if(tf){
            return false;
        }
        userMapperService.register(userName,userPassword);
        return true;
    }
}
