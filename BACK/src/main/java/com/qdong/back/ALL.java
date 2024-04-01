package com.qdong.back;


import com.qdong.back.Threads.UserThread;
import com.qdong.back.service.UserMapperService;
import jakarta.servlet.http.HttpServletRequest;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
@RestController
@CrossOrigin
public class ALL {
    static UserThread userThread;
    @Autowired
    private UserMapperService userMapperService;
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

    @RequestMapping("/exit")
    public boolean exit(){
        userThread.exit();
        return true;
    }
}
