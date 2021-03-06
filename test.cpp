#include "histogram.h"
#include "svg.h"
#include <cassert>

void
test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void test_negative()
{
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}
void test_same()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}
void test_onenum()
{
    double min = 0;
    double max = 0;
    find_minmax({110.5}, min, max);
    assert(min == 110.5);
    assert(max == 110.5);
}
void test_emptymassif()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}
void test_color()
{
    vector <size_t> bins={2,4,6};
    assert(color_bins(bins, 6, bins[0])=="999");
    assert(color_bins(bins, 6, bins[1])=="444");
    assert(color_bins(bins, 6, bins[2])=="111");
}
int
main()
{
    test_positive();
    test_negative();
    test_same();
    test_onenum();
    test_emptymassif();
    test_color();

}
