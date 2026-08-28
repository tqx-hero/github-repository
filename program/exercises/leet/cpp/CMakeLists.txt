cmake_minimum_required(VERSION 4.2)
project(cpp)

#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp main.cpp
        leet/leet2095.cpp
        link/LinkList.cpp
        link/Reverse_link.cpp
        link/main.cpp
        link/ListNode.cpp
        leet/Leet027.cpp
        leet/leet2058.cpp
        leet/leet2074.cpp
        leet/leet3754.cpp
        leet/leet3756.cpp
        leet/leet2130.cpp
        leet/leet2289.cpp
        leet/leet2807.cpp
        leet/leet2816.cpp
        leet/leet3217.cpp
        leet/leet1331.cpp
        leet/lcr021.cpp
        leet/leet1291.cpp
        leet/leet2540.cpp
        leet/leet2553.cpp
        leet/lrc025.cpp
        leet/leet355.cpp
        leet/leet382.cpp
        leet/leet460.cpp
        leet/leet1427.cpp
        leet/l3658.cpp
        leet/l1712.cpp
        link/TreeNode.cpp
        link/TreeNode.h
        leet/l0207.cpp
        leet/l0206.cpp
        leet/l0203.cpp
        leet/l0202.cpp
        leet/l0201.cpp
        leet/lcr141.cpp
        leet/l155.cpp
        leet/l0403.cpp
        leet/l0204.cpp
        leet/l3867.cpp
        leet/l2326.cpp
        leet/l1625.cpp
        leet/l1081.cpp
        leet/l078.cpp
        leet/l1260.cpp
        leet/l2296.cpp
        leet/l3499.cpp
        leet/l029.cpp
        leet/l1797.cpp
        leet/queue/l1700.cpp
#        leet/位运算/l3513.cpp
#        leet/链表/l0208.cpp
#        leet/链表/l031LRU.cpp
#        leet/链表/l154.cpp
#        leet/链表/排序链表077.cpp
#        leet/栈/整理字符串1544.cpp
#        leet/栈/括号的最大嵌套深度1614.cpp
#        leet/位运算/不同xor三元组数目II-3514.cpp
#        leet/链表/重排链表LRC026.cpp
#        leet/链表/扁平化多级双向链表LCR028.cpp
#        leet/数组/两个数字最大乘积3536.cpp
#        leet/链表/环形链表022.cpp
#        leet/数组/移除最小数对使数组有序3507.cpp
#        leet/栈/字符串解码394.cpp
#        leet/queue/三个数的最大乘积628.cpp
#        leet/链表/二叉树中的链表1367.cpp
#        leet/queue/化栈为队0304.cpp
#        leet/queue/找出游戏的胜利者1823.cpp
#        leet/queue/最小回文排列I3517.cpp
#        leet/queue/设计路由器3508.cpp
#        leet/每日一题/输入单词所需最少按键次数3014.cpp
#        leet/queue/设计自助结算系统184.cpp
#        leet/每日一题/输入单词所需最少按键次数II-3016.cpp
#        leet/queue/找到数据流中的连续整数-2526.cpp
#        leet/queue/按递增顺序显示卡牌-950.cpp
#        leet/栈/栈的最小值-0302.cpp
#        leet/栈/栈排序-0305.cpp
#        leet/queue/设计共享出行系统-3829.cpp
#        leet/queue/知道秘密的人数-2327.cpp
#        leet/queue/扁平化嵌套列表迭代器-341.cpp
#        leet/栈/计算器-1626.cpp
#        leet/queue/望远镜中最高的海拔-183.cpp
#        leet/queue/满足不等式的最大值-1499.cpp
#        leet/每日一题/找出缺失的元素-3731.cpp
#        leet/queue/不间断子数组-2762.cpp
#        leet/queue/Dota2参议院-649.cpp
#        leet/queue/K连续位的最小翻转次数-995.cpp
#        leet/栈/基本计算器-224.cpp
#        leet/栈/N叉树的前序遍历-589.cpp
#        leet/每日一题/最小可整除数位乘积I-3345.cpp
#        leet/栈/N叉树的后序遍历-590.cpp
#        leet/栈/棒球比赛-682.cpp
#        leet/栈/比较含退格的字符串-844.cpp
#        leet/栈/递增顺序搜索树-897.cpp
#        leet/栈/删除最外层括号-1021.cpp
#        leet/栈/删除字符串中所有相邻的重复项-1047.cpp
#        leet/栈/验证栈序列-946.cpp
#        leet/栈/文件夹操作日志搜集器-1598.cpp
#        leet/栈/反转单词前缀-2000.cpp
#        leet/栈/三合一-0301.cpp
#        leet/栈/最小栈-147.cpp
#        leet/栈/清除数字-3174.cpp
#        leet/栈/删除子串后的字符串最小长度.cpp
#        leet/树/验证二叉搜索树的后序遍历序列-152.cpp
#        leet/初级算法/数组/LC-旋转数组.cpp
#        leet/初级算法/数组/存在重复元素.cpp
#        leet/初级算法/数组/两个数组的交集.cpp
#        leet/初级算法/数组/移动零.cpp
#        leet/初级算法/数组/两数之和.cpp
#        leet/初级算法/数组/有效数独.cpp
#        leet/初级算法/数组/旋转图像.cpp
#        leet/初级算法/字符串/整数翻转.cpp
#        leet/初级算法/字符串/字符串中第一个唯一字符.cpp
#        leet/初级算法/字符串/有效的字母异位词.cpp
#        leet/初级算法/字符串/验证回文串.cpp
#        leet/初级算法/字符串/字符串转整数atoi.cpp
#        leet/初级算法/字符串/实现strStr.cpp
#        leet/初级算法/字符串/外观数列.cpp
#        leet/初级算法/字符串/最长公共前缀.cpp
#        leet/初级算法/链表/删除链表的倒数第N个节点.cpp
#        leet/初级算法/链表/翻转链表.cpp
#        leet/初级算法/链表/合并两个有序链表.cpp
        leet/初级算法/链表/回文链表.cpp
        leet/初级算法/链表/环形链表.cpp
        leet/初级算法/树/二叉树的最大深度.cpp
        leet/初级算法/树/验证二叉搜索树.cpp
        leet/初级算法/树/对称二叉树.cpp
        leet/初级算法/树/二叉树的层序遍历.cpp
        leet/初级算法/树/将有序数组转换为二叉搜索树.cpp
        leet/初级算法/排序和搜索/合并两个有序数组.cpp
        leet/初级算法/排序和搜索/第一个错误的版本.cpp
        leet/初级算法/动态规划/爬楼梯.cpp
        leet/初级算法/动态规划/买股票的最佳时机.cpp
        leet/每日一题/每个字符最多出现两次的最长子字符串-3090.cpp
        leet/初级算法/动态规划/最大子序和.cpp
        leet/初级算法/动态规划/打家劫舍.cpp
        leet/初级算法/设计问题/打乱数组.cpp
        leet/初级算法/设计问题/最小栈.cpp
        leet/初级算法/数学/Fizz-Buzz.cpp
        leet/初级算法/数学/计数质数.cpp
        leet/初级算法/数学/3的幂.cpp
        leet/初级算法/数学/罗马数字转整数.cpp
        leet/初级算法/其他/位1的个数.cpp
        leet/初级算法/其他/汉明距离.cpp
        leet/初级算法/其他/颠倒二进制位.cpp
        leet/初级算法/其他/杨辉三角.cpp
        leet/初级算法/其他/有效的括号.cpp
        leet/初级算法/其他/缺失数字.cpp
        leet/栈/递增顺序搜索树-LCR052.cpp
        leet/每日一题/安排电影院座位-1386.cpp
        leet/栈/使字符串平衡的最小交换次数-1963.cpp
        leet/每日一题/将元素分配到两个数组中-3069.cpp
        leet/树/最大二叉树-654.cpp
        leet/字符串/有效的括号字符串-678.cpp
        leet/栈/从字符串中移除星号-2390.cpp
        leet/栈/有小括号的嵌套深度-1111.cpp
        leet/树/叶值最小代价生成树-1130.cpp
        leet/每日一题/判断整除性-3622.cpp
        leet/每日一题/检查数组是否经排序和轮转得到.cpp
        leet/栈/前序遍历构造二叉搜索树-1008.cpp
        leet/哈希表/字母异位词分组-49.cpp
        leet/哈希表/最长连续序列-128.cpp
        leet/哈希表/最短且字典序最小的美丽子字符串-2904.cpp
        leet/每日一题/大于目标字符串的最小字典序排列-3720.cpp
        leet/每日一题/大于目标字符串的最小字典序回文排列.cpp
        leet/热门100题/三数之和-15.cpp
        leet/热门100题/找到字符串中所有字母异位词.cpp
)
