package com.qdong.back.Threads;

public class UserThread extends Thread{
    private String UserName;
    private boolean flag = false;
    public UserThread(String name) {
        UserName=name;
        System.out.println("Creating "+UserName );
    }
    public void exit(){
        flag = true;
    }
    @Override
    public void run() {
        System.out.println("Running "+UserName );
        SafeThread safeThread = new SafeThread(UserName);
        try{
            safeThread.start();
            while(!flag){
                /*
                 * 用户线程的方法
                 *
                 *
                 *
                 *
                 *
                 *
                 * */
                Thread.sleep(500);
            }
        }catch (Exception e) {
            System.out.println("Thread " +  UserName + " interrupted.");
        }finally {
            System.out.println("Thread " +  UserName + " exiting.");
            safeThread.exit();
        }
        System.out.println("Thread " +UserName+ " exiting.");
    }

}
