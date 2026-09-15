package com.example.test.erfenfa;

import java.util.HashMap;
import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @description: 二分法查找与目标数据相同的数
 * @date 2026/2/28 9:55
 */
public class ErfenfaTest {


    // [10,18,23,26,30,48,50,60,69,70,88,100]

    /**
     * 查找数所在数组的位置
     *
     * @param target
     * @param arr
     * @return
     * @throws Exception
     */
    static Map<String, Integer> getNum(int target, int[] arr) throws Exception {
        int left = 0;
        int right = arr.length - 1;
        int idx = left + ((right - left) >> 1);
        HashMap<String, Integer> res = new HashMap<>();
        int count = 0;
        res.put("index", -1);
        res.put("count", 0);
        while (true) {
            count++;
            if (arr[idx] == target) {
                res.put("index", idx);
                res.put("count", ++count);
                return res;
            } else if (arr[idx] > target) {
                right = idx - 1;
            } else {
                left = idx + 1;
            }
            if (right <= left) {
                throw new Exception("没找到");
            }
            idx = left + ((right - left) >> 1);

        }
    }


    public static void main(String[] args) throws Exception {
        int[] arr = {10, 18, 23, 26, 30, 48, 50, 60, 69, 70, 88, 100};

        Map<String, Integer> res = ErfenfaTest.getNum(50, arr);
        System.out.println("查找次数=" + res.get("count") + ",所在位置==" + res.get("index"));

    }

}
