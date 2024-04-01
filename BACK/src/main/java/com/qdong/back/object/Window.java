package com.qdong.back.object;

public class Window {
    int State;
    int Switch;
    int Temperature;

    public Window(int state, int aSwitch, int temperature) {
        State = state;
        Switch = aSwitch;
        Temperature = temperature;
    }

    @Override
    public String toString() {
        return "Window{" +
                "State=" + State +
                ", Switch=" + Switch +
                ", Temperature=" + Temperature +
                '}';
    }
}
