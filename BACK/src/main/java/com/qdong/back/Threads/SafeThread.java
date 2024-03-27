package com.qdong.back.Threads;

public class SafeThread extends Thread{
    private String UserName;
    private boolean flag = false;

    public void exit(){
        flag = true;
    }
    public SafeThread(String name) {
        UserName = name;
        System.out.println("Creating " + UserName);
    }

    @Override
    public void run() {
        System.out.println("Running " + UserName);
        try {
            while (!flag) {
                System.out.println(UserName + " is running");
                /*
                 * 安全线程的代码
                 *
                 *
                 *
                 *
                 *
                 *
                 *
                 * */
                Thread.sleep(50);
            }
        } catch (Exception e) {
            System.out.println("Thread " + UserName + " interrupted.");
        } finally {
            System.out.println("Thread " + UserName + " exiting.");
        }
        System.out.println("Thread " + UserName + " exiting.");
    }
}
