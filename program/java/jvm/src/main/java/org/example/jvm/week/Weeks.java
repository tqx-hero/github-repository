package org.example.jvm.week;


/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/4 14:02
 */
public class Weeks {

    static ThreadLocal<String> local = new ThreadLocal<>();

    public static void main(String[] args) {
        new Thread(() -> {
            local.set("zhangsan");
            System.out.println(local.get());
        }).start();
        new Thread(() -> {
            local.set("lisi");
            System.out.println(local.get());
        }).start();
    }


}
