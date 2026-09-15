package com.tqx.fib;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: 斐波那契数列:后一个数是前两个数之和
 * 1 1 2 3 5 8 .....
 * @date 2026/4/10 18:55
 */
public class Fibonacci {

    ArrayList<Integer> memoryList = new ArrayList<>();

    //双指针实现，左右两个指针，分别向前挪，输出右指针所指数据
    public static List<Integer> run(int sum) {
        ArrayList<Integer> list = new ArrayList<>();
        int left = 1, right = 1;
        list.add(left);
        list.add(right);
        while (right < sum) {
            int temp = right;
            right += left;
            list.add(right);
            left = temp;
        }
        return list;
    }

    private int f(int n) {
        if (memoryList.size() > n)
            return memoryList.get(n);
        if (n == 0 || n == 1) {
            memoryList.add(1);
            return 1;
        }
        int result = f(n - 2) + f(n - 1);
        memoryList.add(result);
        return result;
    }

    public List<Integer> runByMath(int sum) {
        List<Integer> result = new ArrayList<>();
        for (int i = 0, s = 0; s < sum; i++)
            result.add(s = f(i));
        return result;
    }

    public static void main(String[] args) {
//        System.out.println(run(34));
        System.out.println(new Fibonacci().runByMath(34));
    }

}
