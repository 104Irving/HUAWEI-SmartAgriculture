package com.qdong.back.object;

import lombok.Data;

import java.util.List;

@Data
public class UserData {
    int UserId;
    List<Integer> list;
    public UserData(int userId, List<Integer> list) {
        UserId = userId;
        this.list = list;
    }
}
