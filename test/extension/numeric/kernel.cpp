//
// Copyright 2019 Mateusz Loskot <mateusz at loskot dot net>
// Copyright 2019 Miral Shah <miralshah2211@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#define BOOST_DISABLE_ASSERTS 1 // kernel_1d_adaptor assertions are too strict
#include <boost/gil.hpp>
#include <boost/gil/extension/numeric/kernel.hpp>

#include <boost/core/lightweight_test.hpp>

#include <vector>

namespace gil = boost::gil;

void test_kernel_1d_default_constructor()
{
    gil::kernel_1d<int> k;
    BOOST_TEST(k.center() == 0);
    BOOST_TEST(k.left_size() == 0);
    BOOST_TEST(static_cast<int>(k.right_size()) == -1);
    // std::vector interface
    BOOST_TEST(k.size() == 0);
}

void test_kernel_2d_default_constructor()
{
    gil::detail::kernel_2d<int> k;
    BOOST_TEST(k.center_y() == 0);
    BOOST_TEST(k.center_x() == 0);

    //BOOST_TEST(k.left_size() == 0);
    //BOOST_TEST(k.right_size() == -1);
    BOOST_TEST(k.upper_size() == 0);
    BOOST_TEST(static_cast<int>(k.lower_size()) == -1);
    // std::vector interface
    BOOST_TEST(k.size() == 0);
}

void test_kernel_1d_parameterized_constructor()
{
    gil::kernel_1d<int> k(9, 4);
    BOOST_TEST(k.center() == 4);
    BOOST_TEST(k.left_size() == 4);
    BOOST_TEST(k.right_size() == 4);
    // std::vector interface
    BOOST_TEST(k.size() == 9);
}

void test_kernel_2d_parameterized_constructor()
{
    gil::detail::kernel_2d<int> k(9, 4, 4);
    BOOST_TEST(k.center_y() == 4);
    BOOST_TEST(k.center_x() == 4);
    BOOST_TEST(k.left_size() == 4);
    BOOST_TEST(k.right_size() == 4);
    BOOST_TEST(k.upper_size() == 4);
    BOOST_TEST(k.lower_size() == 4);
    // std::vector interface
    BOOST_TEST(k.size() == 9);
}

void test_kernel_1d_parameterized_constructor_with_iterator()
{
    std::vector<int> v(9);
    gil::kernel_1d<int> k(v.cbegin(), v.size(), 4);
    BOOST_TEST(k.center() == 4);
    BOOST_TEST(k.left_size() == 4);
    BOOST_TEST(k.right_size() == 4);
    // std::vector interface
    BOOST_TEST(k.size() == 9);
}

void test_kernel_2d_parameterized_constructor_with_iterator()
{
    std::vector<int> v(81);
    gil::detail::kernel_2d<int> k(v.cbegin(), v.size(), 4, 4);
    BOOST_TEST(k.center_y() == 4);
    BOOST_TEST(k.center_x() == 4);
    BOOST_TEST(k.left_size() == 4);
    BOOST_TEST(k.right_size() == 4);
    BOOST_TEST(k.upper_size() == 4);
    BOOST_TEST(k.lower_size() == 4);
    // std::vector interface
    BOOST_TEST(k.size() == 9);
}

void test_kernel_1d_copy_constructor()
{
    gil::kernel_1d<int> d(9, 4);
    gil::kernel_1d<int> k(d);
    BOOST_TEST(k.center() == 4);
    BOOST_TEST(k.center() == d.center());
    BOOST_TEST(k.left_size() == d.left_size());
    BOOST_TEST(k.right_size() == d.right_size());
    // std::vector interface
    BOOST_TEST(k.size() == d.size());
}

void test_kernel_2d_copy_constructor()
{
    gil::detail::kernel_2d<int> d(9, 4, 4);
    gil::detail::kernel_2d<int> k(d);
    BOOST_TEST(k.center_y() == 4);
    BOOST_TEST(k.center_x() == 4);
    BOOST_TEST(k.center_y() == d.center_y());
    BOOST_TEST(k.center_x() == d.center_x());
    BOOST_TEST(k.left_size() == d.left_size());
    BOOST_TEST(k.right_size() == d.right_size());
    BOOST_TEST(k.lower_size() == d.lower_size());
    BOOST_TEST(k.upper_size() == d.upper_size());
    // std::vector interface
    BOOST_TEST(k.size() == d.size());
}

void test_kernel_1d_assignment_operator()
{
    gil::kernel_1d<int> d(9, 4);
    gil::kernel_1d<int> k;
    k = d;
    BOOST_TEST(k.center() == 4);
    BOOST_TEST(k.center() == d.center());
    BOOST_TEST(k.left_size() == d.left_size());
    BOOST_TEST(k.right_size() == d.right_size());
    // std::vector interface
    BOOST_TEST(k.size() == d.size());
}

void test_kernel_2d_assignment_operator()
{
    gil::detail::kernel_2d<int> d(9, 4, 4);
    gil::detail::kernel_2d<int> k;
    k = d;
    BOOST_TEST(k.center_y() == 4);
    BOOST_TEST(k.center_x() == 4);
    BOOST_TEST(k.center_y() == d.center_y());
    BOOST_TEST(k.center_x() == d.center_x());
    BOOST_TEST(k.left_size() == d.left_size());
    BOOST_TEST(k.right_size() == d.right_size());
    BOOST_TEST(k.lower_size() == d.lower_size());
    BOOST_TEST(k.upper_size() == d.upper_size());
    // std::vector interface
    BOOST_TEST(k.size() == d.size());
}

void test_kernel_1d_reverse_kernel()
{
    gil::kernel_1d<int> d(12, 4);
    BOOST_TEST(d.center() == 4);
    auto k = gil::reverse_kernel(d);
    BOOST_TEST(k.center() == d.right_size());
    // std::vector interface
    BOOST_TEST(k.size() == d.size());
}

int main()
{
    test_kernel_1d_default_constructor();
    test_kernel_2d_default_constructor();
    test_kernel_1d_parameterized_constructor();
    test_kernel_2d_parameterized_constructor();
    test_kernel_1d_parameterized_constructor_with_iterator();
    test_kernel_2d_parameterized_constructor_with_iterator();
    test_kernel_1d_copy_constructor();
    test_kernel_2d_copy_constructor();
    test_kernel_1d_assignment_operator();
    test_kernel_2d_assignment_operator();
    test_kernel_1d_reverse_kernel();

    return ::boost::report_errors();
}
