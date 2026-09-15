package com.tqx.graph;

import java.lang.module.FindException;
import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 欧拉回路
 * @date 2026/4/19 14:11
 */
public class EulerCircuit extends MATGraph {

    private static final int EULERCIR = 0, EULERPATH = 1, NONE = -1, INIT = -2, RESET = -1;

    //统计顶点的度
    private int[] indegrees;
    //图的类型：0：欧拉回路；1：单纯的欧拉路径(欧拉通路) ;-1 : 都不是;-2 : 未查询
    private int eulerType;

    public EulerCircuit(String[] ver) {
        super(ver);
        verCount = ver.length;
        vertex = new EulerNode[verCount];
        indegrees = new int[verCount];
        eulerType = INIT;
        for (int i = 0; i < verCount; i++)
            vertex[i] = new EulerNode(ver[i]);
    }

    //顶点
    private static class EulerNode extends MultiNode {

        public EulerNode(String verName) {
            super(verName);
        }
    }

    //边
    private static class ELEdgeNode extends EdgeNode {

        public ELEdgeNode(double cost, String edgeName, int iIdx, EdgeNode iNext, int jIdx, EdgeNode jNext, int idx) {
            super(cost, edgeName, iIdx, iNext, jIdx, jNext, idx);
        }
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
            edges[i] = vertex[iIdx].firstEdge = vertex[jIdx].firstEdge =
                    new ELEdgeNode(cost, name, iIdx, vertex[iIdx].firstEdge, jIdx, vertex[jIdx].firstEdge, i++);
            //给这两个顶点增加度数
            indegrees[iIdx]++;
            indegrees[jIdx]++;
        }
    }

    //初始化边
    public void init(Map<String, Object[]> edge) {
        if (edge == null || edge.isEmpty())
            throw new IllegalArgumentException("边不能为空");
        edgeCount = edge.size();
        edges = new ELEdgeNode[edgeCount];
        initEdges(edge);
    }

    protected static class ResultNode {
        //顶点的下标
        int index;
        ResultNode next;

        public ResultNode(int index) {
            this.index = index;
        }

        public ResultNode() {
        }
    }

    protected static class ResultLinked {
        //链表的头尾指针
        ResultNode head, tail;

        public ResultLinked() {
            head = tail = new ResultNode();
        }

        ResultLinked add(int x) {
            tail = tail.next = new ResultNode(x);
            return this;
        }

        //添加链表到第一个出现的下标位置
        ResultLinked addCurrent(ResultLinked node) {
            if (node == null)
                return this;
            //链表为空，将node合并过来
            if (head == tail) {
                head = node.head;
                tail = node.tail;
                return this;
            }
            int idx = node.head.next.index;
            //遍历找到第一个下标的node
            ResultNode cur = head.next;
            while (cur != null) {
                int index = cur.index;
                //下标相同，替换这个节点并连接node
                if (idx == index) {
                    ResultNode next = cur.next;
                    cur.next = node.head.next.next;
                    node.tail.next = next;
                    node.head.next.next = null;
                    break;
                }
                cur = cur.next;
            }
            return this;
        }
    }

    private int getCount() {
        int c = EULERCIR;
        for (int i = 0; i < verCount; i++) {
            //有度为0的或者度为奇数个的超过2个的顶点，既不是欧拉回路也不是欧拉路径
            if (indegrees[i] == 0 || c > 2)
                return c;
            if (indegrees[i] % 2 != 0)
                c++;
        }
        return c;
    }

    //判断是否为欧拉回路
    private boolean isEulerCircuit() {
        if (eulerType != INIT)
            return eulerType == EULERCIR;
        int c = getCount();
        return (eulerType = c == 0 ? EULERCIR : (c == 2 ? EULERPATH : NONE)) == EULERCIR;
    }


    //查找欧拉回路
    public String[] getEulerCircuit(int x) {
        if (!isEulerCircuit())
            throw new FindException("不满足欧拉回路条件");
        String[] result = new String[edgeCount + 1];
        boolean[] visited = new boolean[edgeCount];
        ResultLinked all = new ResultLinked();
        //备份度信息
        int[] ins = Arrays.copyOf(indegrees, verCount);
        ArrayDeque<Integer> stack = new ArrayDeque<>();
        stack.push(x);
        ResultLinked r = new ResultLinked();
        //记录起始顶点
        int curIndex = RESET;
        ArrayList<Integer> list = new ArrayList<>();
        int count = 0;
        while (!stack.isEmpty()) {
            int index = stack.pop();
            //度为0的点直接跳过
            if (ins[index] == 0)
                continue;
            EdgeNode edge = vertex[index].firstEdge;
            EdgeNode cur = edge;
            while (cur != null) {
                //将没有访问过的边所有顶点放到list准备压栈
                if (!visited[cur.idx]) {
                    //保留第一个没访问过的边
                    if (list.isEmpty())
                        edge = cur;
                    list.add(cur.iIdx == index ? cur.jIdx : cur.iIdx);
                }
                cur = cur.iIdx == index ? cur.iNext : cur.jNext;
            }
            //将所有没访问过的边对应顶点压栈
            for (int l = list.size() - 1; l >= 0; l--)
                stack.push(list.get(l));
            //拿取边的另一个点下标
            int other = list.get(0);
            list.clear();
            visited[edge.idx] = true;
            r.add(index);
            count++;
            //没访问过的才要进行记录处理
            //访问过的边直接重新筛选
            ins[other]--;
            ins[index]--;
            //转圈回来了,需要将结果记录汇总到all记录中
            //并重置r记录
            if (curIndex == RESET)
                curIndex = index;
                //转一圈回来了，记录，清空状态
            else if (curIndex == other) {
                r.add(other);
                count++;
                all.addCurrent(r);
                //查看结果集是否已满，满了直接返回
                if (count == result.length)
                    break;
                r = new ResultLinked();
                curIndex = RESET;
            }
        }
        //拼出结果
        ResultNode cur = all.head.next;
        for (int i = 0; i < result.length; i++) {
            result[i] = vertex[cur.index].verName;
            cur = cur.next;
        }
        return result;
    }

    //计算欧拉回路
    public List<String> Hierholzer(int x) {
        ArrayDeque<Integer> stack = new ArrayDeque<>();
        boolean[] visited = new boolean[edgeCount];
        ArrayList<String> result = new ArrayList<>(edgeCount + 1);
        stack.push(x);
        while (!stack.isEmpty()) {
            //不往外拿，直接先查看有没有可以走的边，有的话直接压入顶点
            //没有才会弹出
            int cur = stack.peek();
            EdgeNode edge = vertex[cur].firstEdge;
            boolean found = false;
            while (edge != null) {
                //没访问的边，设置为已访问，并将另一个顶点入栈
                if (!visited[edge.idx]) {
                    visited[edge.idx] = true;
                    stack.push(edge.iIdx == cur ? edge.jIdx : edge.iIdx);
                    //找到以后停止压栈，循环再从栈顶去查找
                    found = true;
                    break;
                }
                edge = edge.iIdx == cur ? edge.iNext : edge.jNext;
            }
            if (!found)
                result.add(vertex[stack.pop()].verName);
        }
        Collections.reverse(result);
        return result;

    }

    public static Map<String, Object[]> map() {
//        return
//                Map.ofEntries(
//                        Map.entry("a", new Object[]{0, 1, 1.0}),
//                        Map.entry("b", new Object[]{0, 3, 1.0}),
//                        Map.entry("c", new Object[]{1, 2, 1.0}),
//                        Map.entry("d", new Object[]{2, 3, 1.0}),
//                        Map.entry("e", new Object[]{0, 4, 1.0}),
//                        Map.entry("f", new Object[]{0, 2, 1.0}),
//                        Map.entry("g", new Object[]{1, 3, 1.0}),
//                        Map.entry("h", new Object[]{1, 4, 1.0}),
//                        Map.entry("i", new Object[]{2, 4, 1.0}),
//                        Map.entry("j", new Object[]{3, 4, 1.0})
//                );
        return
                Map.ofEntries(
                        Map.entry("a", new Object[]{0, 2, 1.0}),
                        Map.entry("b", new Object[]{0, 3, 1.0}),
                        Map.entry("c", new Object[]{1, 2, 1.0}),
                        Map.entry("d", new Object[]{1, 7, 1.0}),
                        Map.entry("e", new Object[]{2, 3, 1.0}),
                        Map.entry("f", new Object[]{2, 5, 1.0}),
                        Map.entry("g", new Object[]{2, 6, 1.0}),
                        Map.entry("h", new Object[]{2, 8, 1.0}),
                        Map.entry("i", new Object[]{3, 4, 1.0}),
                        Map.entry("j", new Object[]{3, 6, 1.0}),
                        Map.entry("k", new Object[]{3, 9, 1.0}),
                        Map.entry("l", new Object[]{3, 10, 1.0}),
                        Map.entry("m", new Object[]{4, 9, 1.0}),
                        Map.entry("n", new Object[]{5, 8, 1.0}),
                        Map.entry("o", new Object[]{6, 8, 1.0}),
                        Map.entry("p", new Object[]{6, 9, 1.0}),
                        Map.entry("q", new Object[]{7, 8, 1.0}),
                        Map.entry("r", new Object[]{8, 9, 1.0}),
                        Map.entry("s", new Object[]{8, 11, 1.0}),
                        Map.entry("t", new Object[]{9, 11, 1.0}),
                        Map.entry("u", new Object[]{9, 10, 1.0})
                );
    }

    public static void main(String[] args) {
        String[] str1 = {"v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12"};
//        String[] str1 = {"v1", "v2", "v3", "v4", "v5"};
        EulerCircuit p = (EulerCircuit) build(new EulerCircuit(str1), map());
//        System.out.println(p.isEulerCircuit());
//        System.out.println(Arrays.toString(p.getEulerCircuit(0)));
        System.out.println(p.Hierholzer(0));
    }

}
