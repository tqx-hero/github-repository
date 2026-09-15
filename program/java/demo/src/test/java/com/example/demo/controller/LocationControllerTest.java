package com.example.demo.controller;

import com.example.demo.entity.Location;
import com.example.demo.entity.Result;
import com.example.demo.service.LocationService;
import lombok.extern.slf4j.Slf4j;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.List;

@SpringBootTest
@Slf4j
class LocationControllerTest {


    @Autowired
    private LocationService locationService;

    @Test
    void list() {
//        List<Location> list = locationService.findAll(null);
//        log.info(list.toString());
    }

    @Test
    void add() {
        Result<String> result = locationService.add(new Location(1,"山东省济南市历城区",1));
        log.info(result.toString());
    }


}