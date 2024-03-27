package com.qdong.back.mapper;

import com.qdong.back.object.User;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface UserMapper {
    @Select("select userName,userPassword from user where userName = #{userName} and userPassword = #{userPassword}")
    List<User> login(String userName, String userPassword);


}
