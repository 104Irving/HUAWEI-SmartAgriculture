package com.qdong.back.object;

public class LED {
    int State;
    int Switch;
    int Condition;

    public LED(int state, int aSwitch, int condition) {
        State = state;
        Switch = aSwitch;
        Condition = condition;
    }

    @Override
    public String toString() {
        return "LED{" +
                "State=" + State +
                ", Switch=" + Switch +
                ", Condition=" + Condition +
                '}';
    }
}
