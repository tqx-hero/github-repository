package com.tqx.thread.fork;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.ForkJoinTask;
import java.util.concurrent.RecursiveTask;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/19 12:45
 */
public class ForkJoinDemo {


    static class ForkJoinTaskDemo extends RecursiveTask<Integer> {

        //设置fork阈值
        private static final long THRESHOLD = 25;

        private int start;
        private int end;

        public ForkJoinTaskDemo(int end, int start) {
            this.end = end;
            this.start = start;
        }

        @Override
        protected Integer compute() {
            int sum = 0;
            if (end - start > THRESHOLD) {
                int middle = (start + end) >> 1;
                //拆分递归
                ForkJoinTask<Integer> fork = new ForkJoinTaskDemo(middle, start);
                fork.fork();
                ForkJoinTask<Integer> fork1 = new ForkJoinTaskDemo(end, middle + 1);
                fork1.fork();
                sum = fork.join() + fork1.join();
            } else {
                for (int i = start; i <= end; i++) {
                    sum += i;
                }
            }
            return sum;
        }
    }


    public static void main(String[] args) throws ExecutionException, InterruptedException {
        ForkJoinPool pool = new ForkJoinPool();
        //逻辑处理器数量
        ForkJoinTask<Integer> submit = pool.submit(new ForkJoinTaskDemo(100, 1));
        System.out.println(submit.get());
    }
}
