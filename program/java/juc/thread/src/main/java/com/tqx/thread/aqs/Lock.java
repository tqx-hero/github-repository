package com.tqx.thread.aqs;

import java.util.Objects;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.LockSupport;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/17 13:28
 */
public class Lock {

    private volatile AQS queue;

    private boolean fair;


    public AQS getQueue() {
        return queue;
    }

    public Lock() {
        queue = new UnFair();
    }

    public Lock(boolean fair) {
        this.fair = fair;
        queue = fair ? new Fair() : new UnFair();
    }

    class UnFair extends AQS {

    }

    class Fair extends AQS {

        @Override
        public boolean tryLock(int ss) {
            //先判断当前队列是否有操作的线程
            Thread t = Thread.currentThread();
//            if (queue.getSize() == 0) {
//                return true;
//            }
            if (getState() == 0) {
                if (getExclusiveOwnerThread() == t && setState(0, 1)) {
                    setExclusiveOwnerThread(t);
                    return true;
                }
            }
            return false;
        }
    }

    void lock() {
        if (fair) {
            queue.add(true);
            queue.tryLock(1);
        } else {
            int state = queue.getState();
            //state=0 则可以获取锁，修改queue状态
            if (state == 0) {
//            boolean b = queue.tryLock(1);
                //成功，获取锁，不成功则继续锁
                if (!queue.tryLock(1)) {
                    queue.add(false);
                }
            } else {
                //state=1 不能获取锁，添加到AQS队列
                queue.add(false);
            }
        }
    }

    void unlock() {
        queue.release();
    }

}
