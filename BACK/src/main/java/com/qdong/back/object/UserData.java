package com.qdong.back.object;

import lombok.Data;

import java.util.List;

@Data
public class UserData {
    int UserId;
    int[] List;
    public UserData(int userId, int[] list) {
        UserId = userId;
        this.List = list;
    }
}
