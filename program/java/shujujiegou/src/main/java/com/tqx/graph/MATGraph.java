package com.tqx.graph;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 多重邻接表
 * @date 2026/4/18 14:24
 */
public class MATGraph {

    protected MultiNode[] vertex;
    protected int verCount;
    protected EdgeNode[] edges;
    protected int edgeCount;

    //多重邻接表
    protected static class MultiNode {
        //顶点信息
        String verName;
        EdgeNode firstEdge;

        public MultiNode(String verName) {
            this.verName = verName;
        }

        @Override
        public String toString() {
            return "MultiNode{" +
                    "firstEdge=" + firstEdge +
                    ", verName='" + verName + '\'' +
                    '}';
        }
    }

    //边信息
    protected static class EdgeNode implements Comparable<EdgeNode> {
        //边的下标
        int idx;
        //边名
        String edgeName;
        //边的两端顶点
        int iIdx;
        int jIdx;
        //边的权重
        double cost;
        //两端顶点i，j的各自下一条边
        EdgeNode iNext;
        EdgeNode jNext;

        public EdgeNode(double cost, String edgeName, int iIdx, EdgeNode iNext, int jIdx, EdgeNode jNext, int idx) {
            this.cost = cost;
            this.edgeName = edgeName;
            this.iIdx = iIdx;
            this.iNext = iNext;
            this.jIdx = jIdx;
            this.jNext = jNext;
            this.idx = idx;
        }

        @Override
        public String toString() {
            return "EdgeNode{" +
                    "cost=" + cost +
                    ", idx=" + idx +
                    ", edgeName='" + edgeName + '\'' +
                    ", iIdx=" + iIdx +
                    ", jIdx=" + jIdx +
                    ", iNext=" + iNext +
                    ", jNext=" + jNext +
                    '}';
        }

        @Override
        public int compareTo(EdgeNode o) {
            return Double.compare(this.cost, o.cost);
        }
    }

    //存放到堆内的数据，
    // 用于堆比较
    protected static class CompareNode implements Comparable<CompareNode> {
        int index;
        double cost;

        public CompareNode(double cost, int index) {
            this.cost = cost;
            this.index = index;
        }

        @Override
        public int compareTo(CompareNode o) {
            return Double.compare(this.cost, o.cost);
        }
    }

    @Override
    public String toString() {
        return "PrimAlgorithm{" +
                "edgeCount=" + edgeCount +
                ", vertex=" + Arrays.toString(vertex) +
                ", verCount=" + verCount +
                ", edges=" + Arrays.toString(edges) +
                '}';
    }

    public MATGraph(String[] ver) {
        if (ver == null || ver.length == 0)
            throw new IllegalArgumentException("顶点不能为空");
        verCount = ver.length;
        vertex = new MultiNode[verCount];
        for (int i = 0; i < verCount; i++)
            vertex[i] = new MultiNode(ver[i]);
    }

    protected void initEdges(Map<String, Object[]> edge) {
        int i = 0;
        for (Map.Entry<String, Object[]> e : edge.entrySet()) {
            String name = e.getKey();
            Object[] v = e.getValue();
            int iIdx = (int) v[0];
            int jIdx = (int) v[1];
            double cost = (double) v[2];
            //创建边
            vertex[iIdx].firstEdge = vertex[jIdx].firstEdge = edges[i] =
                    new EdgeNode(cost, name, iIdx, vertex[iIdx].firstEdge, jIdx, vertex[jIdx].firstEdge, i++);
        }
    }

    //初始化边
    public void init(Map<String, Object[]> edge) {
        if (edge == null || edge.isEmpty())
            throw new IllegalArgumentException("边不能为空");
        edgeCount = edge.size();
        edges = new EdgeNode[edgeCount];
        initEdges(edge);
    }

    //图demo
    public static MATGraph build(MATGraph graph, Map<String, Object[]> map) {
        graph.init(map);
        return graph;
    }

    protected void calculate(double[] costs, boolean[] visited, int[] parent, int x) {
        //堆内传入的元素不要以全局对象作为比较器参照
        //因为全局对象如果发生变动
        //堆无法动态感知外部数据的变动来动态调整堆结构
        //一旦添加新的引用比如下标，在进行比较时如果parent整好等于之前重复的旧下标，
        //比较器同时比较这两个下标所在对象，如果发现相同，会停止上浮，导致排列出现错误

        PriorityQueue<CompareNode> minHeap = new PriorityQueue<>();
        minHeap.offer(new CompareNode(costs[x], x));
        int count = 0;
        while (!minHeap.isEmpty()) {
            int idx = minHeap.poll().index;
            if (visited[idx])
                continue;
            visited[idx] = true;
            if (++count == verCount)
                break;
            EdgeNode edge = vertex[idx].firstEdge;
            while (edge != null) {
                //拿到另一个顶点下标,计算起点到顶点的权重和，小于的costs[]数组的数据，则进行更新
                int o;
                boolean i = true;
                if (edge.iIdx == idx)
                    o = edge.jIdx;
                else {
                    o = edge.iIdx;
                    i = false;
                }
                double c = edge.cost;
                if (!visited[o] && c < costs[o]) {
                    //更新costs数组与o顶点的上级节点
                    costs[o] = c;
                    parent[o] = idx;
                    minHeap.offer(new CompareNode(costs[o], o));
                }
                edge = i ? edge.iNext : edge.jNext;
            }
        }
    }


    public List<String> buildPrimTree(int x) {
        List<String> result = new ArrayList<>();
        double[] costs = new double[verCount];
        boolean[] visited = new boolean[verCount];
        //表示顶点的上级节点
        int[] parent = new int[verCount];
        Arrays.fill(costs, Double.MAX_VALUE);
        Arrays.fill(parent, -1);
        costs[x] = 0;
        calculate(costs, visited, parent, x);
        //根据以上信息统计顶点与边
        for (int i = 0; i < verCount; i++) {
            int p = parent[i];
            if (p != -1) {
                result.add(vertex[p].verName +
                        " - " +
                        vertex[i].verName +
                        "(" +
                        costs[i] +
                        ")");
            }
        }
        return result;
    }

    //交并集之find
    protected int find(int x, int[] parent) {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x], parent);
    }

    //克鲁斯卡尔算法最小生成树
    public List<String> buildKruskalTree() {
        List<String> result = new ArrayList<>();
        int[] parent = new int[verCount];
        PriorityQueue<EdgeNode> minHeap = new PriorityQueue<>();
        //加载所有边到小顶堆
        for (EdgeNode edge : edges)
            minHeap.offer(edge);
        //加载所有顶点的初始祖宗是它自己
        for (int i = 0; i < verCount; i++)
            parent[i] = i;
        while (!minHeap.isEmpty()) {
            EdgeNode e = minHeap.poll();
            int iIdx = e.iIdx;
            int jIdx = e.jIdx;
            //需要查看这两个顶点连不连通
            //连通则不能要
            int fx = find(iIdx, parent);
            int fy = find(jIdx, parent);
            //两个顶点祖宗不同，说明它们不连通
            //将该条边加入结果集，并更新他们的祖宗为一个
            if (fx != fy) {
                parent[fx] = fy;
                //加入结果集
                result.add(
                        vertex[iIdx].verName
                                + " - "
                                + vertex[jIdx].verName
                                + "("
                                + e.cost
                                + ")"
                );
                if (result.size() == verCount - 1)
                    break;
            }
        }
        return result;
    }

    //从x下标开始深度优先
    public void dfs(int x) {
        boolean[] visited = new boolean[verCount];
        dfs(x, vertex[x].firstEdge, visited);
    }

    //广度优先
//    public void bfs(int x) {
//        boolean[] visited = new boolean[verCount];
//        bfs(x, vertex[x].firstEdge, visited);
//    }
    //广度优先
    public void bfsByQueue(int x) {
        ArrayDeque<Integer> queue = new ArrayDeque<>();
        boolean[] visited = new boolean[verCount];
        queue.offer(x);
        while (!queue.isEmpty()) {
            int idx = queue.poll();
            if (visited[idx])
                continue;
            MultiNode node = vertex[idx];
            System.out.println(node.verName);
            visited[idx] = true;
            //查找它所有的邻居节点，放入队列
            EdgeNode edge = node.firstEdge;
            while (edge != null) {
                int j = edge.iIdx == idx ? edge.jIdx : edge.iIdx;
                if (!visited[j])
                    queue.offer(j);
                edge = edge.iIdx == idx ? edge.iNext : edge.jNext;
            }
        }
    }

    //栈实现深度优先
    public void dfsByStack(int x) {
        ArrayDeque<Integer> stack = new ArrayDeque<>();
        boolean[] visited = new boolean[verCount];
        stack.push(x);
        while (!stack.isEmpty()) {
            int idx = stack.pop();
            if (visited[idx])
                continue;
            MultiNode node = vertex[idx];
            System.out.println(node.verName);
            visited[idx] = true;
            //查找它所有的邻居节点，放入队列
//            ArrayList<Integer> temp = new ArrayList<>();
            EdgeNode edge = node.firstEdge;
            while (edge != null) {
                int j = edge.iIdx == idx ? edge.jIdx : edge.iIdx;
                if (!visited[j])
                    stack.push(j);
                //对顺序有强制要求，先收集，在入栈
//                if (!visited[j])
//                    temp.add(j);
                edge = edge.iIdx == idx ? edge.iNext : edge.jNext;
            }
            //如果对顺序有要求的话
            //可以增加一个List集合来暂时存放以上的j，等到edge==null时，在这里统一将他们全部倒序压入栈
//            for (int i = temp.size() - 1; i >= 0; i--) {
//                stack.add(temp.get(i));
//            }
        }
    }


//    private void bfs(int x, EdgeNode edge, boolean[] visited) {
//        Map<String, Object> map = getCurrentIdx(x, edge);
//        if (map == null)
//            return;
//        int i = (int) map.get("i");
//        int j = (int) map.get("j");
//        EdgeNode iNext = (EdgeNode) map.get("iNext");
//        if (visited[i] && visited[j]) {
//            bfs(i, iNext, visited);
//            return;
//        }
//        if (!visited[i]) {
//            System.out.println(vertex[i].verName);
//            visited[i] = true;
//        }
//        if (!visited[j]) {
//            System.out.println(vertex[j].verName);
//            visited[j] = true;
//        }
//        bfs(i, iNext, visited);
//        bfs(j, vertex[j].firstEdge, visited);
//    }


    //递归深度遍历
    protected void dfs(int x, EdgeNode edge, boolean[] visited) {
        if (!visited[x]) {
            System.out.println(vertex[x].verName);
            visited[x] = true;
        }
        Map<String, Object> map = getCurrentIdx(x, edge);
        if (map == null)
            return;
        int i = (int) map.get("i");
        int j = (int) map.get("j");
        EdgeNode iNext = (EdgeNode) map.get("iNext");
        if (!visited[j])
            dfs(j, vertex[j].firstEdge, visited);
        //调用完了回来
        dfs(i, iNext, visited);
    }

    protected Map<String, Object> getCurrentIdx(int x, EdgeNode edge) {
        if (edge == null)
            return null;
        HashMap<String, Object> map = new HashMap<>();
        int i = x, j = edge.jIdx;
        EdgeNode iNext = edge.iNext, jNext = edge.jNext;
        if (edge.iIdx != x) {
            i = edge.jIdx;
            j = edge.iIdx;
            iNext = edge.jNext;
            jNext = edge.iNext;
        }
        map.put("i", i);
        map.put("j", j);
        map.put("iNext", iNext);
        map.put("jNext", jNext);
        return map;
    }


    public static void main(String[] args) {
//        System.out.println(build().buildPrimTree(0));
//        System.out.println(build().buildKruskalTree());
//        build().dfs(0);
//        build().bfsByQueue(0);
        String[] str = {"v1", "v2", "v3", "v4", "v5", "v6", "v7"};
        MATGraph p = new MATGraph(str);
        Map<String, Object[]> map =
                Map.ofEntries(
                        Map.entry("a", new Object[]{0, 1, 2.0}),
                        Map.entry("b", new Object[]{0, 3, 1.0}),
                        Map.entry("c", new Object[]{0, 2, 4.0}),
                        Map.entry("d", new Object[]{1, 4, 10.0}),
                        Map.entry("e", new Object[]{1, 3, 3.0}),
                        Map.entry("f", new Object[]{2, 3, 2.0}),
                        Map.entry("g", new Object[]{2, 5, 5.0}),
                        Map.entry("h", new Object[]{3, 4, 7.0}),
                        Map.entry("i", new Object[]{3, 5, 8.0}),
                        Map.entry("j", new Object[]{3, 6, 4.0}),
                        Map.entry("k", new Object[]{4, 6, 6.0}),
                        Map.entry("l", new Object[]{5, 6, 1.0})
                );
        build(p, map).dfsByStack(0);
//        build().dfsByStack1(0);
    }

}

