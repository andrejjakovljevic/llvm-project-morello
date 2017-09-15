//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <numeric>
// UNSUPPORTED: c++98, c++03, c++11, c++14

// template <class InputIterator1, class T,
//           class BinaryOperation, class UnaryOperation>
//    T transform_reduce(InputIterator1 first1, InputIterator1 last1,
//                       T init, BinaryOperation binary_op, UnaryOperation unary_op);
//

#include <numeric>
#include <cassert>

#include "test_iterators.h"

template <class _Tp = void>
struct identity : std::unary_function<_Tp, _Tp>
{
    constexpr const _Tp& operator()(const _Tp& __x) const { return __x;}
};

template <>
struct identity<void>
{
    template <class _Tp>
    constexpr auto operator()(_Tp&& __x) const
    _NOEXCEPT_(noexcept(_VSTD::forward<_Tp>(__x)))
    -> decltype        (_VSTD::forward<_Tp>(__x))
        { return        _VSTD::forward<_Tp>(__x); }
};


template <class _Tp = void>
struct twice
{
    constexpr const _Tp operator()(const _Tp& __x) const noexcept { return 2 * __x; }
};

template <>
struct twice<void>
{
    template <class _Tp>
    constexpr auto operator()(const _Tp& __x) const
    _NOEXCEPT_(noexcept(2 * __x))
    -> decltype        (2 * __x)
        { return        2 * __x; }
};

template <class Iter1, class T, class BOp, class UOp>
void
test(Iter1 first1, Iter1 last1, T init, BOp bOp, UOp uOp, T x)
{
    static_assert( std::is_same_v<T,
                    decltype(std::transform_reduce(first1, last1, init, bOp, uOp))> );
    assert(std::transform_reduce(first1, last1, init, bOp, uOp) == x);
}

template <class Iter>
void
test()
{
    int ia[]          = {1, 2, 3, 4, 5, 6};
    unsigned sa = sizeof(ia) / sizeof(ia[0]);

    test(Iter(ia), Iter(ia),    0, std::plus<>(),       identity<>(),       0);
    test(Iter(ia), Iter(ia),    1, std::multiplies<>(), identity<>(),       1);
    test(Iter(ia), Iter(ia+1),  0, std::multiplies<>(), identity<>(),       0);
    test(Iter(ia), Iter(ia+1),  2, std::plus<>(),       identity<>(),       3);
    test(Iter(ia), Iter(ia+2),  0, std::plus<>(),       identity<>(),       3);
    test(Iter(ia), Iter(ia+2),  3, std::multiplies<>(), identity<>(),       6);
    test(Iter(ia), Iter(ia+sa), 4, std::multiplies<>(), identity<>(),    2880);
    test(Iter(ia), Iter(ia+sa), 4, std::plus<>(),       identity<>(),      25);

    test(Iter(ia), Iter(ia),    0, std::plus<>(),       twice<>(),       0);
    test(Iter(ia), Iter(ia),    1, std::multiplies<>(), twice<>(),       1);
    test(Iter(ia), Iter(ia+1),  0, std::multiplies<>(), twice<>(),       0);
    test(Iter(ia), Iter(ia+1),  2, std::plus<>(),       twice<>(),       4);
    test(Iter(ia), Iter(ia+2),  0, std::plus<>(),       twice<>(),       6);
    test(Iter(ia), Iter(ia+2),  3, std::multiplies<>(), twice<>(),      24);
    test(Iter(ia), Iter(ia+sa), 4, std::multiplies<>(), twice<>(),  184320); // 64 * 2880
    test(Iter(ia), Iter(ia+sa), 4, std::plus<>(),       twice<>(),      46);
}

template <typename T, typename Init>
void test_return_type()
{
    T *p = nullptr;
    static_assert( std::is_same_v<Init,
         decltype(std::transform_reduce(p, p, Init{}, std::plus<>(), identity<>()))> );
}

int main()
{
    test_return_type<char, int>();
    test_return_type<int, int>();
    test_return_type<int, unsigned long>();
    test_return_type<float, int>();
    test_return_type<short, float>();
    test_return_type<double, char>();
    test_return_type<char, double>();

//  All the iterator categories
    test<input_iterator        <const int*> >();
    test<forward_iterator      <const int*> >();
    test<bidirectional_iterator<const int*> >();
    test<random_access_iterator<const int*> >();
    test<const int*>();
    test<      int*>();

//  Make sure the math is done using the correct type
    {
    auto v = {1, 2, 3, 4, 5, 6};
    unsigned res = std::transform_reduce(v.begin(), v.end(), 1U, std::multiplies<>(), twice<>());
    assert(res == 46080);       // 6! * 64 will not fit into a char
    }
}
