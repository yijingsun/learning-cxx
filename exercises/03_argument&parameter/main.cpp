#include "../exercise.h"

// READ: <https://stackoverflow.com/questions/156767/whats-the-difference-between-an-argument-and-a-parameter>
// THINK: 参数都有哪些传递方式？如何选择传递方式？ 判断参数需不需要随函数调用更新值。
// 值传递、引用传递与指针传递。
// 值传递通常用于不需要修改实参值的情况。
// 引用传递通常用于需要修改实参值的情况。
// 指针传递通常用于需要操作复杂数据结构或动态内存分配的情况。

void func(int);

// TODO: 为下列 ASSERT 填写正确的值
int main(int argc, char **argv) {
    auto arg = 99;
    ASSERT(arg == 99, "arg should be ?");
    std::cout << "befor func call: " << arg << std::endl;
    func(arg);
    ASSERT(arg == 99, "arg should be ?");
    std::cout << "after func call: " << arg << std::endl;
    return 0;
}

// TODO: 为下列 ASSERT 填写正确的值
void func(int param) {
    ASSERT(param == 99, "param should be ?");
    std::cout << "befor add: " << param << std::endl;
    param += 1;
    ASSERT(param == 100, "param should be ?");
    std::cout << "after add: " << param << std::endl;
}
