package com.tqx.enums;

//失衡类型
public enum ImblanceType {
    IMBALANCE_LL("LL"),
    IMBALANCE_RR("RR"),
    IMBALANCE_LR("LR"),
    IMBALANCE_RL("RL");


    ImblanceType(String type) {
        this.type = type;
    }

    private String type;

//    //平衡树失衡类型
//    private static final String IMBALANCE_LL = "LL";
//    private static final String IMBALANCE_RR = "RR";
//    private static final String IMBALANCE_LR = "LR";
//    private static final String IMBALANCE_RL = "RL";

}
