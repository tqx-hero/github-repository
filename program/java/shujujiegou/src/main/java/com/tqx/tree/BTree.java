package com.tqx.tree;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @description: 手写B树
 * @date 2026/4/9 11:16
 */
public class BTree {
    @Override
    public String toString() {
        return "BTree{" +
                "root=" + root +
                ", stage=" + stage +
                '}';
    }

    //标记0为叶子结点
    private static final int LEAF = 0;
    private static final int NO_LEAF = 1;
    private static final int SENTINEL = 2;
    private static final String KEY = "key";
    private static final String VALUE = "value";
    private BTreeNode root;
    private int stage;
    //后哨数据
    private static final int MAX_VALUE = Integer.MAX_VALUE - 1;

    //B树的Node节点
    private static class BTreeNode {
        @Override
        public String toString() {
            return "BTreeNode{" +
                    "children=" + Arrays.toString(children) +
                    ", keys=" + Arrays.toString(keys) +
                    ", maxSize=" + maxSize +
                    ", count=" + count +
                    ", leaf=" + leaf +
                    '}';
        }

        //每个节点的key集合，设置size=阶数m，这里额外设置一个前哨节点，应该算叫后哨
        //在遍历时不需要再进行判断，直接就可以与下方的children数组一一对应上
        KeyData[] keys;
        int maxSize;
        //key的数量，这里不统计哨兵节点
        int count;
        //同样设置的是阶数大小，与上方key集合一一对应
        BTreeNode[] children;
        //是否为叶子结点，默认0:叶子结点，1：普通节点；2、前哨节点
        int leaf;
        //父节点指针，在分裂时用到
        BTreeNode parent;

        public BTreeNode() {
        }

        public BTreeNode(int maxSize) {
            this.maxSize = maxSize + 1;
            keys = new KeyData[this.maxSize];
            children = new BTreeNode[this.maxSize];
            leaf = LEAF;
            count = 0;
            //设置后哨数据，该数据不计入count，只是为了方便与children数组作对照
            keys[0] = new KeyData(MAX_VALUE);
        }

        public BTreeNode setLeaf(int leaf) {
            this.leaf = leaf;
            return this;
        }
    }

    private static class KeyData {
        //key值与其他杂项
        int key;
        Object others;

        @Override
        public String toString() {
            return "KeyData{" +
                    "key=" + key +
                    ", others=" + others +
                    '}';
        }

        public KeyData(int key) {
            this.key = key;
        }

        public KeyData(int key, Object others) {
            this.key = key;
            this.others = others;
        }
    }

    public BTree(int stage) {
        this.stage = stage;
        //设置前哨节点，将节点root指向前哨节点
        root = new BTreeNode().setLeaf(SENTINEL);
        root.children = new BTreeNode[1];
        BTreeNode bTreeNode = new BTreeNode(stage);
        bTreeNode.parent = root;
        root.children[0] = bTreeNode;
    }

    private void findCurrentLeafNode(KeyData keyData, BTreeNode curr) {
        BTreeNode cur = curr;
        int count = cur.count;
        //二分查找
        //中间位置数据>要插入的数据，只在[0,mid-1]找，否则在[mid+1,count]查找
        int mid = count >>> 1;
        int head = 0, tail = count;
        if (cur.keys[mid].key > keyData.key)
            tail = mid;
        else
            head = mid + 1;
        //二分查找，以头尾节点查看
        for (int i = head; i <= tail; i++) {
            int key = cur.keys[i].key;
            //找到符合的key，如果有相同的，进行修改数据
            if (keyData.key == key) {
                cur.keys[i] = keyData;
                return;
            }
            //比较当小于key时，查看该节点是否为叶子节点
            // 不是，找到对应的children数组的下一个Node继续找，直到找到叶子节点
            //是叶子结点，则将数据插入到该节点
            else if (keyData.key < key) {
                //不是叶子，继续往下找
                if (cur.leaf != LEAF) {
                    findCurrentLeafNode(keyData, cur.children[i]);
                    break;
                }

                /// ////////////////////////////////////////////////////////////
                //是叶子，插入数据
                //先将该坐标i往后的所有数据全部右挪一位，然后插入
                //这里可以再次优化，先不插入，看看count是否已经等于阶数maxSize-1，
                // 如果等于，就需要拆分，这样省去了往后挪动插入的动作，直接可以进行替换等
                for (int j = count; j >= i; j--)
                    cur.keys[j + 1] = cur.keys[j];
                cur.keys[i] = keyData;
                //判断count是否等于阶数
                //小于直接返回
                if (++cur.count < stage)
                    return;
                //大于则需要分裂当前树，将中间节点并入到上层
                doSplitNode(cur);
                return;


                //下方是对上方的优化
                /// ////////////////////////////////////////////////////////////////////////////////
                //先判断我如果添加以后,该节点的数据是否超出阶数限制
                //没有超出就继续添加
//                if ((cur.count + 1) < stage) {
//                    for (int j = count; j >= i; j--)
//                        cur.keys[j + 1] = cur.keys[j];
//                    cur.keys[i] = keyData;
//                    cur.count++;
//                    return;
//                }
//                //超出限制则需要进行先拆分，拆分完了根据拆分的位置以及数据要插入的下标确定要添加的部分（属于前半部分还是后半部分），然后在再添加
//                //这样省去了一次多余的添加操作
//                //1、需要传入当前i下标，即表示需要从当前下标插入该数据keyData
//                //2、需要传入keyData，这个不用说
//                //3、传入cur，具体分家等事项
//                doSplitNode(cur, i, keyData);
//                return;
            }

        }
    }

    //分裂节点中的key成为新的node
    private BTreeNode splitNodeElement(BTreeNode cur, int begin, int end) {
        BTreeNode splitNode = new BTreeNode(stage).setLeaf(cur.leaf);
        int idx = 0;
        for (int i = begin; i <= end; i++) {
            splitNode.keys[idx] = cur.keys[i];
            splitNode.children[idx] = cur.children[i];
            splitNode.count++;
            idx++;
        }
        //如果没有前哨位置，新增一个，同时将分割元素所在下标的children赋值过来接上
        splitNode.keys[idx] = new KeyData(MAX_VALUE);
        //将end+1的数据拷贝过来
        splitNode.children[idx] = cur.children[end + 1];
        return splitNode;
    }

    //index为当前keyData需要插入的下标
    //当前cur还未插入keyData，此时的count还未达到stage（count+1=stage）
    //这里需要做的是先计算好要提取出来的坐标movedIndex
    //然后查看这个index是在movedIndex的左边还是右边，然后直接添加过去
//    private void doSplitNode(BTreeNode cur, int index, KeyData keyData) {
//        //找到要分裂出去的数据坐标，阶数/2-1
//        int movedIndex = (stage >>> 1) - 1;
//        KeyData splitKey;
//        int begin;
//        if (index < movedIndex) {
//            begin = movedIndex = movedIndex - 1;
//            splitKey = cur.keys[movedIndex];
//        } else if (index == movedIndex) {
//            splitKey = keyData;
//            begin = movedIndex;
//        } else {
//            begin = movedIndex - 1;
//            splitKey = cur.keys[movedIndex];
//        }
//        //分家，分为小node与大node
//        BTreeNode small = splitNodeElement(cur, 0, movedIndex - 1);
//        BTreeNode large = splitNodeElement(cur, begin, stage - 1);
//        //父节点
//        BTreeNode parent = cur.parent;
//        // 判断父节点是否为前哨节点
//        //是的话在分裂的同时需要注意更新root的指针
//        if (parent.leaf == SENTINEL) {
//            //设置前哨节点的指针为新节点
//            BTreeNode bTreeNode = new BTreeNode(stage).setLeaf(NO_LEAF);
//            bTreeNode.keys[0] = splitKey;
//            bTreeNode.children[0] = small;
//            bTreeNode.keys[1] = new KeyData(MAX_VALUE);
//            bTreeNode.children[1] = large;
//            bTreeNode.count++;
//            parent.children[0] = bTreeNode;
//
//            bTreeNode.parent = parent;
//
//            small.parent = bTreeNode;
//            large.parent = bTreeNode;
//
//            return;
//        }
//        //父节点不是前哨节点
//        //直接插入
//        BTreeNode newParent = splitUpAddParent(splitKey, parent, small, large);
//        small.parent = newParent;
//        large.parent = newParent;
//        if (newParent.count < stage)
//            return;
//        doSplitNode(newParent);
//    }


    //分裂当前节点
    //将节点的中间位置key挪到父节点
    private void doSplitNode(BTreeNode cur) {
        //找到要分裂出去的数据坐标，阶数/2-1
        int movedIndex = (stage >>> 1) - 1;
        KeyData splitKey = cur.keys[movedIndex];
        //分家，分为小node与大node
        BTreeNode small = splitNodeElement(cur, 0, movedIndex - 1);
        BTreeNode large = splitNodeElement(cur, movedIndex + 1, stage - 1);
        //父节点
        BTreeNode parent = cur.parent;
        // 判断父节点是否为前哨节点
        //是的话在分裂的同时需要注意更新root的指针
        if (parent.leaf == SENTINEL) {
            //设置前哨节点的指针为新节点
            BTreeNode bTreeNode = new BTreeNode(stage).setLeaf(NO_LEAF);
            bTreeNode.keys[0] = splitKey;
            bTreeNode.children[0] = small;
            bTreeNode.keys[1] = new KeyData(MAX_VALUE);
            bTreeNode.children[1] = large;
            bTreeNode.count++;
            parent.children[0] = bTreeNode;

            bTreeNode.parent = parent;

            small.parent = bTreeNode;
            large.parent = bTreeNode;

            return;
        }
        //父节点不是前哨节点
        //直接插入
        BTreeNode newParent = splitUpAddParent(splitKey, parent, small, large);
        small.parent = newParent;
        large.parent = newParent;
        if (newParent.count < stage)
            return;
        doSplitNode(newParent);
    }

    private BTreeNode splitUpAddParent(KeyData keyData, BTreeNode cur, BTreeNode small, BTreeNode large) {
        int count = cur.count;
        //二分查找
        //中间位置数据>要插入的数据，只在[0,mid-1]找，否则在[mid+1,count]查找
        int mid = count >>> 1;
        int head = 0, tail = count;
        if (cur.keys[mid].key > keyData.key)
            tail = mid;
        else
            head = mid + 1;
        //二分查找，以头尾节点查看
        for (int i = head; i <= tail; i++) {
            int key = cur.keys[i].key;
            //key值小于节点时，即找到了位置，进行插入
            if (keyData.key < key) {
                //先更新当前节点的children，将large部分重新给它，然后再挪动位置
                cur.children[i] = large;
                //开始后移,连通children数组一起后移挪位置
                for (int j = count; j >= i; j--) {
                    cur.keys[j + 1] = cur.keys[j];
                    cur.children[j + 1] = cur.children[j];
                }
                cur.keys[i] = keyData;
                cur.children[i] = small;
                cur.count++;
                break;
            }
        }
        return cur;
    }

    public BTreeNode getRoot() {
        return root.children[0];
    }

    public void add(Map<String, Object> objectMap) {
        if (root == null)
            throw new NullPointerException("需要先设置根节点");
        if (objectMap == null || objectMap.isEmpty())
            throw new NullPointerException("数据不存在");
        Integer key = (Integer) objectMap.get(KEY);
        Object value = objectMap.get(VALUE);
        KeyData keyData = new KeyData(key, value);
        findCurrentLeafNode(keyData, root.children[0]);
    }

    public static void main(String[] args) {
        BTree bTree = new BTree(4);
//        int[] arr = {1,5,7,4,16,35,24,42,21,17,18};
        int[] arr = {1, 5, 7, 4, 16, 35, 24, 42, 21, 17, 18};
//        int[] arr = {1,5,7,4};
        HashMap<String, Object> map = new HashMap<>();
        for (int i : arr) {
            map.put(KEY, i);
            map.put(VALUE, new Object());
            bTree.add(map);
        }

        System.out.println(bTree.getRoot());

    }


}
