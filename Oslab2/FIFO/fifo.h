#ifndef FIFO_H
#define FIFO_H
#include <linux/list.h>
#include <linux/spinlock.h>
#define FIFO_SIZE 1024 // 定义FIFO队列的大小

struct fifo_list {
    unsigned long pages[FIFO_SIZE]; // FIFO队列的页面帧号数组
    int head; // 队列头指针
    int tail; // 队列尾指针
    spinlock_t lock; // 自旋锁，用于保护FIFO队列的并发访问
};

extern struct fifo_list fifo; // FIFO队列的全局变量
void add_fifo_page(unsigned long pfn); // 添加页面到FIFO队列
#endif /* FIFO_H */