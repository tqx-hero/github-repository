package com.tqx.graph;

import java.lang.module.FindException;
import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 以十字链表为数据结构的关键路径求解。
 *
 * 名词介绍：
 *  ve：各顶点的最早开始权重。可以看成从顶点出发到各顶点最早开始的时间。如果有多条路径到达这个顶点，就需要取最大值，这样才能保证路径上所有任务都能完成。
 *  vl：各顶点的最晚开始权重，可以看成从这个点到终点需要什么时候开始才能不延误工期。如果有多条路径能到达终点，要保证这些任务都能做完，必须选取最长路径，
 *  所以就需要挑选这个最长路径，用终点最晚开始的时间来减去这个最长路径。
 *  e：弧（也叫边、任务）的最早开始时间。等于出度顶点的最早开始时间。
 *  l：弧的最晚开始时间。如果a表示从顶点v1到v2的弧，c=cost[a],v1为出度、v2为入度，则l[a]= vl[v2]-c。不能直接选择vl[v1]，因为弧尾的最晚开始时间可能不经过弧a，
 *  要l[a]的结果经过a，就必须用vl[弧头]-弧的权重。
 *  关键路径为这个路径上的边(任务)不能延误，一旦延误就会耽误整个工程的完成时间，所以这个路径上的弧最早开始时间必须等于最晚开始时间，即：e[a]=l[a]。
 *  所有满足e[k]=l[k]的弧集合就是关键路径。
 *
 *
 * 1、拓扑排序，同时更新ve。
 *  具体步骤：
 *      初始化ve[]，默认全部为0，存放所有顶点到起点的最长权重，即事件开始的最早时间
 *      收集各顶点的入度数量，放到一个集合中。
 *      找到入度为0的顶点，下标放到队列或栈Deque中。
 *      Deque不为空，弹出并根据下标i找到该顶点的出度集合，链表的话就是头结点vertex[i].firstNode，二维矩阵的话就是arr[i][]这一行。
 *      遍历出度集合，将它们所有的入度数量-1，减完以后入度数量为0的，下标入队。
 *      同时计算这个顶点j的ve，计算方法是： 如果ve[i]+cost(i,j) > ve[j]，cost(i,j)表示从i出度到j的权重。如果比之前记录的大，
 *          说明从起始点到j有更多的任务需要处理，那需要更长的时间，此时更新该权重：ve[j] = ve[i] +cost(i,j)。
 *      拓扑排序完成，ve[]也就收集完成了。
 * 2、ve中值权重最大的那个顶点即为终点end，将ve[end]值初始化到所有顶点的vl[]。
 * 3、逆拓扑排序，更新vl。
 * 具体步骤：
 *      收集各顶点的出度数量，放到集合outdegrees[]。
 *      找出出度为0的顶点，下标放入Deque。
 *      Deque不为空，持续弹出，根据下标i找出该顶点所有入度的弧集合。
 *      遍历入度集合，修改各邻居节点j的出度-1，同时判断它们的出度，为0的加入队列。
 *      遍历过程中同时计算vl[i]-cost(i,j) < vl[j],满足条件的更新：vl[j] = vl[i]-cost(i,j)。
 *      队列为空，更新完成。
 * 4、计算e[]，也就是弧的最早开始时间，直接e[a] = ve[i]，i为弧a的出度点，即弧尾
 * 5、计算l[],即弧的最晚开始时间。l[a] = vl[j]-cost(i,j)。j为入度点（弧头），i为出度点（弧尾）
 * 6、比较e[a] ==l[a]。符合条件的即为关键路径上的弧，放入结果集。
 * @date 2026/4/18 9:49
 */
public class KeyPath {

    private CrossNode[] vertex;
    private int verCount;
    private ArcNode[] arcs;
    private int arcCount;

    //数据结构为十字链表
    private static class CrossNode {
        //顶点(事件)名称
        String verName;
        //入度边数
        int indegrees;
        //出度边数
        int outdegrees;

        //入度弧链表
        ArcNode inFirst;
        //出度弧链表
        ArcNode outFirst;

        public CrossNode(String verName) {
            this.verName = verName;
        }

        @Override
        public String toString() {
            return "CrossNode{" +
                    "indegrees=" + indegrees +
                    ", verName='" + verName + '\'' +
                    ", outdegrees=" + outdegrees +
                    ", inFirst=" + inFirst +
                    ", outFirst=" + outFirst +
                    '}';
        }
    }

    @Override
    public String toString() {
        return "KeyPath{" +
                "arcCount=" + arcCount +
                ", vertex=" + Arrays.toString(vertex) +
                ", verCount=" + verCount +
                ", arcs=" + Arrays.toString(arcs) +
                '}';
    }

    //定义弧节点
    private static class ArcNode {
        //弧的名字
        String arcName;
        //入度idx，即弧头
        int inIdx;
        //出度idx，即弧尾
        int outIdx;
        //弧的权重
        double cost;
        //入度弧idx的下一个入度弧链表
        ArcNode inNext;
        //出度弧idx的下一个出度弧链表
        ArcNode outNext;

        public ArcNode(String arcName, double cost, int inIdx, int outIdx) {
            this.arcName = arcName;
            this.cost = cost;
            this.inIdx = inIdx;
            this.outIdx = outIdx;
        }

        @Override
        public String toString() {
            return "ArcNode{" +
                    "arcName='" + arcName + '\'' +
                    ", inIdx=" + inIdx +
                    ", outIdx=" + outIdx +
                    ", cost=" + cost +
                    ", inNext=" + inNext +
                    ", outNext=" + outNext +
                    '}';
        }
    }

    //初始化顶点
    public KeyPath(String[] verNames) {
        if (verNames == null || verNames.length == 0)
            throw new IllegalArgumentException("顶点不能为空");

        this.verCount = verNames.length;
        vertex = new CrossNode[verCount];
        for (int i = 0; i < verCount; i++)
            vertex[i] = new CrossNode(verNames[i]);
    }

    //加载边 [[0,1,1.0]]
    public void init(Map<String, Object[]> arcSet) {
        if (arcSet == null || arcSet.isEmpty())
            throw new IllegalArgumentException("弧不能为空");
        this.arcCount = arcSet.size();
        arcs = new ArcNode[arcCount];
        initArcs(arcSet);
    }

    private void initArcs(Map<String, Object[]> arcSet) {
        //加载边
        int idx = 0;
        for (Map.Entry<String, Object[]> e : arcSet.entrySet()) {
            String arcName = e.getKey();
            Object[] obj = e.getValue();
            //入度出度顶点的下标以及权重
            int out = (int) obj[0];
            int in = (int) obj[1];
            double cost = (double) obj[2];
            ArcNode arcNode = new ArcNode(arcName, cost, in, out);
            arcs[idx++] = arcNode;
            //添加并维护入度顶点信息
            CrossNode v = vertex[in];
            arcNode.inNext = v.inFirst;
            v.inFirst = arcNode;
            v.indegrees++;
            //添加并维护出度顶点信息
            CrossNode o = vertex[out];
            arcNode.outNext = o.outFirst;
            o.outFirst = arcNode;
            o.outdegrees++;
        }
    }

    //拓扑排序
    //同时更新入度信息与ve信息
    //返回ve的最长路径
    private double initVe(int[] indegrees, Deque<Integer> inQueue, double[] ve) {

        double max = Double.MIN_VALUE;
        int count = 0;
        //初始化ve
        while (!inQueue.isEmpty()) {
            Integer idx = inQueue.poll();
            count++;
            //找到它的邻居节点，即弧头
            //依次减去让邻居节点入度-1
            ArcNode outArc = vertex[idx].outFirst;
            while (outArc != null) {
                int inIdx = outArc.inIdx;
                //邻居的入度-1
                indegrees[inIdx]--;
                double cost = outArc.cost;
                //查看加权是否比当前记录的权重大，大则进行修改
                double v = ve[idx] + cost;
                if (v > ve[inIdx])
                    ve[inIdx] = v;
                if (ve[inIdx] > max)
                    max = ve[inIdx];
                if (indegrees[inIdx] == 0)
                    inQueue.offer(inIdx);
                outArc = outArc.outNext;
            }
        }
        if (count != verCount)
            throw new FindException("该图有环，终止查找关键路径!");
        return max;
    }

    //逆拓扑，从最末顶点开始往前遍历
    //更新它的邻居节点出度-1
    //出度为0的顶点下标入队，直到队列为空
    private void initVl(int[] outdegrees, Deque<Integer> outQueue, double[] vl) {
        while (!outQueue.isEmpty()) {
            Integer idx = outQueue.poll();
            //找到它的入度边
            ArcNode cur = vertex[idx].inFirst;
            while (cur != null) {
                //取出出度顶点下标
                int outIdx = cur.outIdx;
                outdegrees[outIdx]--;
                //计算出度点outIdx到idx的最小权重，如果比当前权重更低，更新
                double c = vl[idx] - cur.cost;
                if (c < vl[outIdx])
                    vl[outIdx] = c;
                //出度为0的顶点入队
                if (outdegrees[outIdx] == 0)
                    outQueue.offer(outIdx);
                cur = cur.inNext;
            }
        }
    }

    //获取关键路径
    public List<String[]> getKeyPath() {
        ArrayList<String[]> result = new ArrayList<>();
        //初始化顶点的入度信息与出度信息
        int[] indegrees = new int[verCount];
        int[] outdegrees = new int[verCount];
        //初始化每个顶点的ve、vl
        double[] ve = new double[verCount];
        double[] vl = new double[verCount];
        ArrayDeque<Integer> inQueue = new ArrayDeque<>();
        ArrayDeque<Integer> outQueue = new ArrayDeque<>();
        //分别将入度、出度为0的顶点入队
        for (int i = 0; i < verCount; i++) {
            indegrees[i] = vertex[i].indegrees;
            outdegrees[i] = vertex[i].outdegrees;
            if (indegrees[i] == 0)
                inQueue.offer(i);
            if (outdegrees[i] == 0)
                outQueue.offer(i);
        }
        //1、先计算每个顶点的ve(最早开始时间),vl(最晚开始时间)
        //     b、拓扑排序找出入度为0的顶点i，同时遍历它的出度，使所有邻居节点的出度-1，并更新邻居节点的ve，
        //规则是： ve[i]+ i到j的弧权重 > ve[j]，更新ve[j]
        double max = initVe(indegrees, inQueue, ve);
        Arrays.fill(vl, max);
        //逆拓扑排序计算vl，即每个顶点的最晚开始时间
        initVl(outdegrees, outQueue, vl);
        //2、计算每条弧的e(最早开始时间),l(最晚开始时间)
        for (int i = 0; i < arcCount; i++) {
            ArcNode arc = arcs[i];
            //弧的最早时间是弧尾(也就是出度顶点的)的最早开始时间
            //弧的最晚开始时间= 弧头(入度顶点)的最晚开始时间- 弧的权重
            //3、找出e=l的弧，满足条件的即为关键路径上的弧
            if (ve[arc.outIdx] == vl[arc.inIdx] - arc.cost)
                result.add(new String[]{arc.arcName, "(" + arc.cost + ")", vertex[arc.outIdx].verName + " -> " + vertex[arc.inIdx].verName});
        }
        return result;
    }

    public static void main(String[] args) {
        String[] str = {"v1", "v2", "v3", "v4", "v5", "v6"};
        KeyPath path = new KeyPath(str);
        Map<String, Object[]> map = Map.of(
                "a", new Object[]{0, 1, 2.0},
                "b", new Object[]{0, 2, 5.0},
                "c", new Object[]{1, 2, 1.0},
                "d", new Object[]{1, 3, 3.0},
                "e", new Object[]{2, 3, 3.0},
                "f", new Object[]{2, 4, 4.0},
                "g", new Object[]{2, 5, 1.0},
                "h", new Object[]{3, 4, 1.0},
                "i", new Object[]{3, 5, 4.0},
                "j", new Object[]{4, 5, 1.0}
        );
        path.init(map);
        path.getKeyPath().forEach(s -> System.out.println(Arrays.toString(s)));
    }
}
