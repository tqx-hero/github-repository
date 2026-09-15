package com.tqx.fib;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: 动态规划输出斐波那契数列
 * @date 2026/4/20 10:39
 */
public class DP {
    //存储递推结果
    static List<Integer> dp = new ArrayList<Integer>();

    //输出值到x为止的斐波那契数列
    public static List<Integer> run(int x) {
        //初始化赋值
        dp.add(0);
        dp.add(1);
        //计算直到符合条件的数据
        //正推，从低向顶递推
        for (int i = 2, sum = 0; sum < x; i++)
            dp.add(sum = (dp.get(i - 2) + dp.get(i - 1)));
        return dp;
    }

    //输出直到第i项的斐波那契数列
    //数组存储上一次的结果，适合打印全部数据的情况
    public static List<Integer> runByIndex(int x) {
        dp.add(0);
        dp.add(1);
        for (var i = 2; i < x; i++) {
            dp.add(dp.get(i - 1) + dp.get(i - 2));
        }
        return dp;
    }

    //如果不要求缓存所有的记录，只需要那一个数据
    //则可以直接通过两个变量值来缓存
    public static int find(int x) {
        //用两个局部变量缓存较小数与较大数
        int min = 0, max = 1, res = 0;
        if (x == 1)
            return min;
        else if (x == 2)
            return max;
        for (var i = 2; i < x; i++) {
            res = min + max;
            min = max;
            max = res;
        }
        return res;
    }

    public static void main(String[] args) {
//        System.out.println(run(34));
//        System.out.println(runByIndex(10));
        System.out.println(get(5, 2));
    }

    /**
     * 爬楼梯
     *动态规划思想：
     *  如果求N个台阶需要多少种情况,如果k=1，也就是一次最多只能爬一层，那就是只能从N-1层往上爬一层，也就是与N-1层的情况相同，即：f(N) = f(n-1)；
     *  如果k=2，一次最多可以跨2层，到达N层就有两种情况：N-2层跨2步与N-1层跨一步。也就是这两种情况的总和：f(n) = f(n-1)+f(n-2);
     *  如果k=3，按照上述情况总结：f(n)=f(n-1)+f(n-2)+f(n-3);
     *  综上看出，最多可跨k步的状况下，f(n)=f(n-1)+f(n-2)+f(n-3)+f(n-4)+.....+f(n-k)，总共是k项n之前的数据相加
     *  这就是求解这个问题的最优子序列。
     *  那么问题就到了如何求n前面这些项的情况了，在N=k时，即最大步数与层数相同时怎么计算次数。
     *  再次从最小的情况开始看：
     *  k=1时，如果只有1层，那只有一种情况，即f(1)=1;
     *  k=2时，只有2层，就有 每次跳一步：1+1或者一次跳两步：2 这两种情况。即f(2) = 2;
     *  k=3时，组合形式为：①、一次1步；②、1次一步+1次两步；③、一次三步。第二种情况又分两种，即第一次1步第二次2步；第一次2步+第二次1步，
     *  所以总共为4种情况，f(3)=4。这里又有个规律是前两种情况是f(1)+f(2),第三种情况是有固定多出的一种，因为只能跳k个台阶并且一次跳完。
     *  所以f(3)=f(1)+f(2)+1;
     *  同理可证k=4时:f(4)=f(3)+f(2)+f(1)+1;.......
     *  上述规律表明：k个台阶，最多能跳k个台阶的情况，f(k) = f(1)+f(2)+f(3)+.....+f(k-1)+1。
     *  如果咱们额外设置一个k=0，并且令f(0)=1，那上述公式就成为了：
     *  f(k) = f(0)+f(1)+f(2)+.....+f(k-1)。
     *  当k=2时，f(2) = f(0)+f(1)就是典型的斐波那契数列：1 1 2 3 5 8 .....
     *  所以可以设置一个数组a[]，初始值a[0]=1,a[1]=1.
     *  从小到大去正着递推求f(k)的值,即求f(k) = f(0)+f(1)+f(2)+.....+f(k-1),k项之前所有数据之和。
     *  当N大于k时，比如N=k+1时，我们只需要求出这前k个区间内值之和即可，即f(k+1) = f(k)+f(k-1)+...+f(1),
     *  N=k+2时，同样是区间为k的前k个数的和：f(k+2) = f(k+1)+f(k)+f(k-1)+....+f(2)。
     *  就相当于设置的区间大小就是k，求N的值就是求N之前区间为k的那些值的和，特殊情况当N<k时，区间不得不缩小成N的大小，即k=N，此时的f(n)=f(k),
     *  也就是求前N个数据项之和。
     * @param total 总共有多少层
     * @param k     一次最多能爬多少层
     * @return
     */
    public static int get(int total, int k) {
        //0个台阶或者1个台阶的情况，都是1
        //这里的0可以看成是加数
        dp.add(1);
        dp.add(1);
        //一次最多跳k个台阶的选择次数
        for (var i = 2; i <= total; i++) {
            int temp = 0;
            //正推计算第k项的值:f(k) = f(0)+f(1)+f(2)+...+f(k-1)
            for (int j = 1; j <= k; j++) {
                //如果N>k，取N前面k个区间内数之和:f(N) = f(N-1)+f(N-2)+...+f(N-k)
                if (j <= i)
                    temp += dp.get(i - j);
                //当N小于等于k时，直接取N这个位置的数据
                else
                    break;
            }
            //计算过后保存到数组的第k个位置
            dp.add(temp);
        }
        return dp.get(total);
    }

}
