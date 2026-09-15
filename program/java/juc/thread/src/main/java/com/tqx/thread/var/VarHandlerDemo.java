package com.tqx.thread.var;

import java.lang.invoke.MethodHandles;
import java.lang.invoke.VarHandle;
import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/19 17:38
 */
public class VarHandlerDemo {

    private String name;
    private static Integer age;

    private volatile int[] nums;

    {
        name = "张三";
        age = 10;
        nums = new int[]{1, 2, 3, 4, 5, 6};
    }


    public static void main(String[] args) {
        VarHandlerDemo demo = new VarHandlerDemo();
        demo.casName(demo.name, "李四");
        demo.casAge(10, 20);
        int[] ints = demo.nums;
        int[] ints1 = Arrays.copyOf(ints, ints.length + 1);
        ints1[ints1.length - 1] = 10;
        demo.casNums(ints, ints1);
        System.out.println(demo.name + ":" + age + ",nums=" + Arrays.toString(demo.nums));

    }

    private static final VarHandle NAME;
    private static final VarHandle AGE;
    private static final VarHandle NUMS;

    static {
        MethodHandles.Lookup lookup = MethodHandles.lookup();
        try {
            NAME = lookup.findVarHandle(VarHandlerDemo.class, "name", String.class);
            AGE = lookup.findStaticVarHandle(VarHandlerDemo.class, "age", Integer.class);
            NUMS = lookup.findVarHandle(VarHandlerDemo.class, "nums", int[].class);
        } catch (NoSuchFieldException e) {
            throw new RuntimeException(e);
        } catch (IllegalAccessException e) {
            throw new RuntimeException(e);
        }
    }

    //修改数组
    private boolean casNums(int[] i, int[] j) {
        return NUMS.compareAndSet(this, i, j);
    }

    //修改静态变量
    private boolean casAge(Integer oldVal, Integer newVal) {
        return AGE.compareAndSet(oldVal, newVal);
    }

    private boolean casName(String oldName, String newName) {
        return NAME.compareAndSet(this, oldName, newName);
    }

}
