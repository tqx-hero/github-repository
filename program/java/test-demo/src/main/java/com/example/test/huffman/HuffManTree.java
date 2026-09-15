package com.example.test.huffman;


import java.util.Arrays;
import java.util.List;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/1 12:02
 */
public class HuffManTree<T> {

    static class SmallHeap<T> {

        public int parIdx = -1;
        private static final int MAX_SIZE = 30;
        private HuffManTree[] hepArray;

        @Override
        public String toString() {
            return "SmallHeap{" +
                    "hepArray=" + Arrays.toString(hepArray) +
                    ", parIdx=" + parIdx +
                    ", size=" + size +
                    '}';
        }

        /**
         * 获取堆顶数据
         *
         * @return
         */
        public HuffManTree<T> getTop() {
            return size == 0 ? null : hepArray[0];
        }

        public SmallHeap(HuffManTree<T>[] hepArray) {
            this.hepArray = hepArray;
        }

        public SmallHeap() {
        }

        public int size = 0;


        /**
         * 给堆添加数据，小堆实现上浮
         *
         * @param v
         */
        public void add(HuffManTree<T> v) {
            if (Objects.isNull(hepArray))
                hepArray = new HuffManTree[MAX_SIZE];
            hepArray[size++] = v;
            //小堆比较最新数据与父节点，比父节点小则上浮,以此类推
            if (size > 1) {
//            parIdx = (size - 1) >> 1;
                swim(size - 1, v);
            }

        }

        private void swim(int parIdx, HuffManTree<T> val) {
            int parentIdx = parIdx - 1 < 0 ? parIdx - 1 : (parIdx - 1) >> 1;
            if (parentIdx < 0) {
                return;
            }
            HuffManTree<T> par = hepArray[parentIdx];
            if (par.weight > val.weight) {
                hepArray[parentIdx] = val;
                hepArray[parIdx] = par;
                swim(parentIdx, val);
            }

        }

        /**
         * 删除小顶堆的堆顶
         */
        public void del() {
//        if (size == 0) return;
            if (size < 1) hepArray[0] = null;
            else {
                //将最末端数值赋给根节点，同时进行下沉操作
                hepArray[0] = hepArray[size - 1];
                hepArray[(size--) - 1] = null;

                //根节点与子节点数值比较，大就下沉
                sink(0);
            }
        }

        /**
         * 小顶堆删除头后下沉数据
         *
         * @param parIdx 删除的索引
         */
        void sink(int parIdx) {
            if (parIdx >= size) {
                return;
            }
            int leftIdx = (parIdx << 1) + 1;
            int rightIdx = (parIdx + 1) << 1;
            int childInx = 0;
            if (leftIdx >= size) return;
            if (rightIdx < size && hepArray[rightIdx].weight < hepArray[leftIdx].weight && hepArray[rightIdx].weight < hepArray[parIdx].weight) {
                childInx = rightIdx;
            } else if (hepArray[leftIdx].weight < hepArray[parIdx].weight) {
                childInx = leftIdx;
            }
            if (childInx != 0) {
                HuffManTree tmp = hepArray[childInx];
                hepArray[childInx] = hepArray[parIdx];
                hepArray[parIdx] = tmp;
                sink(childInx);
            }
        }

        /**
         * 弹出堆顶数据
         *
         * @return
         */
        HuffManTree<T> pop() {
            HuffManTree<T> top = null;
            if (Objects.nonNull(getTop())) {
                top = getTop();
                del();
            }
            return top;
        }
    }

    public HuffManTree() {
    }

    int weight = -1; //权重
    T ch;  //存放的数据
    HuffManTree<T> left;
    HuffManTree<T> right;

    public HuffManTree(T ch, HuffManTree<T> left, HuffManTree<T> right, int weight) {
        this.ch = ch;
        this.left = left;
        this.right = right;
        this.weight = weight;
    }

    public HuffManTree(T ch, int weight) {
        this.ch = ch;
        this.weight = weight;
    }

    @Override
    public String toString() {
        return "HuffManTree{" +
                "ch=" + ch +
                ", weight=" + weight +
                ", left=" + left +
                ", right=" + right +
                '}';
    }

    public HuffManTree<T> init(List<HuffManTree<T>> list) {
        if (Objects.isNull(list)) return null;
        //将树放入小顶堆，拿出堆顶
        SmallHeap<T> smallHeap = new SmallHeap<>();
        for (int i = 0; i < list.size(); i++) {
            smallHeap.add(list.get(i));
        }
        //比较权重，组成新哈夫曼树
        while (smallHeap.size > 1) {
            HuffManTree<T> left = smallHeap.pop();
            HuffManTree<T> right = smallHeap.getTop() == null ? null : smallHeap.pop();
            smallHeap.add(new HuffManTree<>(null, left, right, left.weight + right.weight));
        }
        return smallHeap.pop();
    }


    public static void main(String[] args) {
        HuffManTree<Character> a = new HuffManTree<>('A', 7);
        HuffManTree<Character> b = new HuffManTree<>('B', 4);
        HuffManTree<Character> c = new HuffManTree<>('C', 5);
        HuffManTree<Character> d = new HuffManTree<>('D', 2);
        HuffManTree<Character> news = new HuffManTree().init(List.of(a, b, c, d));
        System.out.println(news);
    }
}
