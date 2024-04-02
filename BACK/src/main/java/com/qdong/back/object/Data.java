package com.qdong.back.object;

import com.qdong.back.service.UserMapperService;

public class Data {
    int SoilMoistrue;
    double Voltage;
    int BatteryLevel;
    int TemperatureOut;
    int AirHumidityOut;
    int Rain;
    int AtomPre;

    int LightIntensity;
    int TemperatureIn;
    int AirHumidityIn;
    int WaterTank;
    int Flume;

    public Data(int soilMoistrue, double voltage, int batteryLevel, int temperatureOut, int airHumidityOut, int rain, int atomPre,int lightIntensity, int temperatureIn, int airHumidityIn, int waterTank, int flume) {
        SoilMoistrue = soilMoistrue;
        Voltage = voltage;
        BatteryLevel = batteryLevel;
        TemperatureOut = temperatureOut;
        AirHumidityOut = airHumidityOut;
        Rain = rain;
        AtomPre = atomPre;
        LightIntensity = lightIntensity;
        TemperatureIn = temperatureIn;
        AirHumidityIn = airHumidityIn;
        WaterTank = waterTank;
        Flume = flume;
    }

    @Override
    public String toString() {
        return "Data{Outside: " +
                "SoilMoistrue=" + SoilMoistrue +
                ", Voltage=" + Voltage +
                ", BatteryLevel=" + BatteryLevel +
                ", TemperatureOut=" + TemperatureOut +
                ", AirHumidityOut=" + AirHumidityOut +
                ", Rain=" + Rain +
                ", AtomPre=" + AtomPre +
                ",Inside: LightIntensity=" + LightIntensity +
                ", TemperatureIn=" + TemperatureIn +
                ", AirHumidityIn=" + AirHumidityIn +
                ", WaterTank=" + WaterTank +
                ", Flume=" + Flume +
                '}';
    }
}
