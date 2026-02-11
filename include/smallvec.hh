#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <iostream>

static constexpr int VEC_DEFAULT_SIZE = 256;

class SmallVec {
    public:
        SmallVec()
            : buffer(
                malloc(VEC_DEFAULT_SIZE)
            ),
            capacity(VEC_DEFAULT_SIZE) {}
        explicit SmallVec(std::size_t size)
            : buffer(
                malloc(size)
            ),
            capacity(size) {}
        explicit SmallVec(std::size_t size, void* ptr)
            : cur_size(size),
            buffer(
                malloc(size)
            ),
            capacity(size) {
                if (size > 0) memcpy(buffer, ptr, size);
                else if (size < 0) {
                    std::cerr << "Invalid construction called";
                    std::abort();
                }
            }
        ~SmallVec() {
            if (buffer) free(buffer);
        }
        SmallVec(SmallVec&& other)
            : cur_size(
                std::exchange(other.cur_size, 0)
            ),
            capacity(
                std::exchange(other.capacity, 0)
            ) {
                buffer = other.buffer;
                other.buffer = nullptr;
            }
        SmallVec(const SmallVec& other)
            : SmallVec(
                other.cur_size,
                other.buffer
            ) {}
        SmallVec& operator=(SmallVec&& other) {
            if (this == &other) return *this;
            if (buffer) free(buffer);
            cur_size = other.cur_size;
            capacity = other.capacity;
            buffer = other.buffer;
            other.capacity = other.cur_size = 0;
            other.buffer = nullptr;
            return *this;
        }
        SmallVec& operator=(const SmallVec& other) {
            if (this == &other) return *this;
            void* new_buffer = malloc(other.capacity);
            if (!new_buffer) {
                std::cerr << "Copy buffer failed to allocate";
                std::abort();
            }
            memcpy(new_buffer, other.buffer, other.cur_size);
            if (buffer) free(buffer);
            cur_size = other.cur_size;
            capacity = other.capacity;
            buffer = new_buffer;
            return *this;
        }
        uint8_t& operator[](std::size_t index) {
            if (index >= cur_size) {
                std::cerr << "Index out of bounds.";
                std::abort();
            }
            return static_cast<uint8_t*>(buffer)[index];
        }
        const uint8_t& operator[](std::size_t index) const {
            if (index >= cur_size) {
                std::cerr << "Index out of bounds.";
                std::abort();
            }
            return static_cast<const uint8_t*>(buffer)[index];
        }
        void debug_assert() {
            if (capacity <= 0) {
                std::cerr << "Invalid Capacity : " << (int) capacity;
                std::abort();
            } if (capacity < cur_size) {
                std::cerr
                    << "Capacity exceeded : [Current size] "
                    << (int) cur_size
                    << " [Capacity] "
                    << (int) capacity;
                std::abort();
            }
        }
        void reserve(std::size_t new_size) {
            if (capacity == new_size) return;
            if (buffer == nullptr) buffer = malloc(new_size);
            else buffer = realloc(buffer, new_size);
            if (!buffer) {
                std::cerr << "Buffer failed to extend.";
                std::abort();
            }
            capacity = new_size;
        }
        void push_back(uint8_t byte) {
            if (cur_size == capacity)
                this->reserve(capacity ? capacity * 2 : 1);
            uint8_t* cast_buffer = (uint8_t*) buffer;
            cast_buffer[cur_size++] = byte;
        }
        void pop_back() {
            if (cur_size == 0) return;
            uint8_t* cast_buffer = (uint8_t*) buffer;
            cur_size--;
        }
    private:
        std::size_t cur_size = 0;
        std::size_t capacity = 0;
        void* buffer = nullptr;
};