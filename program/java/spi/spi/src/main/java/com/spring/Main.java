package com.spring;



import com.spring.service.ISPIService;

import java.util.ServiceLoader;

public class Main {

    public static void main(String[] args) {
        ServiceLoader<ISPIService> services = ServiceLoader.load(ISPIService.class);
        for (ISPIService service : services) {
            service.say();
        }

    }
}