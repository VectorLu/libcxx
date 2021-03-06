//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// UNSUPPORTED: c++03, c++11, c++14, c++17

// <chrono>
// class year_month_weekday;

// constexpr year_month_weekday& operator+=(const years& d) noexcept;
// constexpr year_month_weekday& operator-=(const years& d) noexcept;

#include <chrono>
#include <type_traits>
#include <cassert>

#include "test_macros.h"

template <typename D, typename Ds>
constexpr bool testConstexpr(D d1)
{
    if (static_cast<int>((d1          ).year()) !=  1) return false;
    if (static_cast<int>((d1 += Ds{ 1}).year()) !=  2) return false;
    if (static_cast<int>((d1 += Ds{ 2}).year()) !=  4) return false;
    if (static_cast<int>((d1 += Ds{12}).year()) != 16) return false;
    if (static_cast<int>((d1 -= Ds{ 1}).year()) != 15) return false;
    if (static_cast<int>((d1 -= Ds{ 2}).year()) != 13) return false;
    if (static_cast<int>((d1 -= Ds{12}).year()) !=  1) return false;
    return true;
}

int main()
{
    using year               = std::chrono::year;
    using month              = std::chrono::month;
    using day                = std::chrono::day;
    using weekday            = std::chrono::weekday;
    using weekday_indexed    = std::chrono::weekday_indexed;
    using year_month_weekday = std::chrono::year_month_weekday;
    using years              = std::chrono::years;
    using months             = std::chrono::months;

    ASSERT_NOEXCEPT(                               std::declval<year_month_weekday&>() += std::declval<years>());
    ASSERT_SAME_TYPE(year_month_weekday&, decltype(std::declval<year_month_weekday&>() += std::declval<years>()));

    ASSERT_NOEXCEPT(                               std::declval<year_month_weekday&>() -= std::declval<years>());
    ASSERT_SAME_TYPE(year_month_weekday&, decltype(std::declval<year_month_weekday&>() -= std::declval<years>()));
    
    constexpr weekday Tuesday = std::chrono::Tuesday;
    constexpr month January = std::chrono::January;

    static_assert(testConstexpr<year_month_weekday, years>(year_month_weekday{year{1}, January, weekday_indexed{Tuesday, 2}}), "");

    for (int i = 1000; i <= 1010; ++i)
    {
        year_month_weekday ymwd(year{i}, January, weekday_indexed{Tuesday, 2});

        assert(static_cast<int>((ymwd += years{2}).year()) == i + 2);
        assert(ymwd.month()    == January);
        assert(ymwd.weekday()  == Tuesday);
        assert(ymwd.index()    == 2);

        assert(static_cast<int>((ymwd            ).year()) == i + 2);
        assert(ymwd.month()    == January);
        assert(ymwd.weekday()  == Tuesday);
        assert(ymwd.index()    == 2);

        assert(static_cast<int>((ymwd -= years{1}).year()) == i + 1);
        assert(ymwd.month()    == January);
        assert(ymwd.weekday()  == Tuesday);
        assert(ymwd.index()    == 2);

        assert(static_cast<int>((ymwd            ).year()) == i + 1);
        assert(ymwd.month()    == January);
        assert(ymwd.weekday()  == Tuesday);
        assert(ymwd.index()    == 2);
    }
}
