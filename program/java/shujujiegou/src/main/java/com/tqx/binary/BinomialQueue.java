package com.tqx.binary;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 二项队列
 * 用一个deleting状态位锁住删除分离后的子树在添加时修改最小指针的操作，不让它进行无意义的操作.
 * 具体思路是：
 * 只有在删除操作时，将deleting设置为true，其他情况下均为false，在添加元素时，判断deleting的状态是否为删除状态
 * 删除状态(deleting=true)不进行对最小值指针的维护
 * 当删除操作结束时，修改deleting状态为false，同时将minIdx失效。即释放锁，这样其他添加操作均可执行对最小值指针的维护
 * @date 2026/4/14 9:47
 */
public class BinomialQueue<T> {

    private static final int DEFAULT_CAPACITY = 64;
    //存放所有堆，每个下标存放的堆内元素个数分别为：1,2,4,8,....
    private BQNode<T>[] bqArray;
    private int size;
    //队列有数据的最大index
    private int queueMaxIndex;

    //最小值所在的下标
    private int minIdx;
    //是否正在删除元素
    //默认为false。
    //如果为true，则在添加时不会维护minIdx
    private boolean deleting;

    @Override
    public String toString() {
        return "BinomialQueue{" +
                "bqArray=" + Arrays.toString(bqArray) +
                ", size=" + size +
                ", queueMaxIndex=" + queueMaxIndex +
                '}';
    }

    public BinomialQueue() {
        this(DEFAULT_CAPACITY);
    }

    public BinomialQueue(int size) {
        this.size = size;
        bqArray = new BQNode[size];
        queueMaxIndex = -1;
        minIdx = -1;
        deleting = false;
    }

    private static class BQNode<T> {
        KeyEntry<T> key;
        int degree;
        BQNode<T> child;
        BQNode<T> sibling;

        @Override
        public String toString() {
            return "BQNode{" +
                    "child=" + child +
                    ", key=" + key +
                    ", degree=" + degree +
                    ", sibling=" + sibling +
                    '}';
        }

        public BQNode(KeyEntry<T> key) {
            this.key = key;
        }
    }

    private static class KeyEntry<T> {
        int key;
        T value;

        @Override
        public String toString() {
            return "KeyEntry{" +
                    "key=" + key +
                    ", value=" + value +
                    '}';
        }

        public KeyEntry(int key, T value) {
            this.key = key;
            this.value = value;
        }
    }

    private void addNode(BQNode<T> node) {
        addNode(node, 0);
    }

    private void addNode(BQNode<T> node, int index) {
        if (node == null)
            return;
        if (index >= size || index < 0)
            throw new ArrayIndexOutOfBoundsException("下标越界");
        for (int i = index; i < size; i++) {
            if (bqArray[i] == null) {
                bqArray[i] = node;
                //更新队列有数据的最大index
                if (queueMaxIndex < i)
                    queueMaxIndex = i;
                //更新最小值下标
                //正在删除元素时不进行最小值维护
                if (!deleting && (minIdx == -1 || bqArray[i].key.key < bqArray[minIdx].key.key))
                    minIdx = i;
                return;
            }
            //如果不为空，则需要合并，并放入后续下标位置
            else {
                BQNode<T> smallNode = bqArray[i];
                BQNode<T> largeNode = node;
                if (smallNode.key.key > largeNode.key.key) {
                    smallNode = largeNode;
                    largeNode = bqArray[i];
                }
                //头插法插入child的sibling
                largeNode.sibling = smallNode.child;
                smallNode.child = largeNode;
                smallNode.degree++;
                bqArray[i] = null;
                //删除当前元素时将minIndex失效
                //仅在没有删除元素时维护
                if (!deleting)
                    minIdx = minIdx == i ? -1 : minIdx;
                node = smallNode;
            }
        }
    }

    private int getMinIndex() {
        for (int i = 0; i <= queueMaxIndex; i++) {
            if (bqArray[i] == null || bqArray[i].key == null)
                continue;
            if (minIdx == -1)
                minIdx = i;
            else
                minIdx = bqArray[minIdx].key.key < bqArray[i].key.key ? minIdx : i;
        }
        return minIdx;
    }

    public KeyEntry<T> findMin() {
        if (queueMaxIndex == -1)
            return null;
        return minIdx == -1 ? bqArray[getMinIndex()].key : bqArray[minIdx].key;
    }

    public BQNode<T>[] getArray() {
        return bqArray;
    }

    //合并另一个二项队列
    //将queue这个二项队列合并到this
    public void merge(BinomialQueue<T> queue) {
        //判断queue有没有数据，没有数据时，queueMaxIndex下标为-1
        if (queue.queueMaxIndex < 0)
            return;
        //合并最大次数最多为queue的含有数据的最大下标
        for (int i = 0; i <= queue.queueMaxIndex; i++)
            //当a1与a2两个相同位置均有数据时，合并
            addNode(queue.bqArray[i], i);
    }

    public void insert(int key, T value) {
        //下标0下面没有数据，直接新建节点放入
        addNode(new BQNode<>(new KeyEntry<>(key, value)));
    }

    //删除根节点时，首先将最小值的minIndex设置为-1
    //然后获取它的child，通过遍历child的sibling
    //根据child与sibling的度degree，插入到与degree相同的下标
    //add操作与之前相同
    public void deleteMin() {
        //先确保有数据
        //没有数据直接返回
        if (minIdx == -1 && getMinIndex() == -1)
            return;
        BQNode<T> curNode = bqArray[minIdx];
        //设置删除标志为true
        deleting = true;
        //重置最小值index
        BQNode<T> child = curNode.child;
        //摘链
        bqArray[minIdx] = null;
        curNode.child = null;
        //孩子不为空，则需要对孩子的所有节点
        //逐一重新插入到二项队列中
        while (child != null) {
            BQNode<T> sibling = child.sibling;
            int degree = child.degree;
            child.sibling = null;
            addNode(child, degree);
            child = sibling;
        }
        //更新极值
        updateQueueMaxIndex();
        minIdx = -1;
        deleting = false;
    }

    //更新存有元素的数组最大下标
    private void updateQueueMaxIndex() {
        int i = queueMaxIndex;
        for (; i >= 0 && bqArray[i] == null; i--) ;
        queueMaxIndex = i;
    }

    public static void main(String[] args) {
        BinomialQueue<Object> binomialQueue = new BinomialQueue<>();
        binomialQueue.insert(10, new Object());
        binomialQueue.insert(20, new Object());
        binomialQueue.insert(30, new Object());
        binomialQueue.insert(40, new Object());

        BinomialQueue<Object> b2 = new BinomialQueue<>();
        b2.insert(60, new Object());
        b2.insert(5, new Object());


        binomialQueue.merge(b2);

//        System.out.println(Arrays.toString(binomialQueue.getArray()));
        System.out.println(binomialQueue);

        System.out.println(binomialQueue.findMin());

        binomialQueue.deleteMin();
        System.out.println(binomialQueue);
        System.out.println(binomialQueue.findMin());

    }

}
