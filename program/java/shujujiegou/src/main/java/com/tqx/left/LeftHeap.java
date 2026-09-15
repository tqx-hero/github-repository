package com.tqx.left;

import javax.crypto.interfaces.PBEKey;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicLong;

/**
 * @author Administrator
 * @version 1.0
 * @description: 左偏树（左式堆）
 * @date 2026/4/14 15:41
 */
public class LeftHeap<T> {
    private static final int SENTINEL_NPL = -1;
    private static final AtomicLong UUID_MAKER;
    private LeftHeapNode<T> root;
    private int count;
    //根节点,路径压缩
    private Map<Long, LeftHeapNode<T>> father;

    static {
        UUID_MAKER = new AtomicLong(0L);
    }

    public LeftHeap() {
        this.father = new HashMap<>();
        //初始化哨兵节点
        this.root = getSentinel();
        root.right = getSentinel().parent(root);
    }

    private static class LeftHeapNode<T> implements Cloneable {
        private static final LeftHeapNode<?> SENTINEL_NODE = new LeftHeapNode<>(new HeapEntry<>(-1, null), SENTINEL_NPL);
        HeapEntry<T> key;
        LeftHeapNode<T> left, right, parent;
        //零路径长度
        int npl;
        //设置唯一标识uuid
        long uuid;

        @Override
        public String toString() {
            return "LeftHeapNode{" +
                    "key=" + key +
                    ", left=" + left +
                    ", right=" + right +
                    ", npl=" + npl +
                    ", uuid=" + uuid +
                    '}';
        }

        public LeftHeapNode<T> right(LeftHeapNode<T> right) {
            this.right = right;
            return this;
        }

        public LeftHeapNode<T> npl(int npl) {
            this.npl = npl;
            return this;
        }

        public LeftHeapNode<T> parent(LeftHeapNode<T> parent) {
            this.parent = parent;
            return this;
        }

        public LeftHeapNode(HeapEntry<T> key, int npl) {
            this.key = key;
            this.npl = npl;
            this.uuid = getUuid();
        }

        public LeftHeapNode(HeapEntry<T> key) {
            this(key, 0);
        }

        @Override
        protected LeftHeapNode<T> clone() {
            try {
                return (LeftHeapNode<T>) super.clone();
            } catch (CloneNotSupportedException e) {
                throw new RuntimeException(e);
            }
        }

        private long getUuid() {
            return UUID_MAKER.getAndIncrement();
        }
    }


    private LeftHeapNode<T> getSentinel() {
        return (LeftHeapNode<T>) LeftHeapNode.SENTINEL_NODE.clone();
    }

    @Override
    public String toString() {
        return "LeftHeap{" +
                "count=" + count +
                ", root=" + root +
                ", father=" + father +
                '}';
    }

    private static class HeapEntry<T> {
        int key;
        T value;

        public HeapEntry(int key, T value) {
            this.key = key;
            this.value = value;
        }

        @Override
        public String toString() {
            return "HeapEntry{" +
                    "key=" + key +
                    ", value=" + value +
                    '}';
        }
    }

    //删除最小值堆顶
    public LeftHeapNode<T> deleteMin() {
        LeftHeapNode<T> m = root.right;
        //拆分它的左右子树，两个树按照merge规则进行合并
        //断开原来根节点与左右子树的连接
        m.left.parent = root.right(m.left);
        m.right.parent = getSentinel().npl(0).right(m.right);
        merge(m.left, m.right);
        m.left = getSentinel().parent(m);
        m.right = getSentinel().parent(m);
        //更新删除节点的根节点
        father.put(m.uuid, root.right);
        return m;
    }


    private LeftHeapNode<T> find(LeftHeapNode<T> n) {
        //倒到跟了，返回根节点
        if (n.npl == SENTINEL_NPL)
            return n.right;
        long un = n.uuid;
        LeftHeapNode<T> f = father.get(un);
        if (f == null)
            return n;
        if (n.parent.npl == SENTINEL_NPL || f.uuid == n.parent.uuid)
            return f;
        LeftHeapNode<T> r = find(f.parent);
        father.put(f.uuid, r);
        return r;
    }

    private LeftHeapNode<T> addNode(LeftHeapNode<T> a, LeftHeapNode<T> b) {
        if (b.npl == SENTINEL_NPL) return a;
        if (a.npl == SENTINEL_NPL) return b;
        //设置a为较小值节点，b为较大值节点
        if (a.key.key > b.key.key) {
            LeftHeapNode<T> temp = a;
            a = b;
            b = temp;
        }

        a.right = addNode(a.right, b);
        a.right.parent = a;
        if (a.right.npl > a.left.npl) {
            LeftHeapNode<T> temp = a.right;
            a.right = a.left;
            a.left = temp;
        }
        a.npl = a.right.npl + 1;
        if (a.left.npl != SENTINEL_NPL)
            find(a.left);
        if (a.right.npl != SENTINEL_NPL)
            find(a.right);
        return a;
    }


    public LeftHeapNode<T> merge(LeftHeapNode<T> b) {
        father.put(root.uuid, root.right = addNode(b, root.right).parent(root));
        return root.right;
    }

    public LeftHeapNode<T> merge(LeftHeapNode<T> a, LeftHeapNode<T> b) {
        father.put(root.uuid, root.right = addNode(a, b).parent(root));
        return root.right;
    }

    public LeftHeapNode<T> getHeap() {
        return root.right;
    }

    public void insert(int key, T value) {
        HeapEntry<T> entry = new HeapEntry<>(key, value);
        LeftHeapNode<T> newNode = new LeftHeapNode<>(entry);
        newNode.left = getSentinel().parent(newNode);
        newNode.right = getSentinel().parent(newNode);
        father.put(newNode.uuid, newNode);
        merge(newNode);
    }

    public static void main(String[] args) {
        LeftHeap<Object> heap = new LeftHeap<>();
        heap.insert(1, 20);
        heap.insert(10, 20);
        heap.insert(3, 20);
        heap.insert(5, 20);
        heap.insert(6, 20);
        heap.insert(7, 20);
        System.out.println(heap.getHeap());

        System.out.println(heap.deleteMin());
        System.out.println(heap);
        heap.insert(9, 20);
        System.out.println(123);
    }

}
