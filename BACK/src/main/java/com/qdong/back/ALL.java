package com.qdong.back;


import com.qdong.back.Threads.UserThread;
import com.qdong.back.object.FarmData;
import com.qdong.back.object.UserData;
import com.qdong.back.service.UserMapperService;
import jakarta.servlet.http.HttpServletRequest;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@CrossOrigin
public class ALL {
    static UserThread userThread;
    @Autowired
    UserMapperService userMapperService;
    @RequestMapping("/OpenLightSub")
    public void OpenLightSub(HttpServletRequest R){
        userMapperService.openLED(Integer.parseInt(R.getParameter("Switch")));
    }
    @RequestMapping("/LightSubPlan")
    public void LightSubPlan(HttpServletRequest R){
        userMapperService.updateLED(Integer.parseInt(R.getParameter("Condition")));
    }
    @RequestMapping("/openWin")
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
        if(tf){
            userThread = new UserThread(userName, userPassword, userMapperService);
            userThread.start();
        }
        return tf;
    }
    @RequestMapping("/GetFarmDataList")
    public List<FarmData> GetFarmDataList(HttpServletRequest R){
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
        return userMapperService.getFarmData(Integer.parseInt(R.getParameter("FarmId")),Integer.parseInt(R.getParameter("UserId")));
    }
    @RequestMapping("/exit")
    public boolean exit(){
        userThread.exit();
        return true;
    }
}
