package com.qdong.back;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;

public class CameraClient {
    private static final String IP_ADDRESS = "47.109.192.44";
    private static final int PORT = 8080;

    public static void main(String[] args) {
        try {
            Socket socket = new Socket(IP_ADDRESS, PORT);
            InputStream inputStream = socket.getInputStream();

            // 处理视频流数据
            handleVideoStream(inputStream);

            inputStream.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleVideoStream(InputStream inputStream) {
        // 处理视频流数据的逻辑
    }
}