package com.tqx.thread.aqs;


import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Objects;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.LockSupport;

/**
 * @author Administrator
 * @version 1.0
 * @description: 自定义AQS
 * @date 2026/3/17 11:17
 */
public class AQS {

    private AtomicReference<Node> head;
    private AtomicReference<Node> tail;

    private AtomicInteger state;

    private volatile Thread owner;

    @Override
    public String toString() {
        return "AQS{" +
                "head=" + head +
                ", tail=" + tail +
                ", state=" + state +
                ", owner=" + owner +
//                ", size=" + size +
                '}';
    }

    {
        head = new AtomicReference<>();
        tail = new AtomicReference<>();
        state = new AtomicInteger(0);
    }

    //定义一个双向链表
    class Node {
        private volatile Node next;
        private volatile Node prev;
        private volatile Thread thread;

        public Thread getThread() {
            return thread;
        }

        @Override
        public String toString() {
            return "Node{" +
                    "next=" + next +
                    ", thread=" + thread +
                    '}';
        }

        public Node() {
            this.thread = Thread.currentThread();
        }
    }

    public int getState() {
        return state.get();
    }

    public boolean setState(int expect, int state) {
        return this.state.compareAndSet(expect, state);
    }

    protected final void setExclusiveOwnerThread(Thread thread) {
        owner = thread;
    }

    protected final Thread getExclusiveOwnerThread() {
        return owner;
    }

    public boolean tryRelease() {
        if (getExclusiveOwnerThread() != Thread.currentThread()) {
            System.out.println("owner=" + getExclusiveOwnerThread() + ", 当前线程=" + Thread.currentThread().getName());
//            throw new IllegalMonitorStateException("该线程没有操作权限");
            return false;
        }
        //将queue状态改为0，owner释放,唤醒队列中的线程争锁
        if (getState() == 1) {
            setExclusiveOwnerThread(null);
        }
        state.set(0);
        return true;
    }

    public void release() {
        if (tryRelease() && head.get() != null) {
            LockSupport.unpark(head.get().thread);
        }
    }

    boolean isOperator() {
        Thread ownerThread = getExclusiveOwnerThread();
        boolean res = true;
        if (ownerThread != null)
            res = ownerThread == Thread.currentThread();
        return res;
    }

    public boolean tryLock(int ss) {
        //先判断当前队列是否有操作的线程
        if (getExclusiveOwnerThread() == null && state.compareAndSet(0, ss)) {
            setExclusiveOwnerThread(Thread.currentThread());
            return true;
        }
        return false;
    }


    protected void weekUp() {

    }

    public Node getHead() {
        return head.get();
    }


    private boolean tryLock(Node node) {
        if (tryLock(1) && getExclusiveOwnerThread() == Thread.currentThread()) {
            if (Objects.equals(node, head.get())) {
                if (node.next != null)
                    node.next.prev = null;
                head.set(node.next);
                node.next = null;
                node.thread = null;
                return true;
            }
        }
        return false;
    }

    boolean add(boolean fair) {
        //队列为空时，创建新节点
        Node node = new Node();
        boolean first = false;
        for (; ; ) {
            if (!first) {
                if (head.get() == null) {
                    if (head.compareAndSet(null, node)) {
                        tail.set(node);
                        first = true;
                    }
                    if (fair) {
                        owner = Thread.currentThread();
                    }
                } else {
                    //不为空，需要取出尾结点，CAS尾插法
                    Node tal = tail.get();
                    node.prev = tal;
                    //cas将当前node尾插到tail后
                    if (tail.compareAndSet(tal, node)) {
                        tal.next = node;
                        first = true;
                    }
                }
            } else {
                if (Objects.equals(head.get(), node)) {
                    if (tryLock(node))
                        return true;
                    continue;
                }
                LockSupport.park();
            }
        }

    }
}
