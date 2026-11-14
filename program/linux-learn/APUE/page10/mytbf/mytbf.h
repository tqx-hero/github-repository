#ifndef __MYTBF_H__
#define __MYTBF_H__

//定义存放令牌桶的数组最大长度
#define MYTBF_BUFSIZ 1024

//屏蔽真实的指针类型
typedef void mytbf_t;
//初始化令牌桶
mytbf_t *mytbf_init(int cps,int burst);
//获取令牌
int mytbf_fetch(mytbf_t*,int);
//回返未使用完的令牌
int mytbf_return(mytbf_t*,int);
//销毁令牌
int mytbf_destory(mytbf_t*);

#endif
