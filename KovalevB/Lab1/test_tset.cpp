#include <gtest/gtest.h>
#include "tset.h"

TEST(TSetTest, can_create_set_with_positive_length) {
    EXPECT_NO_THROW(TSet s(15));
}

TEST(TSetTest, can_insert_and_check_element) {
    TSet s(10);
    s.InsElem(4);
    EXPECT_EQ(s.IsMember(4), 1);
    EXPECT_EQ(s.IsMember(5), 0);
}

TEST(TSetTest, can_remove_element) {
    TSet s(10);
    s.InsElem(4);
    s.DelElem(4);
    EXPECT_EQ(s.IsMember(4), 0);
}

TEST(TSetTest, throws_when_insert_out_of_bounds_element) {
    TSet s(10);
    EXPECT_THROW(s.InsElem(-1), std::out_of_range);
    EXPECT_THROW(s.InsElem(10), std::out_of_range);
}

TEST(TSetTest, can_union_element) {
    TSet s(10);
    TSet res = s + 5;
    EXPECT_EQ(res.IsMember(5), 1);
}

TEST(TSetTest, can_subtract_element) {
    TSet s(10);
    s.InsElem(5);
    TSet res = s - 5;
    EXPECT_EQ(res.IsMember(5), 0);
}

TEST(TSetTest, can_union_two_sets) {
    TSet s1(10), s2(15);
    s1.InsElem(2);
    s2.InsElem(12);
    TSet s3 = s1 + s2;
    
    EXPECT_EQ(s3.GetMaxPower(), 15);
    EXPECT_EQ(s3.IsMember(2), 1);
    EXPECT_EQ(s3.IsMember(12), 1);
}

TEST(TSetTest, can_intersect_two_sets) {
    TSet s1(10), s2(15);
    s1.InsElem(2);
    s1.InsElem(5);
    s2.InsElem(5);
    s2.InsElem(12);
    
    TSet s3 = s1 * s2;
    
    EXPECT_EQ(s3.IsMember(5), 1);
    EXPECT_EQ(s3.IsMember(2), 0);
    EXPECT_EQ(s3.IsMember(12), 0);
}

TEST(TSetTest, can_complement_set) {
    TSet s(5);
    s.InsElem(2);
    TSet inv = ~s;
    
    EXPECT_EQ(inv.IsMember(0), 1);
    EXPECT_EQ(inv.IsMember(1), 1);
    EXPECT_EQ(inv.IsMember(2), 0);
    EXPECT_EQ(inv.IsMember(3), 1);
    EXPECT_EQ(inv.IsMember(4), 1);
}