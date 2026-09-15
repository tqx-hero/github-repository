package com.example.test.hash;

import com.example.test.entity.Entry;

import java.util.Arrays;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 手搓哈希表
 * @date 2026/2/27 9:50
 */
public class HashTableDemo {

    private int size = 10;

    private Entry[] buckets = new Entry[size];

    /**
     * 添加
     *
     * @param key
     * @param value
     */
    void put(Object key, Object value) {
        int hashed = HashMethod.hash(key);
        System.out.println("hash===" + hashed);
        Entry ent = buckets[hashed];
        if (ent != null) {
            while (ent != null) {
                if (ent.key.equals(key)) {
                    ent.value = value;
                    return;
                }
                ent = ent.next;
            }
        }
        Entry entry = new Entry(key, value);
        entry.next = ent == null ? null : ent;
        buckets[hashed] = entry;
    }

    /**
     * 删除头部节点
     *
     * @param entry
     * @param idx
     */
    void delFirst(Entry entry, int idx) {
        buckets[idx] = entry.next;
        entry.next = null;
        entry.key = null;
        entry.value = null;
    }

    /**
     * 去尾
     *
     * @param entry 需要去除的目标节点
     * @param prev  上个节点
     * @param idx   链表所在桶的hash
     */
    void delLast(Entry entry, Entry prev) {
        prev.next = null;
        entry.next = null;
        entry.key = null;
        entry.value = null;
    }

    void del(Object key) {
        int hash = HashMethod.hash(key);
        Entry entry = buckets[hash];
        if (Objects.isNull(entry)) throw new IndexOutOfBoundsException();
        Entry prev = new Entry();
        while (Objects.nonNull(entry)) {
            if (entry.key.equals(key)) {
                //去掉所在节点并返回
                //去头
                if (Objects.isNull(prev.key)) {
                    delFirst(entry, hash);
                }
                //去尾
                else if (Objects.isNull(entry.next)) {
                    delLast(entry, prev);
                }
                //去中
                else {
                    prev.next = entry.next;
                    entry.next = null;
                    entry.key = null;
                    entry.value = null;
                }
                return;
            }
            prev = entry;
            entry = entry.next;
        }
    }

    @Override
    public String toString() {
        return "HashTableDemo{" +
                "size=" + size +
                ", buckets=" + Arrays.toString(buckets) +
                '}';
    }

    public static void main(String[] args) {
        HashTableDemo hashTableDemo = new HashTableDemo();
        hashTableDemo.put(1, "a");
        hashTableDemo.put(2, "b");
        hashTableDemo.put(3, "c");
        hashTableDemo.put(4, "d");
        hashTableDemo.put(5, "e");
        hashTableDemo.put(6, "f");
        System.out.println(hashTableDemo);

        hashTableDemo.del(1);
        hashTableDemo.del(2);
        hashTableDemo.del(3);

        System.out.println(hashTableDemo);
    }

}
