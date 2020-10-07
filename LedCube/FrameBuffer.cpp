#include "FrameBuffer.h"

namespace geometricFunc {
    const float GetYForLine(float x, float x1, float y1, float x2, float y2) {
        return (((y2-y1)/(x2-x1))*(x-x1))+y1;
    }
}

FrameBuffer::FrameBuffer() {
    std::bitset<NUMBER_OF_PIXELS_PER_LAYER> tmp_bitset;
    for (size_t layer = 0; layer < NUMBER_OF_LAYERS ; layer++){
        pixels.push_back(tmp_bitset);
    }
}

std::vector<uint8_t> FrameBuffer::TranslateLayerFromBitset(uint8_t layer) const {
    std::vector<uint8_t> out_vec;
    // out_vec.push_back(1 << layer);
    // uint8_t tmp_byte = 0;

    // for(size_t i = 0; i < NUMBER_OF_PIXELS_PER_LAYER; i++) {
    //     if(i == NUMBER_OF_PIXELS_PER_LAYER - 1){
    //         tmp_byte = tmp_byte | pixels[layer][i];
    //         out_vec.push_back(tmp_byte);
    //     }
    //     else if (i != 0 && i % 8 == 0){
    //         out_vec.push_back(tmp_byte);
    //         tmp_byte = pixels[layer][i] << 7;
    //     } else {
    //         tmp_byte = tmp_byte | pixels[layer][i] << (7-(i % 8)); 
    //     } 
    // }

    std::bitset<16> mask(0xFF);

    for (uint8_t blockIndex = 0; blockIndex < NUMBER_OF_PIXELS_PER_LAYER / 8; blockIndex++){
        out_vec.push_back(((pixels[layer] >> (8 * blockIndex)) & mask).to_ulong());
    }
    out_vec.push_back(1 << (layer + 4));

    return out_vec;
}

void FrameBuffer::setPixel(bool new_state, uint8_t x, uint8_t y, uint8_t z) {
    uint8_t bit_location = y * NUMBER_OF_PIXELS_PER_AXIS + x;
    pixels[z][bit_location] = new_state;
}

void FrameBuffer::setPixelByIndex(bool new_state, uint8_t index, uint8_t layer) {
    pixels[layer][index] = new_state;
}

void FrameBuffer::setHorizontalLayer(bool new_state, uint8_t layer) {
    for(size_t i = 0; i < NUMBER_OF_PIXELS_PER_LAYER; i++){
        pixels[layer][i] = new_state;
    }
}

void FrameBuffer::draw2DLine(bool new_state, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t z) {
    if (x2-x1 > y2-y1){
        for(uint8_t x = x1; x <= x2; x++){
            float y = geometricFunc::GetYForLine(x, x1, y1, x2, y2);
            uint8_t rounded_y = round(y);
            setPixel(new_state, x, rounded_y, z);
        }
    }
    else{
        for(uint8_t y = y1; y <= y2; y++){
            float x = geometricFunc::GetYForLine(y, y1, x1, y2, x2);
            uint8_t rounded_x = round(x);
            setPixel(new_state, rounded_x, y, z);
        }
    }
}

void FrameBuffer::setAll(bool new_state) {
    std::bitset<NUMBER_OF_PIXELS_PER_LAYER> tmp_bitset;
    for (size_t layer = 0; layer < NUMBER_OF_LAYERS ; layer++){
        pixels[layer] = tmp_bitset;
    }
}

void FrameBuffer::clear() {
    setAll(false);
}