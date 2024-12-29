#include "BloomFilter.h"
#include <iostream>

BloomFilter::BloomFilter(size_t size, size_t numHashes)
    : m_size(size), m_numHashes(numHashes) {}

void BloomFilter::add(const std::string& item) {
    // std::cout << "Adding to BloomFilter: " << item << std::endl; // Debug print
    for (size_t i = 0; i < m_numHashes; ++i) {
        m_bits[hash(item, i) % m_size] = true;
    }
}

bool BloomFilter::contains(const std::string& item) const {
    // std::cout << "Checking BloomFilter for: " << item << std::endl; // Debug print
    for (size_t i = 0; i < m_numHashes; ++i) {
        if (!m_bits[hash(item, i) % m_size]) {
            return false;
        }
    }
    return true;
}

size_t BloomFilter::hash(const std::string& item, size_t i) const {
    std::hash<std::string> hashFn;
    return hashFn(item + std::to_string(i));
}