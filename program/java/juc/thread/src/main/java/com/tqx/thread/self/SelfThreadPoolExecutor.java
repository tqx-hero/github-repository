package com.tqx.thread.self;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/15 10:21
 */
public class SelfThreadPoolExecutor {

    private Integer corePoolSize;
    private Integer maximumPoolSize;
    private BlockingQueue<Runnable> queue;
    private ThreadFactory threadFactory;

    private static List<WorkerThread> threadList;

    private static volatile boolean shutDown = false;

    //当前的线程数量
    private static volatile AtomicInteger currentThreadNum;


    public SelfThreadPoolExecutor(Integer corePoolSize, Integer maximumPoolSize, BlockingQueue<Runnable> queue, ThreadFactory threadFactory) {
        this.corePoolSize = corePoolSize;
        this.maximumPoolSize = maximumPoolSize;
        this.queue = queue;
        this.threadFactory = threadFactory;
        currentThreadNum = new AtomicInteger(0);
        threadList = new ArrayList<>();
    }


    class WorkerThread implements Runnable {

        //绑定这个worker的启动线程,线程由线程工厂统一创建
        private Thread thread;

        //这个worker的任务
        private Runnable mission;


        public WorkerThread(Runnable mission) {
            this.mission = mission;
            this.thread = threadFactory.newThread(this);
        }

        @Override
        public void run() {

            if (shutDown) {
                return;
            }

            //如果任务不为空，直接启动任务
            Runnable task = mission;
            while (true) {
                if (task != null) {
                    task.run();
                    mission = null;
                }
                //销毁方法，队列为空时，销毁多余的线程，保留核心线程数
                if (queue.isEmpty() && currentThreadNum.get() > corePoolSize) {
                    synchronized (threadList) {
                        if (currentThreadNum.get() > corePoolSize) {
                            threadList.remove(this);
                            currentThreadNum.incrementAndGet();
                            break;
                        }
                    }
                }

                //循环去阻塞队列中取任务
                try {
                    task = queue.take();
                    mission = task;
                } catch (InterruptedException e) {
                    //打断的线程在推出前查看线程池内的线程数量，不够核心线程数的补齐
                    if (!shutDown) {
                        synchronized (threadList) {
                            if (currentThreadNum.get() <= corePoolSize) {
                                threadList.remove(this);
                                threadList.add(addWorker(task));
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

    public void shutDown() {
        shutDown = true;
        for (WorkerThread workerThread : threadList) {
            workerThread.thread.interrupt();
        }
        currentThreadNum = null;
    }

    /**
     * 获取当前线程池内线程数量
     *
     * @return
     */
    public static Integer getThreadListNum() {
        return threadList.size();
    }

    /**
     * 获取当前线程池内线程数量
     *
     * @return
     */
    public static Integer getThreadNum() {
        return currentThreadNum.get();
    }

    private WorkerThread addWorker(Runnable mission) {
        WorkerThread worker = new WorkerThread(mission);
        synchronized (threadList) {
            threadList.add(worker);
        }
        return worker;
    }

    private void enableWorker(Runnable mission) {
        addWorker(mission).thread.start();
    }

    public void execute(Runnable runnable) {
        //1、判断核心线程数是否已超过
        if (currentThreadNum.get() < corePoolSize) {
            //小于则创建线程，执行任务
            enableWorker(runnable);
            currentThreadNum.incrementAndGet();
        } else {
            //查看队列是否已满
            if (!queue.offer(runnable)) {
                //队列已满，查看有没有到达最大线程数
                if (currentThreadNum.get() < maximumPoolSize) {
                    enableWorker(runnable);
                    currentThreadNum.incrementAndGet();
                } else {
                    //都满了，抛异常
                    System.out.println("任务已满，已丢掉 : " + runnable.toString());
                }
            }
        }
    }

//    public void shutdown() {
//
//    }

}
