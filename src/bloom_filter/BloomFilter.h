#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <bitset>
#include <string>
#include <vector>
#include <functional>

class BloomFilter {
public:
    BloomFilter(size_t size, size_t numHashes);
    void add(const std::string& item);
    bool contains(const std::string& item) const;

private:
    size_t hash(const std::string& item, size_t i) const;
    size_t m_size;
    size_t m_numHashes;
    std::bitset<1000> m_bits; // Adjust size as needed
};

#endif // BLOOM_FILTER_H