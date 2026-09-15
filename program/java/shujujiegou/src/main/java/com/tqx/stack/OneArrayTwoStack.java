package com.tqx.stack;

/**
 * @author Administrator
 * @version 1.0
 * @description: 一个数组实现两个栈
 * 这个例子是从中间往两边添加的栈；
 * 更优化的方式是从数组两边开始往中间添加，即指针均往中间靠拢
 * @date 2026/4/8 14:41
 */
public class OneArrayTwoStack {
    private static final float DEFAULT_FACTOR = 0.50f;
    private static final int STACKHEAD = 0;
    private static final int STACKTAIL = 1;
    private Object[] arr;

    private int size;
    //初始两个栈容量,容量之和为size
    private int stackHeadSize;
    private int stackTailSize;
    //两个栈内的元素数量
    private int stackHeadCount;
    private int stackTailCount;

    //栈顶指针
    private int stackHeadCur;
    private int stackTailCur;

    public OneArrayTwoStack(int size) {
        this(size, (int) (size * DEFAULT_FACTOR));
    }

    public OneArrayTwoStack(int size, int stackHeadSize) {
        this.size = size;
        this.arr = new Object[size];
        this.stackHeadSize = stackHeadSize;
        this.stackTailSize = size - stackHeadSize;
        this.stackHeadCount = 0;
        this.stackTailCount = 0;
        this.stackHeadCur = stackHeadSize;
        this.stackTailCur = stackHeadSize - 1;
    }

    //查看栈是否已满
    private boolean canSet(int stack) {
        if (stack == STACKHEAD)
            return stackHeadCount < stackHeadSize;
        else
            return stackTailCount < stackTailSize;
    }

    //查看栈是否还能扩容，即栈空间是否已满
    private boolean canResize() {
        return stackHeadCount + stackTailCount < size;
    }

    //尾栈往后移动一位，
    private void removeBackStackTail() {
//        for (int i = stackHeadSize + stackTailCount - 1; i >= stackHeadSize - stackHeadCount - 1; i--) {
        for (int i = stackTailCur; i >= stackHeadCur; i--) {
            arr[i + 1] = arr[i];
        }
        //更新两个栈的容量
        stackTailSize--;
        stackHeadSize++;
        stackHeadCur++;
        stackTailCur++;
    }

    //头栈往前挪，复制数据
    private void removeAheadStackHead() {
        for (int i = stackHeadCur; i <= stackTailCur; i++) {
            arr[i - 1] = arr[i];
        }
        stackHeadSize--;
        stackTailSize++;
        stackHeadCur--;
        stackTailCur--;
    }


    //往前面的那个栈内存放数据
    public void pushStackHead(Object value) {
        if (!canSet(STACKHEAD)) {
            //栈内已满
            //查看数组是否已满
            if (!canResize())
                throw new ArrayIndexOutOfBoundsException("数组已满");
            //移动tail栈，添加新元素
            removeBackStackTail();
        }
        arr[--stackHeadCur] = value;
        stackHeadCount++;
    }

    //往后面的栈内放入
    public void pushStackTail(Object value) {
        if (!canSet(STACKTAIL)) {
            if (!canResize())
                throw new ArrayIndexOutOfBoundsException("数组已满");
            removeAheadStackHead();
        }
        arr[++stackTailCur] = value;
        stackTailCount++;
    }

    public Object popStackHead() {
        if (stackHeadCount == 0)
            return null;
        Object o = arr[stackHeadCur++];
        stackHeadCount--;
        return o;
    }

    public Object popStackTail() {
        if (stackTailCount == 0)
            return null;
        Object o = arr[stackTailCur--];
        stackTailCount--;
        return o;
    }

    public int stackHeadSize() {
        return stackHeadCount;
    }

    public int stackTailSize() {
        return stackTailCount;
    }

    public Object peekHead() {
        if (stackHeadCount == 0)
            return null;
        return arr[stackHeadCur];
    }

    public Object peekTail() {
        if (stackTailCount == 0)
            return null;
        return arr[stackTailCur];
    }

    public static void main(String[] args) {
        OneArrayTwoStack twoStack = new OneArrayTwoStack(10);
        twoStack.pushStackHead(10);
        twoStack.pushStackHead(20);
        twoStack.pushStackHead(30);
        twoStack.pushStackHead(22);
        twoStack.pushStackHead(24);
        twoStack.pushStackHead(23);
        twoStack.pushStackHead(21);
        twoStack.pushStackTail(77);
        twoStack.pushStackTail(248);
        twoStack.pushStackTail(245);

        System.out.println(twoStack.stackHeadSize());
        System.out.println(twoStack.peekHead());
        System.out.println(twoStack.stackTailSize());
        System.out.println(twoStack.stackHeadSize());
    }

}
