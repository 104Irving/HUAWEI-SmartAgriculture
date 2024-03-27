package com.qdong.back.service;

import com.qdong.back.mapper.UserMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class UserMapperService {
    @Autowired
    private UserMapper userMapper;
    public boolean login(String userName, String userPassword) {
        return !userMapper.login(userName, userPassword).isEmpty();
    }
}
