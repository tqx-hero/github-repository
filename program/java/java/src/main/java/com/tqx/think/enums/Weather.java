package com.tqx.think.enums;

public enum Weather {
    SPRING("春天");


    Weather(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    private final String name;

}
