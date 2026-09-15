package com.tqx.tree;

import java.util.ArrayDeque;
import java.util.Iterator;

/**
 * @author Administrator
 * @version 1.0
 * @description: 编写TreeSet
 * @date 2026/4/10 9:33
 */
@SuppressWarnings("uncheck")
public class MyTreeSet<T> {

    private SetEntry<T> root;
    private int count;
    private static final int SENTINEL_HASH = -1;
    private static final int LEFT_TREE = 0;
    private static final int RIGHT_TREE = 1;

    private static class SetEntry<T> implements Cloneable, Iterable<T> {

        private static final SetEntry<?> SENTINEL_ENTRY = new SetEntry<>(-1, null);
        int hash;
        T key;
        SetEntry<T> left;
        SetEntry<T> right;
        SetEntry<T> parent;
        boolean visited;

        public SetEntry<T> setVisited(boolean visited) {
            this.visited = visited;
            return this;
        }

        public SetEntry() {
        }

        public SetEntry<T> setParent(SetEntry<T> parent) {
            this.parent = parent;
            return this;
        }

        public SetEntry(int hash, T key, SetEntry<T> parent) {
            this.hash = hash;
            this.key = key;
            this.parent = parent;
        }

        public SetEntry(int hash, T key) {
            this.hash = hash;
            this.key = key;
        }

        @Override
        public String toString() {
            return "SetEntry{" +
                    "hash=" + hash +
                    ", key=" + key +
                    ", left=" + left +
                    ", right=" + right +
                    '}';
        }

        @Override
        @SuppressWarnings("uncheck")
        public SetEntry<T> clone() {
            try {
                return (SetEntry<T>) super.clone();
            } catch (CloneNotSupportedException e) {
                throw new AssertionError();
            }
        }

        @Override
        public Iterator<T> iterator() {
            return new SetIterator<>(this);
        }
    }

    private static class SetIterator<T> implements Iterator<T> {
        private SetEntry<T> entry;
        private ArrayDeque<SetEntry<T>> stack;

        public SetIterator(SetEntry<T> entry) {
            this.entry = entry;
            this.stack = new ArrayDeque<>();

            //惰性压栈，只压左子树的左边
            pushLeft();
//            //压入栈内
//            push(entry);
        }

        private void pushLeft() {
            SetEntry<T> e = entry;
            while (e.hash != SENTINEL_HASH) {
                stack.push(e);
                e = e.left;
            }
        }

        //全部压栈
        //如果树过高，容易出现OOM
        private void push(SetEntry<T> entry) {
            //中序压栈
            if (entry.hash != SENTINEL_HASH) {
                SetEntry<T> right = entry.right;
                push(right);
                if (right.hash != SENTINEL_HASH && !right.visited)
                    stack.push(right.setVisited(true));
                stack.push(entry.setVisited(true));
                SetEntry<T> left = entry.left;
                push(left);
                if (left.hash != SENTINEL_HASH && !left.visited)
                    stack.push(left.setVisited(true));
            }
        }

        @Override
        public boolean hasNext() {
            return !stack.isEmpty();
        }

        @Override
        public T next() {
            SetEntry<T> p = stack.pop();
            SetEntry<T> r = p.right;
            //迭代时在压入右子树的左子树
            while (r.hash != SENTINEL_HASH) {
                stack.push(r);
                r = r.left;
            }
            return p.key;

//            if (stack.isEmpty())
//                return null;
//            return stack.pop();
        }
    }

    @Override
    public String toString() {
        return "MyTreeSet{" +
                "count=" + count +
                ", root=" + root +
                '}';
    }

    @SuppressWarnings("uncheck")
    private SetEntry<T> getSentinelEntry() {
        return (SetEntry<T>) SetEntry.SENTINEL_ENTRY.clone();
    }

    public MyTreeSet() {
        this.root = new SetEntry<>(SENTINEL_HASH, null);
        //设置初始两个哨兵节点
        root.left = getSentinelEntry().setParent(root);
    }

    private int getHash(Object key) {
        int h;
        return (key == null) ? 0 : (h = key.hashCode()) ^ (h >>> 16);
    }

    private SetEntry<T> findPosition(int hash, SetEntry<T> cur) {
        if (cur.hash == SENTINEL_HASH)
            return cur.parent;
        if (cur.hash == hash)
            return cur;
        else if (cur.hash < hash)
            //往右找
            cur = findPosition(hash, cur.right);
        else
            cur = findPosition(hash, cur.left);
        //等于null，则找到他的parent，返回
        return cur;
    }

    public void add(T o) {
        int hash = getHash(o);
        SetEntry<T> parent = findPosition(hash, root.left);
        //相同的说明已在树中，直接返回
        if (parent.hash == hash)
            return;
        SetEntry<T> setEntry = new SetEntry<>(hash, o, parent);
        if (parent.hash == SENTINEL_HASH) {
            root.left = setEntry;
        } else {
            if (parent.hash > hash)
                parent.left = setEntry;
            else
                parent.right = setEntry;
        }
        setEntry.left = getSentinelEntry().setParent(setEntry);
        setEntry.right = getSentinelEntry().setParent(setEntry);
    }

    public SetEntry<T> getRoot() {
        return root.left;
    }

    //查找节点的前驱或者后继
    public SetEntry<T> successor(SetEntry<T> entry) {
        if (entry.right.hash != SENTINEL_HASH) {
            SetEntry<T> r = entry.right;
            while (r.hash != SENTINEL_HASH)
                r = r.left;
            return r.parent;
        } else {
            SetEntry<T> l = entry.left;
            while (l.hash != SENTINEL_HASH)
                l = l.right;
            return l.parent;
        }
    }

    private void delete(SetEntry<T> cur) {
        if (cur.hash == SENTINEL_HASH)
            return;
        SetEntry<T> p = cur.parent;
        SetEntry<T> left = cur.left;
        SetEntry<T> right = cur.right;
        int type;
        if (p.left.hash == cur.hash)
            type = LEFT_TREE;
        else
            type = RIGHT_TREE;
        SetEntry<T> c = left;
        if (left.hash == SENTINEL_HASH && right.hash == SENTINEL_HASH)
            c = getSentinelEntry().setParent(p);
        else if (left.hash == SENTINEL_HASH)
            c = right;

        if (type == LEFT_TREE)
            p.left = c;
        else
            p.right = c;

        c.parent = p;
        cur.parent = null;
    }


    public Object remove(Object o) {
        int hash = getHash(o);
        SetEntry<T> cur = findPosition(hash, root.left);
        //没找到直接返回
        if (cur.hash != hash)
            return o;
        //找到了就开始删除
        if (cur.left.hash == SENTINEL_HASH && cur.right.hash == SENTINEL_HASH)
            //没孩子直接删除
            delete(cur);
        else {
            SetEntry<T> s = successor(cur);
            cur.hash = s.hash;
            cur.key = s.key;
            //删除后继或者前驱节点
            delete(s);
        }
        return o;
    }

    public static void main(String[] args) {
        MyTreeSet<Integer> set = new MyTreeSet<>();
        set.add(6);
        set.add(7);
        set.add(8);
        set.add(1);
        System.out.println(set.getRoot());
        //增强for循环形式
        for (Integer i : set.getRoot()) {
            System.out.println(i);
        }
        //迭代器形式
//        Iterator it = set.getRoot().iterator();
//        while (it.hasNext()) {
//            System.out.println(it.next());
//        }
//        set.remove(6);
//        set.remove(1);
//        set.remove(8);
//        set.remove(7);
//        System.out.println(set.getRoot());
    }

}
