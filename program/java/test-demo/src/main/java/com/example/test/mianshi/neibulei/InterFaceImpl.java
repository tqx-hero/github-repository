package com.example.test.mianshi.neibulei;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/3 20:52
 */
public class InterFaceImpl {

    public InterFace getSay() {
        class InterImpl implements InterFace {
            @Override
            public String say() {

                return "好好好";
            }
        }
        return new InterImpl();
    }


    public static void main(String[] args) {
        new InterFace() {
            @Override
            public String say() {
                return "大家好";
            }
        }.say();
    }
}
