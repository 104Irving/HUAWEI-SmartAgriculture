package com.qdong.back;


import org.bytedeco.javacv.*;
import org.bytedeco.javacv.Frame;
import org.bytedeco.opencv.opencv_core.Mat;
import org.mybatis.spring.annotation.MapperScan;
import org.opencv.highgui.HighGui;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

import static com.sun.org.apache.xerces.internal.util.DOMUtil.setVisible;

@SpringBootApplication
@MapperScan("com.qdong.back.mapper")
public class BackApplication {
	private static CanvasFrame canvasFrame;
	private static FrameGrabber frameGrabber;
	private static Socket socket;
	public static void main(String[] args) throws IOException {
        SpringApplication.run(BackApplication.class, args);
		ServerSocket serverSocket = new ServerSocket(8081);
		socket = serverSocket.accept();
		InputStream inputStream = socket.getInputStream();
		if(inputStream != null){
			System.out.println("Client connected: " + socket);
			canvasFrame = new CanvasFrame("Server Frame");
			canvasFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			canvasFrame.setSize(640, 480);
			canvasFrame.setVisible(true);
			frameGrabber = FrameGrabber.createDefault(0);
			frameGrabber.start();
			Frame frame;
			while ((frame = frameGrabber.grab()) != null) {
				canvasFrame.showImage(frame);
			}
		}
	}
}
