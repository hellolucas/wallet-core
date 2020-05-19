// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Bitcoin/FeeCalculator.h"

#include <gtest/gtest.h>

using namespace TW;
using namespace TW::Bitcoin;

TEST(BitcoinFeeCalculator, calculate) {
    FeeCalculator& feeCalculator = getFeeCalculator(TWCoinTypeBitcoin);
    EXPECT_EQ(feeCalculator.calculate(1, 2, 1, 't', 0), 226);
    EXPECT_EQ(feeCalculator.calculate(1, 1, 1, 't', 0), 192);
    EXPECT_EQ(feeCalculator.calculate(0, 2, 1, 't', 0), 78);
    EXPECT_EQ(feeCalculator.calculate(1, 0, 1, 't', 0), 158);
    EXPECT_EQ(feeCalculator.calculate(0, 0, 1, 't', 0), 10);
    EXPECT_EQ(feeCalculator.calculate(1, 2, 10, 't', 0), 2260);
}

TEST(BitcoinDefaultFeeCalculator, calculate) {
    DefaultFeeCalculator defaultFeeCalculator;
    EXPECT_EQ(defaultFeeCalculator.calculate(1, 2, 1, 't', 0), 226);
    EXPECT_EQ(defaultFeeCalculator.calculate(1, 1, 1, 't', 0), 192);
    EXPECT_EQ(defaultFeeCalculator.calculate(0, 2, 1, 't', 0), 78);
    EXPECT_EQ(defaultFeeCalculator.calculate(1, 0, 1, 't', 0), 158);
    EXPECT_EQ(defaultFeeCalculator.calculate(0, 0, 1, 't', 0), 10);
    EXPECT_EQ(defaultFeeCalculator.calculate(1, 2, 10, 't', 0), 2260);
}

TEST(BitcoinDefaultFeeCalculator, calculateSingleInput) {
    DefaultFeeCalculator defaultFeeCalculator;
    EXPECT_EQ(defaultFeeCalculator.calculateSingleInput(1), 148);
    EXPECT_EQ(defaultFeeCalculator.calculateSingleInput(2), 296);
    EXPECT_EQ(defaultFeeCalculator.calculateSingleInput(10), 1480);
}
