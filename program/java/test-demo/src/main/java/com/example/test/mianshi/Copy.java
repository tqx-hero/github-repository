package com.example.test.mianshi;

/**
 * @author Administrator
 * @version 1.0
 * @description: 引用拷贝、浅拷贝、深拷贝
 * @date 2026/3/3 19:35
 */
public class Copy implements Cloneable {

    int age;
    int arr[];


    public Copy(int age, int[] arr) {
        this.age = age;
        this.arr = arr;
    }

    @Override
    protected Copy clone() throws CloneNotSupportedException {
        Copy copy = (Copy) super.clone();
        //在克隆方法里手动拷贝引用类型数据
        copy.arr = arr.clone();
        return copy;
    }

    public static void main(String[] args) throws CloneNotSupportedException {
        Copy copy = new Copy(10, new int[]{1, 2, 3});
        Copy copy1 = copy.clone();
        System.out.println(copy1 == copy);  //false
        copy1.age = 20;
        System.out.println(copy.age);  // 还是10没变，基本数据类型
        copy1.arr[0] = 10;
        System.out.println(copy.arr[0]);  // 还是1
    }

}
