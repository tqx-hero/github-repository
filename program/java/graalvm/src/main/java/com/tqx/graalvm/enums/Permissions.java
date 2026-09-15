package com.tqx.graalvm.enums;

public enum Permissions {
    ADD("add"),
    UPDATE("update"),
    DELETE("delete"),
    SELECT("select");


    private final String name;

    Permissions(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
