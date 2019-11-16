#ifndef ABSTRACT_H
#define ABSTRACT_H

/**/

#include <utility>

/**/

template <typename T>
struct Abstract {
    Abstract(T &t) : ref(t) {}
    Abstract(T &&t) : ref(t) {}
    T &ref;
};

/**/

struct IA {
    virtual auto a1() -> int = 0;
    virtual auto a2() -> int = 0;
};

template <typename T>
struct A : virtual IA, virtual Abstract<T> {
    A(T &t) : Abstract<T>(t) {}
    A(T &&t) : Abstract<T>(std::move(t)) {}

    auto a1() -> int override { return Abstract<T>::ref.a1(); }
    auto a2() -> int override { return Abstract<T>::ref.a2(); }
};

/**/

struct IB {
    virtual auto b1() -> int = 0;
    virtual auto b2() -> int = 0;
};

template <typename T>
struct B : virtual IB, virtual Abstract<T> {
    B(T &t) : Abstract<T>(t) {}
    B(T &&t) : Abstract<T>(std::move(t)) {}

    auto b1() -> int override { return Abstract<T>::ref.b1(); }
    auto b2() -> int override { return Abstract<T>::ref.b2(); }
};

/**/

struct IC : virtual IA, virtual IB {};

template <typename T>
struct C : virtual IC, virtual A<T>, virtual B<T>, virtual Abstract<T> {
    C(T &t) : A<T>(t), B<T>(t), Abstract<T>(t) {}
    C(T &&t) : A<T>(t), B<T>(t), Abstract<T>(t) {}
};

/**/

#endif
