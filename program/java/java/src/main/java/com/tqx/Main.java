package com.tqx;

public class Main {
    public static void main(String[] args) {
//        System.out.println(-7&255);
//        System.out.println(Integer.toBinaryString(255));
//        System.out.println(Integer.toBinaryString(-7));
//        String str ="ab";
//        System.out.println(Integer.toString(255, 16));
//        str.hashCode()
//        String s = "a"+"b"+"c";
//        System.out.println(s);

        System.out.println(differ_two_number(-10, 20));
//        System.out.println(differ_two_number(0, 0));


    }

    //求两数据有多少位不同
    public static int differ_two_number(int x, int y) {
        int z = x ^ y;
        int num = 0;
        while (z != 0) {
            if ((z & 1) == 1)
                num++;
            //这个地方必须是逻辑右移
            //即无符号右移
            //否则如果z为负数
            //>> 补码进行算术右移，高位会一直补1，该程序不会终止
            z >>>= 1;
        }
        return num;
    }
}


//class Father {
//    public void show() {
//        System.out.println("父类实例方法");
//    }
//    public static void staticShow() {
//        System.out.println("父类静态方法");
//    }
//}
//class Son extends Father {
//    @Override
//    public void show() {
//        System.out.println("子类实例方法");
//    }
//    public static void staticShow() {
//        System.out.println("子类静态方法");
//    }
//}
// class Test1 {
//    public static void main(String[] args) {
//        Father f = new Son();
//        f.show();
//        f.staticShow();
//    }
//}