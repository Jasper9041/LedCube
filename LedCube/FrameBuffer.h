#ifndef FrameBuffer_H
#define FrameBuffer_H

#include <bitset>
#include <vector>
#include <cmath>

const uint8_t NUMBER_OF_LAYERS = 4;
const uint8_t NUMBER_OF_PIXELS_PER_LAYER = 16;
const uint8_t NUMBER_OF_PIXELS_PER_AXIS = 4;

class FrameBuffer {
    public:
        FrameBuffer();
        std::vector<uint8_t> TranslateLayerFromBitset(uint8_t layer) const;

        void clear();
        void setAll(bool new_state);
        void setPixel(bool new_state, uint8_t x, uint8_t y, uint8_t z);
        void setPixelByIndex(bool new_state, uint8_t index, uint8_t layer);
        void setHorizontalLayer(bool new_state, uint8_t layer);
        void drawLine(bool new_state, uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2, bool readyToDraw=false);
        // void FrameBuffer::setPlane(bool new_state, std::vector<uint8_t> line1_start, std::vector<uint8_t> line1_end,
        //                                     std::vector<uint8_t> line2_start);
    private:
        std::vector<std::bitset<NUMBER_OF_PIXELS_PER_LAYER>> pixels;
};

#endif