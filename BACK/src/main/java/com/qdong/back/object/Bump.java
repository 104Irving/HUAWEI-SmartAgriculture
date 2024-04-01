package com.qdong.back.object;

public class Bump {
    int State;
    int Switch;
    int Time;
    long Interval;
    long StartTime;
    int o_i;

    public Bump(int State, int Switch, int Time, long Interval, long StartTime, int o_i) {
        this.State = State;
        this.Switch = Switch;
        this.Time = Time;
        this.Interval = Interval;
        this.StartTime = StartTime;
        this.o_i = o_i;
    }

    @Override
    public String toString() {
        return "Bump{" +
                "State=" + State +
                ", Switch=" + Switch +
                ", Time=" + Time +
                ", Interval=" + Interval +
                ", StartTime=" + StartTime +
                ", o_i=" + o_i +
                '}';
    }
}
