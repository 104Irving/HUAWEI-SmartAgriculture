package com.qdong.back;

import org.bytedeco.javacv.*;
import org.bytedeco.opencv.opencv_core.Mat;
import org.bytedeco.opencv.opencv_videoio.VideoCapture;
import org.opencv.videoio.Videoio;

import javax.swing.*;
import java.awt.image.BufferedImage;
import java.io.IOException;

import static org.bytedeco.opencv.global.opencv_core.flip;


public class HttpVideoReceiver {

    public static void main(String[] args) throws Exception {
        // 创建一个视频捕捉对象
        VideoCapture capture = new VideoCapture();
        // 打开视频流
        capture.open("http://192.168.16.4:81");

        // 创建一个窗口来显示视频
        CanvasFrame canvasFrame = new CanvasFrame("Video", CanvasFrame.getDefaultGamma() / capture.get(Videoio.CAP_PROP_GAMMA));
        canvasFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        Mat frame = new Mat();
        while (canvasFrame.isVisible() && capture.read(frame)) {
            // 从捕捉对象中读取帧
            capture.read(frame);

            // 翻转帧以适应Java窗口
            flip(frame, frame, 1);
            int width = frame.cols();
            int height = frame.rows();
            byte[] data = new byte[width * height * (int)frame.elemSize()];
            frame.data().get(data);
            BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_3BYTE_BGR);
            image.getRaster().setDataElements(0, 0, width, height, data);
            canvasFrame.showImage(image);
        }

        // 释放资源
        capture.release();
        canvasFrame.dispose();
    }
}