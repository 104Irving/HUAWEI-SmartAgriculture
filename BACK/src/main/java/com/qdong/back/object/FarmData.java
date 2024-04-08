package com.qdong.back.object;
import lombok.AllArgsConstructor;
import lombok.Data;
@Data
public class FarmData {
    String tiandiName;
    int wendu;
    int kongqishidu;
    int CO2nongdu;
    int gzqiangdu;
    int turangshidu;
    double dianchidianya;
    int qiya;
    int shuiwei;
    int shuicaoshuiwei;
    int dianchidianliang;
    int jiangyuliang;
    public FarmData(String tiandiName,int wendu,int kongqishidu,int CO2nongdu,int gzqiangdu,int turangshidu,int dianchidianya,int qiya,int shuiwei,int shuicaoshuiwei,int dianchidianliang,int jiangyuliang){
        this.tiandiName=tiandiName;
        this.wendu=wendu;
        this.kongqishidu=kongqishidu;
        this.CO2nongdu=CO2nongdu;
        this.gzqiangdu=gzqiangdu;
        this.turangshidu=turangshidu;
        this.dianchidianya=dianchidianya;
        this.qiya=qiya;
        this.shuiwei=shuiwei;
        this.shuicaoshuiwei=shuicaoshuiwei;
        this.dianchidianliang=dianchidianliang;
        this.jiangyuliang=jiangyuliang;
    }
}
