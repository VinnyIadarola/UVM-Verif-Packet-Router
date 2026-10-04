#pragma once

enum TestFail {
    DUPLICATE_PACKET,
    PACKET_NOT_FOUND,
    DATA_MISMATCH
};

void fail(TestFail f);
