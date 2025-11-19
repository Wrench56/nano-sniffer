#ifndef NS_UTILITY_H
#define NS_UTILITY_H

#include <Arduino.h>
#include <ArduinoBLE.h>

#include <stdint.h>

template <size_t N>
struct Msg {
    uint8_t data[N];
};

template <size_t N>
constexpr Msg<N> make_msg(const char (&str)[N]) {
    Msg<N> msg{};
    msg.data[0] = static_cast<uint8_t>(N - 1);
    for (size_t i = 1; i < N; ++i) {
        msg.data[i] = static_cast<uint8_t>(str[i - 1]);
    }
    return msg;
}

#define GIO_WRITE(GIO, STRING) \
    do { \
        static constexpr auto msg = make_msg(STRING); \
        GIO->write(msg.data, msg.data[0] + 1); \
    } while (0);

#endif // NS_UTILITY_H
