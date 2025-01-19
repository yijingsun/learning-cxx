#include "../exercise.h"

// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T> // 声明一个类模版
struct Tensor4D {
    unsigned int shape[4]; // 张量的形状，四维大小
    T *data; // 指向存储张量数据的指针，C++ 中，通常是行优先row-major

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size
        for (int i = 0; i < 4; i++)
        {
            shape[i] = shape_[i];
        }
        for (int i = 0; i < 4; i++)
        {
            size *= shape[i];
        }
        
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }
    ~Tensor4D() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 这个加法需要支持“单向广播”。
    // 具体来说，`others` 可以具有与 `this` 不同的形状，形状不同的维度长度必须为 1。
    // `others` 长度为 1 但 `this` 长度不为 1 的维度将发生广播计算。
    // 例如，`this` 形状为 `[1, 2, 3, 4]`，`others` 形状为 `[1, 2, 1, 4]`，
    // 则 `this` 与 `others` 相加时，3 个形状为 `[1, 2, 1, 4]` 的子张量各自与 `others` 对应项相加。 //  this的第三个维度长度为3，可拆分成3个
    Tensor4D &operator+=(Tensor4D const &others) {
        // TODO: 实现单向广播的加法
        unsigned int this_size = 1;

        // 检查形状是否兼容
        for (int i = 0; i < 4; i++) {
            if (shape[i] != others.shape[i] && others.shape[i] != 1)
            {
                throw std::invalid_argument("形状不同的维度长度必须为 1");
            }
        }

        for (int i = 0; i < 4; i++)
        {
            this_size *= shape[i];
        }

        // 二维张量形状[2,3]，共6个元素，索引(i,j)，对应数组下标 i * dim2 +j
        // 四维张量形状[1,2,3,4]，共24个元素，索引（i,j,k,l），对应数组下标 ((i * dim2 + j) * dim3 +k)
        
        for (unsigned int i = 0; i < this_size; i++)
        {

            // 计算 this 的索引
            unsigned int idx = i;
            unsigned int this_idx[4];
            for (int dim = 3; dim >= 0; --dim) {
                this_idx[dim] = idx % shape[dim]; // 按顺序计算 l,k,j,i的值 // %取余数
                idx /= shape[dim]; // 整除
            }

            // 通过循环计算出对应索引在 others 数组中的位置 ((i * dim2 + j) * dim3 +k)
            unsigned int others_idx = 0;
            for (int dim = 0; dim < 4; ++dim) {
                others_idx *= others.shape[dim];
                others_idx += (others.shape[dim] == 1) ? 0 : this_idx[dim]; // 维度长度为1时，默认使用索引 0（即广播），否则取上一步算出来的索引
            }

            // 执行加法
            data[i] += others.data[others_idx];
        }

        return *this;
    }
};


// 推导指南（C++17 及以上）
template<class T>
Tensor4D(unsigned int const[4], T const*) -> Tensor4D<T>;

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        auto t0 = Tensor4D(shape, data);
        auto t1 = Tensor4D(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]{1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}
