package com.qdong.back.object;

public class Fan {
    int State;
    int Switch;
    int Temperature;

    public Fan(int state, int aSwitch, int temperature) {
        State = state;
        Switch = aSwitch;
        Temperature = temperature;
    }

    @Override
    public String toString() {
        return "Fan{" +
                "State=" + State +
                ", Switch=" + Switch +
                ", Temperature=" + Temperature +
                '}';
    }
}
