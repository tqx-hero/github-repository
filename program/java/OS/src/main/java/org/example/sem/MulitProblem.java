package org.example.sem;

import java.util.concurrent.Semaphore;

/**
 * @author Administrator
 * @version 1.0
 * @description: 多生产者多消费者模型
 * 有一个盘子，只能放一个水果
 * 爸爸放苹果、妈妈放橘子
 * 儿子拿苹果吃，女儿拿橘子吃
 * @date 2026/5/18 17:07
 */
public class MulitProblem {

    private static final Semaphore PLANT = new Semaphore(1);
    private static final Semaphore APPLE = new Semaphore(0);
    private static final Semaphore ORANGE = new Semaphore(0);

    private static class Producer extends Thread {
        //水果类型
        private Semaphore fruit;

        public Producer(Semaphore fruit) {
            this.fruit = fruit;
        }

        @Override
        public void run() {
            while (true) {
                try {
                    //消耗一个往空盘子放置水果的许可
                    PLANT.acquire();
                    //放置相应的水果
                    fruit.release();
                    if (fruit == APPLE)
                        System.out.println("爸爸放置了一个苹果");
                    else
                        System.out.println("妈妈放置了一个橘子");
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    private static class Consumer extends Thread {
        private Semaphore fruit;

        public Consumer(Semaphore fruit) {
            this.fruit = fruit;
        }

        @Override
        public void run() {
            while (true) {
                try {
                    //先消耗拿水果的许可
                    fruit.acquire();
                    if (fruit == APPLE)
                        System.out.println("儿子拿取了一个苹果");
                    else
                        System.out.println("女儿拿取了一个橘子");
                    //在把盘子为空的状态+1，增加添加水果的许可
                    PLANT.release();
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    public static void main(String[] args) {
        new Producer(APPLE).start();
        new Producer(ORANGE).start();
        new Consumer(APPLE).start();
        new Consumer(ORANGE).start();


    }

}
