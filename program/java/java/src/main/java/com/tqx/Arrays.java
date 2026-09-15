package com.tqx;

import java.util.Iterator;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/6 20:34
 */
public class Arrays implements Iterable {

    private int size;

    public Arrays(int size) {
        this.size = size;
        this.arr = new int[size];
    }

    public Arrays(int[] arr, int size) {
        this.arr = arr;
        this.size = size;
    }

    private int[] arr;

    public Iterator<Integer> reverseIterator() {
        return new ArrayReverse();
    }

    @Override
    public Iterator<Integer> iterator() {
        return new ArrayIter();
    }

    private class ArrayReverse implements Iterator {
        int index = size - 1;

        @Override
        public boolean hasNext() {
            return index >= 0;
        }

        @Override
        public Object next() {
            return arr[index--];
        }
    }

    private class ArrayIter implements Iterator {
        int index = 0;

        @Override
        public boolean hasNext() {
            if (size == 0)
                return false;
            return index < size;
        }

        @Override
        public Object next() {
            return arr[index++];
        }
    }
}

class Test {
    public static void main(String[] args) {
//        Arrays arrays = new Arrays(new int[]{10, 9, 28, 33, 4}, 5);
//
////        for (Object o : arrays) {
////            System.out.println(o);
////        }
//
//        //正序遍历
//        Iterator<Integer> iterator = arrays.iterator();
//        while (iterator.hasNext()) {
//            System.out.println(iterator.next());
//        }
//        System.out.println("倒序遍历");
//        //倒序
//        Iterator<Integer> r = arrays.reverseIterator();
//        while (r.hasNext()) {
//            System.out.println(r.next());
//        }
        System.out.println(Integer.parseInt("a9DE",16));


    }
}
