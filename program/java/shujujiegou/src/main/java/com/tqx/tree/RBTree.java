package com.tqx.tree;

import com.tqx.enums.ImblanceType;

import java.util.HashMap;
import java.util.Map;

import static com.tqx.enums.ImblanceType.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 红黑树实现插入与删除
 * @date 2026/4/3 23:49
 */
public class RBTree {
    //平衡树失衡类型
    //红黑树颜色： 0：红色;1、黑色
    private static final int BLACK_COLOR = 0;
    private static final int RED_COLOR = 1;
    //双黑节点
    private static final int DOUBLE_BLACK = -1;
    //左子树：0，右子树：1
    private static final int LEFT_TREE = 0;
    private static final int RIGHT_TREE = 1;
    private static final int ROOT = -1;
    //左子树,右子树
    private static final String LEFT = "left";
    private static final String RIGHT = "right";
    //定义孩子的类型是左孩子还是右孩子
    private static final String CHILD_TYPE = "childType";
    private static final String CHILD_COUNT = "count";
    //存放根节点，用于在对树操作时方便转换根节点
    private RBTreeNode rootNode;

    static class RBTreeNode {
        Integer value;
        //代表颜色 0:黑色,1、红色
        int color;
        //左孩子、右孩子、父亲节点
        RBTreeNode left, right, parent;

        public RBTreeNode(int color, Integer value, RBTreeNode parent) {
            this.color = color;
            this.value = value;
            this.parent = parent;
        }

        public RBTreeNode(int color, Integer value) {
            this.color = color;
            this.value = value;
        }

        public RBTreeNode(Integer value) {
            this.value = value;
            //默认为红色，后续再根据情况进行旋转
            this.color = RED_COLOR;
        }

        @Override
        public String toString() {
            return "RBTreeNode{" +
                    "color=" + color +
                    ", value=" + value +
                    ", left=" + left +
                    ", right=" + right +
                    '}';
        }
    }

    private void init(RBTreeNode treeNode, int value) {
        RBTreeNode currentNode = treeNode;
        while (currentNode.value != null) {
            int current = currentNode.value;
            if (current == value)
                return;
            if (value < current)
                currentNode = currentNode.left;
            else
                currentNode = currentNode.right;
        }
        //新建并插入节点
        RBTreeNode parentNode = currentNode.parent;
        RBTreeNode newNode = new RBTreeNode(RED_COLOR, value, parentNode);
        if (parentNode.value > value)
            parentNode.left = newNode;
        else
            parentNode.right = newNode;

        newNode.left = currentNode;
        newNode.right = new RBTreeNode(BLACK_COLOR, null, newNode);
        currentNode.parent = newNode;

        //解决添加时可能出现的红红冲突
        resolveRedConflict(newNode);
    }

    private int leftOrRightTree(RBTreeNode currentNode) {
        if (currentNode == null)
            throw new IllegalArgumentException("节点不能为空");
        if (rootNode == currentNode)
            return ROOT;
        return currentNode.parent.left == currentNode ? LEFT_TREE : RIGHT_TREE;
    }

    private void resolveRedConflict(RBTreeNode currentNode) {
        RBTreeNode resolveNode = currentNode;
        //查看父节点的颜色是否为红色，如果是红色就要处理，黑色直接结束
        while (resolveNode.parent.color != BLACK_COLOR) {
            RBTreeNode parentNode = resolveNode.parent;
            //如果为红色，需要查看叔父颜色
            RBTreeNode uncleNode = getUncleNode(resolveNode);
            RBTreeNode grandNode = parentNode.parent;
            int uncleColor = uncleNode.color;
            //叔父颜色红色的话，需要把叔父爷三个节点都变色。
            // 变色完成后，需要查看爷节点是否为根节点，是的话需要再次变色，不是则不需要变色
            if (uncleColor == RED_COLOR) {
                uncleNode.color = BLACK_COLOR;
                parentNode.color = BLACK_COLOR;
                grandNode.color = RED_COLOR;
                //爷节点是根节点，那么需要将颜色再次变为黑色
                if (this.rootNode == grandNode)
                    grandNode.color = BLACK_COLOR;
                else
                    //如果不是根节点，因为爷爷已经成为红色，需要递归查看其父节点颜色，再次调用该方法，直到满足不红红为止
                    resolveNode = grandNode;
            } else {
                //如果颜色为黑色，那情况就复杂了，需要旋转并且按照情况进行讨论
                //判断失衡类型 ： LL /RR/LR/RL,翻转节点
                reverseNode(getImBlanceType(parentNode, leftOrRightTree(resolveNode)), grandNode, parentNode, uncleNode, resolveNode);
            }
        }

    }

    //LL型，或RR型，父升爷，爷变叔
    private void reverseLlAndRr(ImblanceType imBlanceType, RBTreeNode... nodes) {
        RBTreeNode grandNode = nodes[0];
        RBTreeNode parentNode = nodes[1];
        if (imBlanceType.equals(IMBALANCE_LL)) {
            RBTreeNode right = parentNode.right;
            parentNode.right = grandNode;
            grandNode.left = right;
            right.parent = grandNode;
        } else if (imBlanceType.equals(IMBALANCE_RR)) {
            RBTreeNode left = parentNode.left;
            parentNode.left = grandNode;
            grandNode.right = left;
            left.parent = grandNode;
        }
        //变换颜色
        parentNode.color = BLACK_COLOR;
        grandNode.color = RED_COLOR;
        //判断爷节点是否为根节点,是的话，把根节点指针指向父节点
        if (rootNode == grandNode) {
            grandNode.parent = parentNode;
            rootNode = parentNode;
            return;
        }
        //不是根节点，找到爷节点的父节点，更新它的指针
        RBTreeNode gParent = grandNode.parent;
        parentNode.parent = gParent;
        grandNode.parent = parentNode;
        int le = gParent.left == grandNode ? LEFT_TREE : RIGHT_TREE;
        if (le == LEFT_TREE)
            gParent.left = parentNode;
        else
            gParent.right = parentNode;
    }

    private void reverseLrAndRl(ImblanceType imBlanceType, RBTreeNode... nodes) {
        RBTreeNode grandNode = nodes[0];
        RBTreeNode parentNode = nodes[1];
        RBTreeNode currentNode = nodes[3];
        RBTreeNode left = currentNode.left;
        RBTreeNode right = currentNode.right;
        //指针维护
        if (imBlanceType.equals(IMBALANCE_LR)) {
            currentNode.right = grandNode;
            currentNode.left = parentNode;
            parentNode.parent = currentNode;
            parentNode.right = left;
            left.parent = parentNode;
            grandNode.left = right;
            right.parent = grandNode;
        } else if (imBlanceType.equals(IMBALANCE_RL)) {
            currentNode.left = grandNode;
            currentNode.right = parentNode;
            parentNode.parent = currentNode;
            parentNode.left = right;
            grandNode.right = left;
            left.parent = grandNode;
            right.parent = parentNode;
        }

        //变色
        currentNode.color = BLACK_COLOR;
        grandNode.color = RED_COLOR;

        //判断爷节点是否为根节点,是的话，把根节点指针指向父节点
        if (rootNode == grandNode) {
            grandNode.parent = currentNode;
            rootNode = currentNode;
            return;
        }
        //不是根节点，找到爷节点的父节点，更新它的指针
        RBTreeNode gParent = grandNode.parent;
        currentNode.parent = gParent;
        grandNode.parent = currentNode;
        int le = gParent.left == grandNode ? LEFT_TREE : RIGHT_TREE;
        if (le == LEFT_TREE)
            gParent.left = currentNode;
        else
            gParent.right = currentNode;

    }

    private void reverseNode(ImblanceType balanceType, RBTreeNode... nodes) {
        switch (balanceType) {
            case IMBALANCE_LL -> reverseLlAndRr(balanceType, nodes);
            case IMBALANCE_RR -> reverseLlAndRr(balanceType, nodes);
            case IMBALANCE_LR -> reverseLrAndRl(balanceType, nodes);
            case IMBALANCE_RL -> reverseLrAndRl(balanceType, nodes);
        }
    }

    private ImblanceType getImBlanceType(RBTreeNode parentNode, int insertPosition) {
        RBTreeNode grandNode = parentNode.parent;
        //LL
        if (grandNode.left == parentNode && insertPosition == LEFT_TREE)
            return IMBALANCE_LL;
            //LR
        else if (grandNode.left == parentNode && insertPosition == RIGHT_TREE)
            return IMBALANCE_LR;
            //RL
        else if (grandNode.right == parentNode && insertPosition == LEFT_TREE)
            return IMBALANCE_RL;
            //RR
        else if (grandNode.right == parentNode && insertPosition == RIGHT_TREE)
            return IMBALANCE_RR;
        return null;
    }

    RBTreeNode getUncleNode(RBTreeNode newNode) {
        RBTreeNode parent = newNode.parent;
        RBTreeNode grandFatherNode = parent.parent;
        return grandFatherNode.left == parent ? grandFatherNode.right : grandFatherNode.left;
    }

    void initRootNode(int rootNum) {
        this.rootNode = new RBTreeNode(BLACK_COLOR, rootNum);
        rootNode.left = new RBTreeNode(BLACK_COLOR, null, rootNode);
        rootNode.right = new RBTreeNode(BLACK_COLOR, null, rootNode);
    }

    public RBTreeNode create(int[] arr) {
        if (arr == null || arr.length == 0)
            return null;
        //构建初始根节点
        initRootNode(arr[0]);
        for (int i = 1; i < arr.length; i++) {
            init(rootNode, arr[i]);
        }
        return rootNode;
    }

    //查询当前节点有几个孩子,不包括null节点
    private Map<String, Object> getChildNum(RBTreeNode treeNode) {
        HashMap<String, Object> map = new HashMap<>();
        int num = 0;
        String str = null;
        if (treeNode.left.value != null) {
            map.put(LEFT, treeNode.left);
            str = LEFT;
            num++;
        }
        if (treeNode.right.value != null) {
            str = RIGHT;
            map.put(RIGHT, treeNode.right);
            num++;
        }
        map.put(CHILD_COUNT, num);
        if (num == 1)
            map.put(CHILD_TYPE, str);
        return map;
    }

    //获取后继节点
    private RBTreeNode getAfterNode(RBTreeNode currentNode) {
        RBTreeNode after = currentNode.right;
        while (after.value != null) {
            if (after.left.value == null)
                return after;
            after = after.left;
        }
        return null;
    }

    private void deleteNode(RBTreeNode currentNode) {
        //判断节点有几个孩子
        //只有两种情况：1、没有孩子；2、只有一个孩子
        Map<String, Object> map = getChildNum(currentNode);
        Integer chindNum = (Integer) map.get(CHILD_COUNT);
        //判断当前节点是父节点的左孩子还是右孩子

        //只有一个的情况，该节点必为黑色节点
        //因为红色节点不相邻，要么有两个黑孩子，要么没有孩子，不会只有一个黑孩子的情况，否则会破坏黑路同规则
        //这种情况删除并将它的孩子节点移动到该位置，同时变黑色即可
        if (chindNum == 1) {
            RBTreeNode child = map.get(LEFT) == null ? (RBTreeNode) map.get(RIGHT) : (RBTreeNode) map.get(LEFT);
            int leftOrRight = leftOrRightTree(child);
            currentNode.value = child.value;
            child.left = null;
            child.right = null;
            child.parent = null;
            if (leftOrRight == LEFT_TREE)
                currentNode.left = new RBTreeNode(BLACK_COLOR, null, currentNode);
            else
                currentNode.right = new RBTreeNode(BLACK_COLOR, null, currentNode);
            return;
        }

        //如果没有孩子，看一下节点颜色
        int l = leftOrRightTree(currentNode);
        //如果是红色，直接删除即可
        if (currentNode.color == RED_COLOR) {
            RBTreeNode parent = currentNode.parent;
            if (l == LEFT_TREE)
                parent.left = new RBTreeNode(BLACK_COLOR, null, currentNode);
            else
                parent.right = new RBTreeNode(BLACK_COLOR, null, currentNode);
            currentNode.parent = null;
            return;
        }
        // todo 如果颜色为黑色，那就需要分情况看
        //设置当前节点为双黑节点 color= -1
        currentNode.color = DOUBLE_BLACK;
        deleteEleWithOutChildren(currentNode);

    }

    //获取兄弟节点
    private RBTreeNode getBroterNode(RBTreeNode currentNode, int l) {
        RBTreeNode parent = currentNode.parent;
        //左子树，兄弟为右子树
        if (l == LEFT_TREE)
            return parent.right;
        else
            return parent.left;
    }

    //兄弟节点为红色，左旋或者右旋
    private void routeLeftAndRight(int position, RBTreeNode... nodes) {
        RBTreeNode parent = nodes[0];
        boolean isRoot = true;
        RBTreeNode grandNode = parent.parent;
        int where = -1;
        //父节点是爷节点左子树还是右子树
        if (rootNode != parent) {
            isRoot = false;
            where = leftOrRightTree(parent);
        }
        RBTreeNode broterNode = nodes[2];

        //将父与兄弟节点颜色改变
        parent.color = RED_COLOR;
        broterNode.color = BLACK_COLOR;
        //在把父节点左旋，让兄弟节点成为父节点的父节点，即双黑节点的爷节点
        parent.parent = broterNode;
        broterNode.parent = grandNode;
        //当前节点在父节点左子树，左旋
        if (position == LEFT_TREE) {
            RBTreeNode left = broterNode.left;
            parent.right = left;
            broterNode.left = parent;
            left.parent = parent;

//            left.color = RED_COLOR;
        }
        //在右子树，需要右旋
        else {
            RBTreeNode right = broterNode.right;
            parent.left = right;
            broterNode.right = parent;
            right.parent = parent;
//            right.color = RED_COLOR;
        }
//        parent.color = BLACK_COLOR;
        //如果原父节点为根节点，更新根节点
        if (isRoot) {
            rootNode = broterNode;
            return;
        }
        //原兄弟节点连接上原爷节点，左子树或者右子树
        if (where == LEFT_TREE)
            grandNode.left = broterNode;
        else
            grandNode.right = broterNode;
    }


    //颜色为黑色节点的删除
    //此时节点设置为双黑节点
    private void deleteEleWithOutChildren(RBTreeNode doubleBlackNode) {
        //记录下要删除的节点，最后统一删除
        RBTreeNode deletedNode = doubleBlackNode;
        while (doubleBlackNode.color != BLACK_COLOR) {
            //判断双黑节点是否为根节点,是则直接改变颜色即可
            if (rootNode == doubleBlackNode) {
                doubleBlackNode.color = BLACK_COLOR;
                break;
            }
            int l = leftOrRightTree(deletedNode);
            RBTreeNode parentNode = doubleBlackNode.parent;
            //获取兄弟节点
            RBTreeNode broterNode = getBroterNode(doubleBlackNode, l);
            int brColor = broterNode.color;
            //兄弟颜色为红，将父与兄弟颜色互换，父旋转,兄弟的左孩子成为新的兄弟，再次迭代查看新兄弟的
            //颜色以及孩子情况
            if (brColor == RED_COLOR) {
                routeLeftAndRight(l, parentNode, doubleBlackNode, broterNode);
                continue;
            }
            //兄弟节点为黑，需要分情况讨论
            //获取兄弟有几个孩子
            Map<String, Object> childMap = getChildNum(broterNode);
            Integer childrenNum = (Integer) childMap.get(CHILD_COUNT);
            //是红孩子的情况
            boolean only = false;
            //查看左孩子节点是否为红色
            if ((only = childrenNum == 1) ||
                    (childrenNum == 2 &&
                            (broterNode.left.color == RED_COLOR ||
                                    broterNode.right.color == RED_COLOR))) {
                ImblanceType routeType;
                //只有一个孩子,需要判断孩子是LL/RR还是RL/LR
                if (only) {
                    String childType = (String) childMap.get(CHILD_TYPE);
                    routeType = judgeRouteType(childType, broterNode);
                } else {
                    //有两个孩子的情况,先看红孩子是哪个树，然后判断是LL/RR型还是LR/RL
                    // 直接按照LL与RR情况处理
                    int broDirection = leftOrRightTree(broterNode);
                    int leftColor = broterNode.left.color;
                    int rightColor = broterNode.right.color;
                    //todo需要查看两个孩子是红还是黑
                    routeType = judgeRouteTypeByColor(broDirection, leftColor, rightColor);
                }
                //LL/RR统一处理，LR/RL统一处理
                if (routeType.equals(IMBALANCE_LL) || routeType.equals(IMBALANCE_RR)) {
                    deleteTypeRRAndLL(routeType, parentNode, doubleBlackNode, broterNode);
                } else {
                    deleteTypeLRAndRL(routeType, parentNode, doubleBlackNode, broterNode);
                }
                if (deletedNode != doubleBlackNode)
                    doubleBlackNode.color -= DOUBLE_BLACK;
                break;
            }
            //没有确定值的孩子，null值不算
            //1、先把兄弟节点变成红，然后将双黑上推给父节点
            broterNode.color = RED_COLOR;
            doubleBlackNode.color -= DOUBLE_BLACK;
            parentNode.color += DOUBLE_BLACK;
            doubleBlackNode = parentNode;
            //父节点不是红色的，则需要迭代查看其兄弟节点以及爷节点
            //todo 需要将该方法改为迭代,修改删除逻辑,先对这个要删除的节点增加标记，等到红黑树平衡以后删除,由于是叶子结点，所以不受影响
        }
        //删除节点
        deletedNodeRemove(deletedNode);
    }


    private ImblanceType judgeRouteTypeByColor(int broDirection, int leftColor, int rightColor) {
        if (broDirection == LEFT_TREE) {
            if (leftColor == RED_COLOR)
                return IMBALANCE_LL;
            if (rightColor == RED_COLOR)
                return IMBALANCE_LR;
        } else {
            if (rightColor == RED_COLOR)
                return IMBALANCE_RR;
            if (leftColor == RED_COLOR)
                return IMBALANCE_RL;
        }
        return null;
    }

    private void deletedNodeRemove(RBTreeNode deletedNode) {
        if (rootNode == deletedNode) {
            rootNode = null;
            return;
        }
        int l = leftOrRightTree(deletedNode);
        RBTreeNode parent = deletedNode.parent;
        deletedNode.parent = null;
        if (l == LEFT_TREE)
            parent.left = new RBTreeNode(BLACK_COLOR, null, parent);
        else
            parent.right = new RBTreeNode(BLACK_COLOR, null, parent);
    }

    private void deleteTypeRRAndLL(ImblanceType routeType, RBTreeNode... nodes) {
        RBTreeNode parentNode = nodes[0];
        RBTreeNode broterNode = nodes[2];
        RBTreeNode grandNode = parentNode.parent;
        RBTreeNode left = broterNode.left;
        //有的话需要添加过去
        RBTreeNode right = broterNode.right;
        int where = -1;
        boolean isRoot = true;

        //父节点是爷节点左子树还是右子树
        if (rootNode != parentNode) {
            isRoot = false;
            where = leftOrRightTree(parentNode);
        }
        if (routeType.equals(IMBALANCE_LL)) {
            left.color = broterNode.color;
            //更新指针
            broterNode.right = parentNode;
            parentNode.left = right;
            right.parent = parentNode;
        } else if (routeType.equals(IMBALANCE_RR)) {
            right.color = broterNode.color;
            broterNode.left = parentNode;
            parentNode.right = left;
            left.parent = parentNode;
        }
        broterNode.color = parentNode.color;
        parentNode.color = BLACK_COLOR;
        parentNode.parent = broterNode;
        broterNode.parent = grandNode;

        //如果原父节点为根节点，更新根节点
        if (isRoot) {
            rootNode = broterNode;
            return;
        }
        //原兄弟节点连接上原爷节点，左子树或者右子树
        if (where == LEFT_TREE)
            grandNode.left = broterNode;
        else
            grandNode.right = broterNode;
    }

    private void deleteTypeLRAndRL(ImblanceType routeType, RBTreeNode... nodes) {
        RBTreeNode parentNode = nodes[0];
        RBTreeNode broterNode = nodes[2];
        RBTreeNode grandNode = parentNode.parent;
        RBTreeNode left = broterNode.left;
        //有的话需要添加过去
        RBTreeNode right = broterNode.right;
        int where = -1;
        boolean isRoot = true;
        boolean isRL = true;
        //父节点是爷节点左子树还是右子树
        if (rootNode != parentNode) {
            isRoot = false;
            where = leftOrRightTree(parentNode);
        }
        if (routeType.equals(IMBALANCE_LR)) {
            right.color = parentNode.color;
            broterNode.right = new RBTreeNode(BLACK_COLOR, null, broterNode);
            right.parent = grandNode;
            right.left = broterNode;
            right.right = parentNode;
            broterNode.parent = right;
            parentNode.parent = right;
            parentNode.left = new RBTreeNode(BLACK_COLOR, null, parentNode);
            isRL = false;
            //更新指针
        } else if (routeType.equals(IMBALANCE_RL)) {
            left.color = parentNode.color;
            broterNode.left = new RBTreeNode(BLACK_COLOR, null, broterNode);
            left.parent = grandNode;
            left.left = parentNode;
            left.right = broterNode;
            broterNode.parent = left;
            parentNode.parent = left;
            parentNode.right = new RBTreeNode(BLACK_COLOR, null, parentNode);
        }
        parentNode.color = BLACK_COLOR;
        //如果原父节点为根节点，更新根节点
        if (isRoot) {
            if (isRL)
                rootNode = left;
            else
                rootNode = right;
            return;
        }
        //原兄弟节点连接上原爷节点，左子树或者右子树
        if (where == LEFT_TREE)
            grandNode.left = left;
        else
            grandNode.right = right;
    }

    private ImblanceType judgeRouteType(String childType, RBTreeNode parentNode) {
        int position = childType.equals(LEFT) ? LEFT_TREE : RIGHT_TREE;
        return getImBlanceType(parentNode, position);
    }

    public RBTreeNode deleteElement(int value) {

        RBTreeNode currentNode = rootNode;
        //先找到删除的节点
        while (currentNode.value != null) {
            Integer v = currentNode.value;

            if (v == value) {
                //找到后需要按情况处理、
                Map<String, Object> childNum = getChildNum(currentNode);
                //如果是有两个孩子的情况，找到它的后继节点，将后继节点数据复制到这个节点，然后删除后继节点即可
                //其余情况（1个孩子或者没有孩子）都可以与后继节点统一处理
                if ((Integer) childNum.get(CHILD_COUNT) == 2) {
                    //找到后继节点，将数据复制到当前节点，删除后继节点
                    RBTreeNode afterNode = getAfterNode(currentNode);
                    currentNode.value = afterNode.value;
                    deleteNode(afterNode);
                } else
                    deleteNode(currentNode);
                break;
            } else if (value < v)
                currentNode = currentNode.left;
            else
                currentNode = currentNode.right;
        }

        return rootNode;
    }

    public static void main(String[] args) {
//        int[] arr = {17, 18, 23, 34, 27, 15, 9, 6, 8, 5, 25};
        int[] arr = {15, 9, 18, 6, 13, 17, 27, 23, 34, 25, 37};
        //{15,9,18,6,13,17,27,23,34,25,37};
        RBTree rbTree = new RBTree();
        System.out.println(rbTree.create(arr));

        //根节点删除
//        System.out.println(rbTree.deleteElement(15));

        //只有一个孩子节点
        //左孩子
//        System.out.println(rbTree.deleteElement(6));
        //右孩子
//        System.out.println(rbTree.deleteElement(23));


//        //2个孩子节点
        //右子树的红节点
//        System.out.println(rbTree.deleteElement(27));
        //右子树黑节点
//        System.out.println(rbTree.deleteElement(18));
        //左子树黑节点
//        System.out.println(rbTree.deleteElement(8));

        //没孩子的，兄弟没孩子，父红
//        rbTree.deleteElement(25);
//        System.out.println(rbTree.deleteElement(23));
        //兄弟没孩子，父黑
//        rbTree.deleteElement(5);
//        System.out.println(rbTree.deleteElement(6));


    }

}
