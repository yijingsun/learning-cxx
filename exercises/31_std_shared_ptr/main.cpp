#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10); // 创建+1
    std::shared_ptr<int> ptrs[]{shared, shared, shared}; // 复制+3

    std::weak_ptr<int> observer = shared; // std::weak_ptr 是一个弱引用指针，它不会增加所指向对象的引用计数。
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset(); // -1
    // ptrs[0] 是一个 std::shared_ptr<int>，调用 reset() 会将其置为空指针，并减少所管理对象的引用计数。 -1
    ASSERT(observer.use_count() == 3, ""); 
    /*
    observer.use_count() 返回的是与之关联的 std::shared_ptr 的引用计数
    1.std::weak_ptr 的行为：
        std::weak_ptr 不会增加引用计数。
        使用 observer.use_count() 返回的是与之关联的 std::shared_ptr 的引用计数。
    2.std::shared_ptr 的引用计数：
        当 std::shared_ptr 被创建时，引用计数为 1。
        如果将其赋值给另一个 std::shared_ptr，引用计数会增加。
        如果将其赋值给 std::weak_ptr，引用计数不会增加。
    */

    ptrs[1] = nullptr; // -1
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared); // -1 // 创建了一个新的 std::shared_ptr，它与 shared 无关.但ptrs[2] 原本指向 shared 所管理的资源，现在指向新的资源，而不是原来的 shared 所管理的资源。
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared; // +1
    ptrs[1] = shared; // +1
    ptrs[2] = std::move(shared); // 将 shared 的所有权转移给 ptrs[2]，不会增加引用计数。 // ptrs[2] 指向 shared 原来的资源，而 shared 变为空指针。
    ASSERT(observer.use_count() == 3, ""); // 此时ptrs[0]、ptrs[1] 和 ptrs[2] 都指向同一个资源，引用计数为 3。

    std::ignore = std::move(ptrs[0]); // -1 ptrs[0]原本指向资源但变为空指针
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]); // ptrs[2]变为nullptr，但p1与p2指向资源一致，所以不减少引用次数
    ASSERT(observer.use_count() == 2, "");

    shared = observer.lock(); // +1 observer.lock() 会创建一个新的 std::shared_ptr，增加引用计数。
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr; // -1
    for (auto &ptr : ptrs) ptr = nullptr; // 引用计数变为0
    ASSERT(observer.use_count() == 0, ""); // 当 std::shared_ptr 的引用计数变为 0 时，它所管理的资源会被自动释放。

    shared = observer.lock(); 
    /*
        当资源已经被释放后，调用 observer.lock() 会返回一个空的 std::shared_ptr。
        这种行为可以用来检查资源是否仍然存在，避免访问已经释放的资源。
    */
    ASSERT(observer.use_count() == 0, "");

    return 0;
}
