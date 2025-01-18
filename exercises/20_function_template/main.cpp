#include "../exercise.h"

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化
// int plus(int a, int b) {
//     return a + b;
// }
template <typename T>
T plus(T a, T b) {
    return a+b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？ // 由整数转化而来可直接判断== // 浮点数经过运算、来自不同计算路径时需计算差值，选择合适的epsilon，一般是1e^-6或1e^-9
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    // TODO: 修改判断条件使测试通过 // 0.1和0.2用二进制表示都是无限不循环小数，计算机存储的近似值有精度问题
    ASSERT(plus(0.1f, 0.2f) == 0.3f, "How to make this pass?");

    return 0;
}
