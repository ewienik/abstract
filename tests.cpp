#include "abstract.h"

#include "catch.hpp"

/**/

namespace {

/**/

struct AImpl {
    auto a1() {
        count++;
        return 2;
    }
    auto a2() {
        count++;
        return 3;
    }
    int count{}; // NOLINT
};

/**/

struct BImpl {
    auto b1() {
        count++;
        return 4;
    }
    auto b2() {
        count++;
        return 5;
    }
    int count{}; // NOLINT
};

/**/

struct CImpl1 {
    auto a1() {
        count++;
        return 6;
    }
    auto a2() {
        count++;
        return 7;
    }
    auto b1() {
        count++;
        return 8;
    }
    auto b2() {
        count++;
        return 9;
    }
    int count{}; // NOLINT
};

/**/

struct CImpl2 : public AImpl, public BImpl {};

/**/

struct Use {
    Use(IC *ic) : ic(ic) { std::cout << "Use: " << this << ", " << ic << "\n" << std::flush; }
    IC *ic; // NOLINT
};

/**/

} // namespace

/**/

#if 0
TEST_CASE("IA") {
    auto aimpl = AImpl{};
    auto a = A(aimpl);

    REQUIRE(2 == [](IA &&ia) { return ia.a1(); }(A(aimpl)));
    REQUIRE(3 == [](IA &&ia) { return ia.a2(); }(A(aimpl)));

    REQUIRE(2 == [](IA &ia) { return ia.a1(); }(a));
    REQUIRE(3 == [](IA &ia) { return ia.a2(); }(a));

    REQUIRE(2 == [](IA *ia) { return ia->a1(); }(&a));
    REQUIRE(3 == [](IA *ia) { return ia->a2(); }(&a));

    REQUIRE(aimpl.count == 6);
}

/**/

TEST_CASE("IB") {
    auto bimpl = BImpl{};
    auto b = B(bimpl);

    REQUIRE(4 == [](IB &&ib) { return ib.b1(); }(B(bimpl)));
    REQUIRE(5 == [](IB &&ib) { return ib.b2(); }(B(bimpl)));

    REQUIRE(4 == [](IB &ib) { return ib.b1(); }(b));
    REQUIRE(5 == [](IB &ib) { return ib.b2(); }(b));

    REQUIRE(4 == [](IB *ib) { return ib->b1(); }(&b));
    REQUIRE(5 == [](IB *ib) { return ib->b2(); }(&b));

    REQUIRE(bimpl.count == 6);
}

/**/

TEST_CASE("IC1") {
    auto cimpl = CImpl1{};
    auto c = C(cimpl);

    REQUIRE(6 == [](IC &&ic) { return ic.a1(); }(C(cimpl)));
    REQUIRE(7 == [](IC &&ic) { return ic.a2(); }(C(cimpl)));
    REQUIRE(8 == [](IC &&ic) { return ic.b1(); }(C(cimpl)));
    REQUIRE(9 == [](IC &&ic) { return ic.b2(); }(C(cimpl)));

    REQUIRE(6 == [](IC &ic) { return ic.a1(); }(c));
    REQUIRE(7 == [](IC &ic) { return ic.a2(); }(c));
    REQUIRE(8 == [](IC &ic) { return ic.b1(); }(c));
    REQUIRE(9 == [](IC &ic) { return ic.b2(); }(c));

    REQUIRE(6 == [](IC *ic) { return ic->a1(); }(&c));
    REQUIRE(7 == [](IC *ic) { return ic->a2(); }(&c));
    REQUIRE(8 == [](IC *ic) { return ic->b1(); }(&c));
    REQUIRE(9 == [](IC *ic) { return ic->b2(); }(&c));

    REQUIRE(cimpl.count == 12);
}

/**/

TEST_CASE("IC2") {
    auto cimpl = CImpl2{};
    auto c = C(cimpl);

    REQUIRE(2 == [](IC &&ic) { return ic.a1(); }(C(cimpl)));
    REQUIRE(3 == [](IC &&ic) { return ic.a2(); }(C(cimpl)));
    REQUIRE(4 == [](IC &&ic) { return ic.b1(); }(C(cimpl)));
    REQUIRE(5 == [](IC &&ic) { return ic.b2(); }(C(cimpl)));

    REQUIRE(2 == [](IC &ic) { return ic.a1(); }(c));
    REQUIRE(3 == [](IC &ic) { return ic.a2(); }(c));
    REQUIRE(4 == [](IC &ic) { return ic.b1(); }(c));
    REQUIRE(5 == [](IC &ic) { return ic.b2(); }(c));

    REQUIRE(2 == [](IC *ic) { return ic->a1(); }(&c));
    REQUIRE(3 == [](IC *ic) { return ic->a2(); }(&c));
    REQUIRE(4 == [](IC *ic) { return ic->b1(); }(&c));
    REQUIRE(5 == [](IC *ic) { return ic->b2(); }(&c));

    REQUIRE(cimpl.AImpl::count == 6);
    REQUIRE(cimpl.BImpl::count == 6);

    auto pointer = []([[maybe_unused]] IC *ic) {};
    auto move = []([[maybe_unused]] IC &&ic) {};
    auto a1 = [](IC &&ic) { ic.a1(); };
    BENCHMARK("Pointer") { pointer(&c); };
    BENCHMARK("Move") { move(C(cimpl)); };
    BENCHMARK("A1") { a1(C(cimpl)); };
}

#endif
/**/

TEST_CASE("Use") {
    auto cimpl = CImpl2{};
    std::cout << "Use cimpl: " << &cimpl << ", " << sizeof(C(cimpl)) << ", " << sizeof(IC) << ", "
              << sizeof(Abstract<CImpl2>) << "\n"
              << std::flush;
    auto ptr = static_cast<IC *>((C(cimpl)));
    std::cout << "Use ptr: " << ptr << "\n" << std::flush;
    auto use = Use(C(cimpl));
    // auto use = [&]() -> Use { return Use(C(cimpl)); }();

    REQUIRE(2 == use.ic->a1());
    REQUIRE(3 == use.ic->a2());
    REQUIRE(4 == use.ic->b1());
    REQUIRE(5 == use.ic->b2());

    REQUIRE(cimpl.AImpl::count == 2);
    REQUIRE(cimpl.BImpl::count == 2);
}

/**/

