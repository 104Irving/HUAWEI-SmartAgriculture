package com.qdong.back;

import java.io.*;
import java.net.*;
import java.awt.*;
import javax.swing.*;
import java.awt.image.*;
import org.opencv.core.*;
import org.opencv.imgcodecs.*;
import org.opencv.imgproc.*;

public class VideoServer {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("47.109.192.44",8080);
            System.out.println("Client connected: " + socket);
            InputStream inputStream = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
            JFrame frame = new JFrame("Server Frame");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(640, 480);
            JLabel label = new JLabel();
            frame.getContentPane().add(label);
            frame.setVisible(true);

            // Main loop to receive and display images
            String line;
            MatOfByte imageData;
            while ((line = reader.readLine()) != null) {
                // Read image data from the stream
                if (line.equals("Frame Begin")) {
                    imageData = new MatOfByte();
                    while (!(line = reader.readLine()).equals("Frame Over")) {
                        byte[] bytes = line.getBytes();
                        imageData.push_back(new MatOfByte(bytes));
                    }

                    // Convert image data to BufferedImage
                    Mat imageMat = Imgcodecs.imdecode(imageData, Imgcodecs.IMREAD_COLOR);
                    BufferedImage bufferedImage = new BufferedImage(imageMat.width(), imageMat.height(), BufferedImage.TYPE_3BYTE_BGR);
                    byte[] data = ((DataBufferByte) bufferedImage.getRaster().getDataBuffer()).getData();
                    imageMat.get(0, 0, data);

                    // Display the image
                    label.setIcon(new ImageIcon(bufferedImage));
                    frame.pack();
                }
            }

            // Close resources
            inputStream.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
