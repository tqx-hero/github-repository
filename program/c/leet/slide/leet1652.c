//
// Created by Administrator on 2026/7/5.
//
/**
* 1652. 拆炸弹
简单
相关标签
premium lock icon
相关企业
提示
你有一个炸弹需要拆除，时间紧迫！你的情报员会给你一个长度为 n 的 循环 数组 code 以及一个密钥 k 。

为了获得正确的密码，你需要替换掉每一个数字。所有数字会 同时 被替换。

如果 k > 0 ，将第 i 个数字用 接下来 k 个数字之和替换。
如果 k < 0 ，将第 i 个数字用 之前 k 个数字之和替换。
如果 k == 0 ，将第 i 个数字用 0 替换。
由于 code 是循环的， code[n-1] 下一个元素是 code[0] ，且 code[0] 前一个元素是 code[n-1] 。

给你 循环 数组 code 和整数密钥 k ，请你返回解密后的结果来拆除炸弹！



示例 1：

输入：code = [5,7,1,4], k = 3
输出：[12,10,16,13]
解释：每个数字都被接下来 3 个数字之和替换。解密后的密码为 [7+1+4, 1+4+5, 4+5+7, 5+7+1]。注意到数组是循环连接的。
示例 2：

输入：code = [1,2,3,4], k = 0
输出：[0,0,0,0]
解释：当 k 为 0 时，所有数字都被 0 替换。
示例 3：

输入：code = [2,4,9,3], k = -2
输出：[12,5,6,13]
解释：解密后的密码为 [3+9, 2+3, 4+2, 9+4] 。注意到数组是循环连接的。如果 k 是负数，那么和为 之前 的数字。


提示：

n == code.length
1 <= n <= 100
1 <= code[i] <= 100
-(n - 1) <= k <= n - 1
 * @return
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *decrypt(int *code, int codeSize, int k, int *returnSize) {
    *returnSize = codeSize;
    int *ret = calloc(codeSize, sizeof(int));
    if (!ret) {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    if (!k)
        return ret;
    int ks = abs(k), size = codeSize + ks, count = 0, i, sum = 0;
    int *tmp = malloc(size * sizeof(int));
    if (!tmp) {
        printf("%s\n", strerror(errno));
        free(ret);
        return NULL;
    }
    if (k > 0) {
        //k大于0，将code数组前k个元素放到code数组后面
        memcpy(tmp, code, codeSize * sizeof(int));
        memcpy(tmp + codeSize, code, ks * sizeof(int));
        //加载0号位置
        for (i = 1; i <= k; i++)
            sum += tmp[i];
        ret[count++] = sum;
        //指针移动
        for (; i < size; i++) {
            sum += (tmp[i] - tmp[count]);
            ret[count++] = sum;
        }
    } else {
        //k<0，将数组后k个元素放到code前面
        memcpy(tmp, code + (codeSize - ks), ks * sizeof(int));
        memcpy(tmp + ks, code, codeSize * sizeof(int));
        for (i = 0; i < ks; i++)
            sum += tmp[i];
        ret[count++] = sum;
        for (; i < size - 1; i++) {
            sum += tmp[i] - tmp[i - ks];
            ret[count++] = sum;
        }
    }
    free(tmp);
    return ret;
}

int main() {
    int code[] = {2, 4, 9, 3}, size, k = -2;
    // int code[] = {5, 7, 1, 4}, size, k = 0;
    int *re = decrypt(code, sizeof(code) / sizeof(int), k, &size);
    for (int i = 0; i < size; i++) {
        printf("%d ", re[i]);
    }
    free(re);
    return 0;
}
