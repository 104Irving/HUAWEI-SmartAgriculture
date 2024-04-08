package com.qdong.back.object;

import lombok.Data;

@Data
public class Id {
    int userId;
    int tiandisId;
    public Id(int a,int b){
        userId=a;
        tiandisId=b;
    }
}
