#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>

// READ: `std::transform` <https://zh.cppreference.com/w/cpp/algorithm/transform>
// READ: `std::vector::begin` <https://zh.cppreference.com/w/cpp/container/vector/begin>

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    // TODO: 调用 `std::transform`，将 `v` 中的每个元素乘以 2，并转换为字符串，存入 `ans`
    // (输入容器 v 的起始迭代器, 输入容器 v 的结束迭代器, 表示输出容器 ans 的起始迭代器, 转换操作)
    /*
        [](int x) { return std::to_string(x * 2); } 是一个 lambda 函数，定义了对每个输入元素的转换逻辑。
        参数 x：输入容器 v 中的每个元素。
        操作 x * 2：将元素乘以 2。
        std::to_string(x * 2)：将结果转换为字符串。
    */
    std::vector<std::string> ans(val.size());
    std::transform(val.begin(), val.end(), ans.begin(), [](int x) {
        return std::to_string(x * 2); // 将元素乘以 2 并转换为字符串
    });
    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");
    return 0;
}
