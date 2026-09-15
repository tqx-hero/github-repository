package com.tqx.thread.condition;

import java.util.concurrent.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/19 11:19
 */
public class MQ {

    private SimpleBlockQueue<Object> queue;

    private Integer maxSize;

    public MQ(Integer maxSize) {
        this.maxSize = maxSize;
        this.queue = new SimpleBlockQueue<>(maxSize);
    }


    static class Producer<K> extends Thread {
        private MQ mq;

        public Producer(MQ mq) {
            this.mq = mq;
        }

        public Producer(MQ mq, K obj) {
            this.mq = mq;
            this.obj = obj;
        }

        private K obj;

        @Override
        public void run() {
            while (!Thread.interrupted())
                mq.queue.put(obj);
        }
    }

    static class Consumer implements Runnable {

        private MQ mq;

        public Consumer(MQ mq) {
            this.mq = mq;
        }


        @Override
        public void run() {
            while (!Thread.interrupted()) {
                try {
                    mq.queue.take();
                } finally {
                }
            }
        }
    }

}

class TestMQ {
    public static void main(String[] args) throws ExecutionException, InterruptedException {
        MQ mq = new MQ(10);
        ExecutorService pool = Executors.newCachedThreadPool();
        try {
            //生产者
            for (int i = 0; i < 1000; i++) {
                final int num = i;
                pool.execute(new MQ.Producer(mq, num));
            }
            //消费者
            for (int i = 0; i < 1000; i++) {
                Future res = pool.submit(new MQ.Consumer(mq));
                System.out.println("结果=" + res.get());
            }
        } catch (Exception e) {
        } finally {
            pool.shutdown();
        }

    }
}
