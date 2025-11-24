#ifndef NS_TRANSPORT_H
#define NS_TRANSPORT_H

#include <stdint.h>
#include <stddef.h>

class ITransport {
public:
    virtual int available() = 0;
    virtual uint8_t read() = 0;
    virtual uint32_t write(const uint8_t* data, size_t len) = 0;
    virtual void flush() {}
    virtual void drain() {}
    virtual bool connected() {
        return true;
    }
};

#endif // NS_TRANSPORT_H
