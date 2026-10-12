#include <gtest/gtest.h>
#include "tbitfield.h"
#include <stdexcept>

TEST(TBitFieldTest, can_create_bitfield_with_positive_length) {
    EXPECT_NO_THROW(TBitField bf(10));
}

TEST(TBitFieldTest, throws_when_create_bitfield_with_negative_length) {
    EXPECT_THROW(TBitField bf(-10), std::invalid_argument); 
}

TEST(TBitFieldTest, can_copy_bitfield) {
    TBitField bf1(10);
    bf1.SetBit(3);
    TBitField bf2(bf1);
    EXPECT_EQ(bf1, bf2);
}

TEST(TBitFieldTest, can_assign_bitfields_of_different_sizes) {
    TBitField bf1(10), bf2(20);
    bf1.SetBit(3);
    bf2 = bf1;
    EXPECT_EQ(bf1, bf2);
    EXPECT_EQ(bf2.GetLength(), 10);
}

TEST(TBitFieldTest, can_set_and_get_bit) {
    TBitField bf(10);
    bf.SetBit(5);
    EXPECT_EQ(bf.GetBit(5), 1);
}

TEST(TBitFieldTest, can_clear_bit) {
    TBitField bf(10);
    bf.SetBit(3);
    bf.ClrBit(3);
    EXPECT_EQ(bf.GetBit(3), 0);
}

TEST(TBitFieldTest, throws_when_access_out_of_bounds) {
    TBitField bf(10);
    EXPECT_THROW(bf.SetBit(-1), std::out_of_range); 
    EXPECT_THROW(bf.GetBit(10), std::out_of_range); 
    EXPECT_THROW(bf.ClrBit(100), std::out_of_range);
}

TEST(TBitFieldTest, can_apply_bitwise_OR_with_different_sizes) {
    TBitField bf1(10), bf2(20);
    bf1.SetBit(5);
    bf2.SetBit(15);
    TBitField bf3 = bf1 | bf2;
    
    EXPECT_EQ(bf3.GetLength(), 20);
    EXPECT_EQ(bf3.GetBit(5), 1);
    EXPECT_EQ(bf3.GetBit(15), 1);
}

TEST(TBitFieldTest, can_apply_bitwise_AND_with_different_sizes) {
    TBitField bf1(10), bf2(20);
    bf1.SetBit(5);
    bf1.SetBit(2);
    bf2.SetBit(5);
    bf2.SetBit(15);
    
    TBitField bf3 = bf1 & bf2;
    
    EXPECT_EQ(bf3.GetLength(), 20);
    EXPECT_EQ(bf3.GetBit(5), 1);
    EXPECT_EQ(bf3.GetBit(2), 0);
    EXPECT_EQ(bf3.GetBit(15), 0);
}

TEST(TBitFieldTest, can_apply_bitwise_NOT_and_clear_tail) {
    TBitField bf(35);
    TBitField inv = ~bf;
    
    EXPECT_EQ(inv.GetBit(0), 1);
    EXPECT_EQ(inv.GetBit(34), 1);
    
    TBitField double_inv = ~inv;
    EXPECT_EQ(bf, double_inv);
}