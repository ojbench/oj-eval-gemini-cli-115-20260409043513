#include "src.hpp"
#include <iostream>
#include <cassert>

using namespace sjtu;

struct TestObj {
    int value;
    static int count;
    TestObj(int v) : value(v) { count++; }
    ~TestObj() { count--; }
};

int TestObj::count = 0;

void test_unique_ptr() {
    {
        unique_ptr<TestObj> p1(new TestObj(10));
        assert(p1->value == 10);
        assert((*p1).value == 10);
        assert(TestObj::count == 1);

        unique_ptr<TestObj> p2 = std::move(p1);
        assert(p1.get() == nullptr);
        assert(p2->value == 10);
        assert(TestObj::count == 1);

        unique_ptr<TestObj> p3;
        p3 = std::move(p2);
        assert(p2.get() == nullptr);
        assert(p3->value == 10);
        assert(TestObj::count == 1);

        TestObj* raw = p3.release();
        assert(p3.get() == nullptr);
        assert(raw->value == 10);
        assert(TestObj::count == 1);

        p3.reset(); // should do nothing
        assert(TestObj::count == 1);

        unique_ptr<TestObj> p4(raw);
        assert(TestObj::count == 1);
        p4.reset();
        assert(TestObj::count == 0);
    }
    assert(TestObj::count == 0);

    {
        auto p5 = make_unique<TestObj>(20);
        assert(p5->value == 20);
        assert(TestObj::count == 1);
    }
    assert(TestObj::count == 0);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test_unique_ptr();
    return 0;
}
