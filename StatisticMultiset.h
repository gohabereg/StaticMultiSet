#pragma once
#include <set>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>

template<class T>
class StatisticMultiset {

public:

    StatisticMultiset() = default;
    ~StatisticMultiset() = default;

    void add(const T& num);
    void add(const std::vector<T>& numbers);
    void add(const std::multiset<T>& numbers);
    void add(const std::list<T>& numbers);
    void add(const StatisticMultiset& numbers);
    void addFromFile(const std::string& filename);

    T max() const;
    T min() const;
    float avg() const;

    int lessThan(float threshold) const;
    int greaterThan(float threshold) const;

private:
    std::multiset<T> set;

    mutable std::pair<T, bool> lastMax, lastMin;
    mutable std::pair<float, bool> lastAvg;
    mutable std::map<float, std::pair<T, bool>> lastLessThan, lastGreaterThan;

    void setUpdated() const;

};


template<class T>
void StatisticMultiset<T>::add(const T &num) {

    this->setUpdated();
    this->set.insert(num);

}

template<class T>
void StatisticMultiset<T>::add(const std::vector<T> &numbers) {

    this->setUpdated();
    this->set.insert(numbers.begin(), numbers.end());

}

template<class T>
void StatisticMultiset<T>::add(const std::multiset<T> &numbers) {

    this->setUpdated();
    this->set.insert(numbers.begin(), numbers.end());

}

template<class T>
void StatisticMultiset<T>::add(const std::list<T> &numbers) {

    this->setUpdated();
    this->set.insert(numbers.begin(), numbers.end());

}

template<class T>
void StatisticMultiset<T>::add(const StatisticMultiset<T> &numbers) {

    this->add(numbers.set);

}

/** Reading only int and floats value from file supported **/
template <>
void StatisticMultiset<int>::addFromFile(const std::string &filename) {

    this->setUpdated();

    std::ifstream ifs;
    std::string line;

    ifs.open(filename, std::ifstream::in);

    while (ifs.good()) {
        std::getline(ifs, line);

        int num = std::stoi(line);
        this->add(num);

    }

    ifs.close();

}

template <>
void StatisticMultiset<float>::addFromFile(const std::string &filename) {

    this->setUpdated();

    std::ifstream ifs;
    std::string line;

    ifs.open(filename, std::ifstream::in);

    while (ifs.good()) {
        std::getline(ifs, line);

        float num = std::stof(line);
        this->add(num);

    }

    ifs.close();

}

/**
 * Get max value from set
 *
 * @tparam T
 * @return
 */
template<class T>
T StatisticMultiset<T>::max() const {

    /**
     * If set wasn't updated since last call, return cached value
     */
    if (this->lastMax.second) {
        return this->lastMax.first;
    }

    T max = *set.begin();

    for (auto num : this->set) {
        if (num > max) {
            max = num;
        }
    }

    /** Cache new value */
    this->lastMax.first = max;
    this->lastMax.second = true;

    return max;

}

/**
 * Get min value
 *
 * @tparam T
 * @return
 */
template<class T>
T StatisticMultiset<T>::min() const {

    /**
     * If set wasn't updated since last call, return cached value
     */
    if (this->lastMin.second) {
        return this->lastMin.first;
    }

    T min = *set.begin();

    for (auto num : this->set) {
        if (num < min) {
            min = num;
        }
    }

    /** Cache new value */
    this->lastMin.first = min;
    this->lastMin.second = true;

    return min;

}

template<class T>
float StatisticMultiset<T>::avg() const {

    /**
     * If set wasn't updated since last call, return cached value
     */
    if (this->lastAvg.second) {
        return this->lastAvg.first;
    }

    T sum  = 0;

    for (auto num : this->set) {
        sum += num;
    }

    float avg = (float)sum / this->set.size();

    /** Cache new value */
    this->lastAvg.first = avg;
    this->lastAvg.second = true;

    return avg;

}

/**
 * Get count of set members, which less then given threshold
 *
 * @tparam T
 * @param threshold
 * @return
 */
template<class T>
int StatisticMultiset<T>::lessThan(float threshold) const {

    /** Try to find cached value */
    typename std::map<float, std::pair<T, bool>>::const_iterator cached = this->lastLessThan.find(threshold);

    /** If cached value found, return one */
    if (cached != this->lastLessThan.end() && cached->second.second) {
        return cached->second.first;
    }

    int result = 0;

    for (auto num : this->set) {
        result += num < threshold;
    }

    /** Cache new value */
    std::pair<T, bool> valueToCache(result, true);
    this->lastLessThan[threshold] = valueToCache;

    return result;

}

template<class T>
int StatisticMultiset<T>::greaterThan(float threshold) const {

    /** Try to find cached value */
    typename std::map<float, std::pair<T, bool>>::const_iterator cached = this->lastLessThan.find(threshold);

    /** If cached value found, return one */
    if (cached != this->lastLessThan.end() && cached->second.second) {
        return cached->second.first;
    }

    int result = 0;

    for (auto num : this->set) {
        result += num > threshold;
    }

    /** Cache new value */
    std::pair<T, bool> valueToCache(result, true);
    this->lastGreaterThan[threshold] = valueToCache;


    return result;

}

/**
 * Called every time, when set was updated
 *
 * @tparam T
 */
template<class T>
void StatisticMultiset<T>::setUpdated() const {

    this->lastMax.second = false;
    this->lastMin.second = false;
    this->lastAvg.second = false;

    for (auto& i : this->lastLessThan) {
        i.second.second = false;
    }

    for (auto& i : this->lastGreaterThan) {
        i.second.second = false;
    }
}
