package com.tqx.find;

/**
 * @author Administrator
 * @version 1.0
 * @description: 链表形式的分块查找
 * @date 2026/4/3 11:49
 */
public class FenkuaiSearchLinked {

    private Entry[] obj;
    private int keySize;


    static class Entry {
        int maxVal;
        EntryNode firstNode;

        @Override
        public String toString() {
            return "Entry{" +
                    "firstNode=" + firstNode +
                    ", maxVal=" + maxVal +
                    '}';
        }
    }

    static class EntryNode {
        int value;
        EntryNode next;

        public EntryNode(int value, EntryNode next) {
            this.value = value;
            this.next = next;
        }

        @Override
        public String toString() {
            return "EntryNode{" +
                    "next=" + next +
                    ", value=" + value +
                    '}';
        }
    }

    public FenkuaiSearchLinked(int keySize, int[] obj) {
        this.keySize = keySize;
        this.obj = new Entry[keySize];
        for (int i = 0; i < keySize; i++) {
            this.obj[i] = new Entry();
        }
        init(obj);
    }

    //int[] obj = {3, 55, 22, 44,  77, 88, 66,58,  89,99,100,2333};
    private void init(int[] obj) {
        if (obj == null || obj.length == 0)
            return;
        int length = obj.length;
        int nums = (int) Math.ceil((double) length / keySize);

        for (int i = 0; i < keySize; i++) {
            int begin = i * nums;
            int end = Math.min((i + 1) * nums - 1, length - 1);
            //放入桶的链表并查找最大值
            int maxVal = -1;
            for (; begin <= end; begin++) {
                int i1 = obj[begin];
                this.obj[i].firstNode = new EntryNode(i1, this.obj[i].firstNode);
                if (i1 > maxVal)
                    maxVal = i1;
            }
            this.obj[i].maxVal = maxVal;
        }
    }

    public EntryNode getIndex(int num) {
        for (Entry entry : obj) {
            if (entry.maxVal >= num) {
                EntryNode node = entry.firstNode;
                while (node != null) {
                    if (node.value == num)
                        return node;
                    node = node.next;
                }
            }
        }
        return null;
    }

    public static void main(String[] args) {
        int[] obj = {3, 55, 22, 44, 77, 88, 66, 58, 89, 99, 100, 2333};
        FenkuaiSearchLinked fs = new FenkuaiSearchLinked(3, obj);
        System.out.println(fs.getIndex(55));
    }

}
