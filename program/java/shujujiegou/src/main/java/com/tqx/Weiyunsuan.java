package com.tqx;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/10 15:24
 */
public class Weiyunsuan {

    //数组中只有一个数不重复，其余两两重复，找出这个不重复的数
    public static int get(int[] arr) {
        int res = 0;
        for (int i : arr) {
            res ^= i;  //利用了异或运算的特点：只有1个为0，1个为1时才会是1，并且a^a=0;a^0 =a;
        }
        return res;
    }

    //数组中只有两个数不重复，其余两两重复，找出这两个数
    public static int[] getArr(int[] arr) {
        //先对数组内所有数据异或操作，拿到这两个不同数据的异或结果
        int ab = 0;
        for (int i : arr)
            ab ^= i;
        //由于异或是位上的值不相同才会出现1，所以可以以这个为突破口，找到这两个数最后一位1的那一位
        //这里利用了数据与它的负数进行与运算会得到最后一个1的位数
        // -ab = ~ab +1;
        int s = ab & -ab;
        int res1 = 0, res2 = 0;
        for (int i : arr) {
            //与运算不为0，说明i与s在有1的位置同时都有1，那就可以用异或筛选出有1的那个不重复的数
            if ((s & i) != 0)
                res1 ^= i;
                //与运算为0，s那一位是1，说明i的同位置是0，继续异或运算，能筛选出那一位为0的数
            else
                res2 ^= i;
        }
        return new int[]{res1, res2};
    }

    //判断是否是2的整数幂
    public static boolean config(int a) {
        return a > 0 && (a & (a - 1)) == 0;
    }

    //计算一个整数二进制中含有几个1
    public static int count(int a) {
        if (a == 0)
            return 0;
        int count = 0;
        while ((a & ((a--) - 1)) != 0)
            count++;
        return count;
    }

     static class Student{
        String name;
        int age;

         @Override
         public String toString() {
             return "Student{" +
                     "name='" + name + '\'' +
                     ", age=" + age +
                     '}';
         }
     }

   static void setStu(Student stu){
        stu.name ="张三";
        stu.age=18;
    }

    public static void main(String[] args) {
//        int[] arr = {10, 20, 30, 40, 20, 30};
//        System.out.println(Arrays.toString(getArr(arr)));
//        System.out.println(config(18));
//        System.out.println(count(10));
//        System.out.println(Integer.toBinaryString('2'));
//        char c ='a';
//        System.out.println((char) 97);
//
//        Student student = new Student();
//        setStu(student);
//
//        System.out.println(student);


        int i = 0;
        int [] arr= {1,2,3,4,5,6,7,8,9,10};
        for ( i = 0; i < 10; i++) {
            arr[i]=0;
            System.out.print("....");
        }
    }
}
