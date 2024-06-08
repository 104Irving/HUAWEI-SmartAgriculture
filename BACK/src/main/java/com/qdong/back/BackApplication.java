package com.qdong.back;


import org.bytedeco.javacv.*;
import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.io.IOException;
import java.net.Socket;

@SpringBootApplication
@MapperScan("com.qdong.back.mapper")
public class BackApplication {

	public static void main(String[] args){
        SpringApplication.run(BackApplication.class, args);
	}
}
