package com.tqx.hash;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/27 21:40
 */
public class HashMp<K, V> {

    private static final int DEFAULT_INITSIZE = 16;

    private Entry<K, V>[] elementData;
    private int size;
    private Entry<K, V>[] elementDataBk;
    private int initSize;

    static class Entry<K, V> {
        K key;
        V val;
        Entry<K, V> next;

        public Entry<K, V> setNext(Entry<K, V> next) {
            this.next = next;
            return this;
        }

        public Entry() {
        }

        public Entry(K key, V val) {
            this.key = key;
            this.val = val;
        }

        public boolean containsKey(K key) {
            Entry<K, V> n = this;
            for (K k = n.key; n != null; n = n.next, k = n.key) {
                if (k.equals(key))
                    return true;
            }
            return false;
        }

        public Entry<K, V> getEntry(K key) {
            Entry<K, V> n = this;
            for (K k = n.key; n != null; n = n.next, k = n.key) {
                if (k.equals(key))
                    return n;
            }
            return null;
        }

        public Entry<K, V> containsAndUpdate(K key, V val) {
            Entry<K, V> n = this;
            for (K k = n.key; n != null; n = n.next, k = n.key) {
                if (k.equals(key)) {
                    n.val = val;
                    return n;
                }
            }
            return null;
        }


        public Entry<K, V> addEntry(K key, V val) {
            Entry<K, V> res;
            if ((res = containsAndUpdate(key, val)) == null)
                res = new Entry<>(key, val).setNext(this);
            return res;
        }
    }

    public int size() {
        return this.size;
    }

    public V get(K key) {
        Entry<K, V> el = elementData[getIdx(key)];
        if (el == null)
            return null;
        if ((el = el.getEntry(key)) == null)
            return null;
        return el.val;
    }

    public void put(K key, V val) {
        int idx = this.getIdx(key);
        elementData[idx] = elementData[idx] == null
                ? new Entry<>(key, val) :
                this.addLinks(key, val, elementData[idx]);
        size++;
    }

    private Entry<K, V> addLinks(K key, V val, Entry<K, V> e) {
        return e.addEntry(key, val);
    }


    int getIdx(K key) {
        return key.hashCode() & (initSize - 1);
    }

    static int getInitSize(int init) {
        return Integer.highestOneBit(init - 1) << 1;
    }

    public static void main(String[] args) {
        HashMp<String, Integer> mp = new HashMp<>();
        mp.put("name", 123);
        System.out.println(mp.size());
        System.out.println(mp.get("name"));
        mp.put("name", 333);
        System.out.println(mp.get("name"));
    }

    public HashMp(int initSize) {
        this.initSize = initSize;
        elementData = new Entry[getInitSize(initSize)];
    }

    public HashMp() {
        this(DEFAULT_INITSIZE);
    }
}
