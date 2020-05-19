#include "FeeCalculator.h"

#include <iostream>

using namespace TW;

namespace TW::Bitcoin {

DefaultFeeCalculator DefaultFeeCalculator::instance;

int64_t DefaultFeeCalculator::calculate(int64_t inputs, int64_t outputs, int64_t byteFee, char prefix, int witnessProgramSize) const {
    const auto txsize = ((148 * inputs) + (34 * outputs) + 10);
    auto txsize2 = txsize;
    if (witnessProgramSize > 0) {
        txsize2 = txsize - (witnessProgramSize*3)/4;
    }
    std::cerr << "QQQ calculateFee " << witnessProgramSize << " " << prefix << " " << inputs << " " << outputs << " txsize " << txsize2 << " " << txsize << "\n";
    return int64_t(txsize) * byteFee;
}

int64_t DefaultFeeCalculator::calculateSingleInput(int64_t byteFee) const {
    return int64_t(148) * byteFee;
}

class ZCashFeeCalculator : public FeeCalculator {
public:
    int64_t calculate(int64_t inputs, int64_t outputs = 2, int64_t byteFee = 1, char prefix = '?', int witnessProgramSize = 0) const override {
        return 10000;
    }

    int64_t calculateSingleInput(int64_t byteFee) const override {
        return 0;
    }
};

class GroestlcoinFeeCalculator : public FeeCalculator {
public:
    int64_t calculate(int64_t inputs, int64_t outputs = 2, int64_t byteFee = 1, char prefix = '?', int witnessProgramSize = 0) const override {
        return 20000;
    }

    int64_t calculateSingleInput(int64_t byteFee) const override {
        return 0;
    }
};

class DecredFeeCalculator : public FeeCalculator {
public:
    int64_t calculate(int64_t inputs, int64_t outputs = 2, int64_t byteFee = 1, char prefix = '?', int witnessProgramSize = 0) const override {
        const auto txsize = ((166 * inputs) + (38 * outputs) + 12);
        return int64_t(txsize) * byteFee;
    }

    int64_t calculateSingleInput(int64_t byteFee) const override {
        return int64_t(166) * byteFee;
    }
};

DefaultFeeCalculator defaultFeeCalculator;
ZCashFeeCalculator zcashFeeCalculator;
GroestlcoinFeeCalculator groestlcoinFeeCalculator;
DecredFeeCalculator decredFeeCalculator;

FeeCalculator& getFeeCalculator(TWCoinType coinType) {
    switch (coinType) {
    case TWCoinTypeZelcash:
    case TWCoinTypeZcash:
        return zcashFeeCalculator;

    case TWCoinTypeGroestlcoin:
        return groestlcoinFeeCalculator;

    case TWCoinTypeDecred:
        return decredFeeCalculator;

    default:
        return defaultFeeCalculator;
    }
}

} // namespace TW::Bitcoin
