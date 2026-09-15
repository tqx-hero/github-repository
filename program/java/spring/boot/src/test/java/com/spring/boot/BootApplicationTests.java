package com.spring.boot;

import com.spring.boot.service.IService;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class BootApplicationTests {

	@Autowired
	IService service;

	@Test
	void contextLoads() {
		service.say();
	}

}
