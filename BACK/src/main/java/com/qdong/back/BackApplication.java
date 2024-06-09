package com.qdong.back;


import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.io.IOException;

@SpringBootApplication
@MapperScan("com.qdong.back.mapper")
public class BackApplication {
	public static void main(String[] args) throws IOException {
        SpringApplication.run(BackApplication.class, args);
	}
}
