package com.qdong.back.object;
import lombok.Data;
@Data
public class FarmData {
    String FarmName;
    int wendu;
    int kongqishidu;
    int CO2nongdu;
    int gzqiangdu;
    int turangshidu;
    FarmData(String FarmName, int wendu, int kongqishidu, int CO2nongdu, int gzqiangdu, int turangshidu){
        this.FarmName = FarmName;
        this.wendu = wendu;
        this.kongqishidu = kongqishidu;
        this.CO2nongdu = CO2nongdu;
        this.gzqiangdu = gzqiangdu;
        this.turangshidu = turangshidu;
    }
}
