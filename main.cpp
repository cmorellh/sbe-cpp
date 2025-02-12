#include <iostream>
#include <string>
#include "trading/NewOrder.h"
#include "trading/MessageHeader.h"

using namespace trading;

class OrderEncoder {
private:
    char* buffer_;
    std::uint64_t bufferLength_;
    MessageHeader messageHeader_;
    NewOrder newOrder_;

public:
    OrderEncoder(char* buffer, std::uint64_t length) 
        : buffer_(buffer)
        , bufferLength_(length)
    {
        messageHeader_.wrap(buffer, 0, NewOrder::sbeSchemaVersion(), bufferLength_);
    }

    void encode(
        std::int64_t orderId,
        const std::string& symbol,
        std::int32_t price,
        std::int32_t quantity,
        Side::Value side)  // Changed from Side to Side::Value
    {
        messageHeader_.blockLength(NewOrder::sbeBlockLength())
                     .templateId(NewOrder::sbeTemplateId())
                     .schemaId(NewOrder::sbeSchemaId())
                     .version(NewOrder::sbeSchemaVersion());

        newOrder_.wrapForEncode(buffer_, messageHeader_.encodedLength(), bufferLength_)
                .orderId(orderId)
                .price(price)
                .quantity(quantity)
                .side(side);

        // Use the string version of putSymbol
        newOrder_.putSymbol(symbol);
    }

    std::uint64_t encodedLength() const
    {
        return messageHeader_.encodedLength() + newOrder_.sbeBlockLength();
    }
};

int main()
{
    // Allocate buffer
    const std::uint64_t bufferLength = 1024;
    char buffer[bufferLength];

    // Create encoder
    OrderEncoder encoder(buffer, bufferLength);

    // Encode an order
    encoder.encode(
        12345,           // orderId
        "AAPL",         // symbol
        15000,          // price (150.00)
        100,            // quantity
        Side::Value::Buy  // Changed to Side::Value::BUY
    );

    std::cout << "Message encoded, length = " << encoder.encodedLength() << " bytes\n";

    return 0;
}