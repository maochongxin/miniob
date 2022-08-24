#ifndef __COMMON_LANG_CACHE_H__
#define __COMMON_LANG_CACHE_H__

namespace common {

template <typename Container, typename KeyType = typename Container::key_type, typename ValueType = typename Container::value_type>
class Cache {
public:
    ValueType get(const KeyType& key) {
        return static_cast<Container*>(this)->get(key);
    }
    void put(const KeyType key, const ValueType& value) {
        static_cast<Container*>(this)->put(key, value);
    }
    inline std::size_t capacity() {
        return static_cast<Container*>(this)->capacity();
    }
};

template <typename KeyType, typename ValueType>
class SimpleLRU : public Cache<SimpleLRU<KeyType, ValueType>, KeyType, ValueType> {
public:
    using key_type = KeyType;
    using value_type = ValueType;
public:
    SimpleLRU(std::size_t cacacity = 10): capacity_(cacacity) {}
    ~SimpleLRU() = default;
public:
    ValueType get(const KeyType& key) {
        if (map_.find(key) != map_.end()) {
            auto val = *map_[key];
            list_.erase(map_[key]);
            list_.push_front(val);
            map_[key] = list_.begin();
            return val.second;
        }
        return ValueType();
    }
    void put(const KeyType& key, const ValueType& value) {
        if (capacity_ > 0) {
            if (map_.find(key) != map_.end()) {
                list_.erase(map_[key]);
                list_.push_front({key, value});
            } else {
                if (list_.size() >= capacity_) {
                    map_.erase(list_.back().first);
                    list_.pop_back();
                }
                list_.push_front({key, value});
            }
            map_[key] = list_.begin();
        }
    }
    inline std::size_t capacity() const {
        return capacity_;
    }

private:
    std::list<std::pair<KeyType, ValueType>> list_;
    std::unordered_map<KeyType, typename std::list<std::pair<KeyType, ValueType>>::iterator> map_;
    std::size_t capacity_;
};

}

#endif