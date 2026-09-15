package com.tqx.think;

import com.tqx.think.enums.Weather;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/10 18:01
 */
public class 编程思想 {

    public static void tes(Weather name) {
        String s = "";
        switch (name) {
            case SPRING -> s = "春天";
        }
        System.out.println(s);
    }

    public static void main(String[] args) {
        tes(Weather.SPRING
        );
//        System.out.println(Cal.PLUS.calculate(10, 20));

//        System.out.println(Inter.SUCCESS.getCode());

    }

}
