package com.tqx.find;


/**
 * @author Administrator
 * @version 1.0
 * @description: 线性查找
 * @date 2026/4/3 7:38
 */
public class Xianxing {
    private int[] obj;
    //长度，这里是数组长度-1，头结点为哨兵节点，存放需要查询的数据
    private int length;

    public Xianxing(int[] obj) {
        this.length = obj.length;
        this.obj = new int[this.length + 1];
        System.arraycopy(obj, 0, this.obj, 1, length);
    }

    //线性查找，将要查找的数据放入哨兵节点，从后往前找，这样能找到
    //就返回index，找不到的话直接返回哨兵节点的index=0，
    //就不需要在循环中依次判断索引是否越界了
    public int getIndex(int num) {
        obj[0] = num;
        int i = length;
        for (; obj[i] != num; i--) ;
        return i;
    }

    public static void main(String[] args) {
        int[] obj = {3, 5556, 77, 55, 22, 44, 88, 11};
        Xianxing xianxing = new Xianxing(obj);
        System.out.println(xianxing.getIndex(55));
    }

}
