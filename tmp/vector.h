//
// Created by pokerstar on 28.06.2019.
//
#include <iostream>

template<typename T>
struct vector {
public:
    typedef T value_type;
    typedef T *iterator;
    typedef T const *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


    vector() : info(nullptr) {}

    vector(vector const &rhs) {
        if (rhs.empty()) {
            info = nullptr;
        } else if (rhs.is_small()) {
            new(&small_obj) value_type(rhs.small_obj);
            info = (size_t *) &small_obj;
        } else {
            info = rhs.info;
            array = rhs.array;
            ++info[2];
        }
    }

    vector &operator=(vector const &rhs) {
        if (this == &rhs) {
            return *this;
        }
        if (rhs.empty()) {
            free_data();
            info = nullptr;
        } else if (rhs.is_small()) {
            if (is_null()) {
                new(&small_obj) value_type(rhs.small_obj);
                info = (size_t *) &small_obj;
            } else if (is_small()) {
                small_obj = rhs.small_obj;
            } else {
                size_t *save_pointer = info;
                new(&small_obj) value_type(rhs.small_obj);
                info = (size_t *) &small_obj;
                free_info(save_pointer);
            }
        } else {
            free_data();
            info = rhs.info;
            array = rhs.array;
            ++info[2];
        }
        return *this;
    }

    template<typename InputIterator>
    vector(InputIterator first, InputIterator last) : info(nullptr) {
        try{
            while (first != last) {
                push_back(*first);
                ++first;
            }
        } catch (...) {
            free_data();
            throw;
        }
    }

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last) {
        vector oth(first, last);
        swap(*this, oth);
    }

    value_type &operator[](size_t pos) {
        if (pos < size()) {
            if (capacity() == 1) {
                return small_obj;
            } else {
                if (safety_change()) {
                    return array[pos];
                } else {
                    throw std::runtime_error("Couldn't get access for element modifying");
                }
            }
        } else {
            throw std::runtime_error("Position greater than size");
        }
    }

    value_type const &operator[](size_t pos) const {
        if (pos < size()) {
            if (capacity() == 1) {
                return small_obj;
            } else {
                return array[pos];
            }
        } else {
            throw std::runtime_error("Position greater than size");
        }
    }

    value_type &front() {
        if (!empty()) {
            return (*this)[0];
        } else {
            throw std::runtime_error("Empty vector");
        }
    }

    value_type &back() {
        if (!empty()) {
            return (*this)[size() - 1];
        } else {
            throw std::runtime_error("Empty vector");
        }
    }

    value_type const &front() const {
        if (!empty()) {
            return (*this)[0];
        } else {
            throw std::runtime_error("Empty vector");
        }
    }

    value_type const &back() const {
        if (!empty()) {
            return (*this)[size() - 1];
        } else {
            throw std::runtime_error("Empty vector");
        }
    }

    bool push_back(value_type const& obj) {
        if (is_null()) {
            new(&small_obj) value_type(obj);
            info = (size_t *) &small_obj;
        } else {
            if (begin() <= &obj && &obj < end()) {
                value_type K = obj;
                safety_change();
                reserve(size() + 1);
                new(array + size()) value_type(K);
            } else {
                safety_change();
                reserve(size() + 1);
                new(array + size()) value_type(obj);
            }
            ++info[1];
        }
        return true;
    }

    void pop_back() {
        if (size() > 0) {
            if (is_small()) {
                small_obj.~value_type();
                info = nullptr;
            } else {
                array[--info[1]].~value_type();
            }
        } else {
            throw std::runtime_error("Empty vector");
        }
    }

    value_type *data() {
        return begin();
    }

    value_type const *data() const {
        return begin();
    }

    bool empty() const {
        return size() == 0;
    }

    size_t size() const {
        if (is_null()) {
            return 0;
        } else if (is_small()) {
            return 1;
        } else {
            return info[1];
        }
    }

    void reserve(size_t cap) {
        if (cap > capacity()) {
            if (is_null() || is_small()) {
                from_small_to_big(2 * cap);
            } else {
                change_array_capacity(2 * cap);
            }
        }
    }

    size_t capacity() const noexcept {
        if (is_null()) {
            return 0;
        } else if (is_small()) {
            return 1;
        } else {
            return info[0];
        }
    }

    void shrink_to_fit() {
        if (!is_null() && !is_small()) {
            change_array_capacity(size());
        }
    }

    void resize(size_t sz, value_type const &obj) {
        reserve(sz);
        while (sz < size()) {
            pop_back();
        }
        while (sz > size()) {
            push_back(obj);
        }
    }

    void clear() {
        while (size() > 0) {
            pop_back();
        }
    }

    ~vector() {
        free_data();
    }

    iterator begin() {
        if (is_null()) {
            return nullptr;
        }
        if (is_small()) {
            return &small_obj;
        }
        return array;
    }

    const_iterator begin() const {
        if (is_null()) {
            return nullptr;
        }
        if (is_small()) {
            return &small_obj;
        }
        return array;
    }

    iterator end() {
        if (is_null()) {
            return nullptr;
        }
        return begin() + size();
    }

    const_iterator end() const {
        if (is_null()) {
            return nullptr;
        }
        return begin() + size();
    }

    reverse_iterator rbegin() {
        if (is_null()) {
            return (reverse_iterator) nullptr;
        }
        size_t sz = size();
        if (sz == 0) {
            return (reverse_iterator) nullptr;
        } else {
            return (reverse_iterator) (end());
        }
    }

    const_reverse_iterator rbegin() const {
        if (is_null()) {
            return (const_reverse_iterator) nullptr;
        }
        size_t sz = size();
        if (sz == 0) {
            return (const_reverse_iterator) nullptr;
        } else {
            return (const_reverse_iterator) (end());
        }
    }

    reverse_iterator rend() {
        if (is_null()) {
            return (reverse_iterator) nullptr;
        }
        return rbegin() + size();
    }

    const_reverse_iterator rend() const {
        if (is_null()) {
            return (const_reverse_iterator) nullptr;
        }
        return rbegin() + size();
    }

    iterator insert(const_iterator pos, value_type const &val) {
        const_iterator finish = end();
        size_t count_after = 0;
        while (pos < finish) {
            --finish;
            ++count_after;
        }
        if (!push_back(val)) {
            return end();
        }
        iterator it = end() - 1;
        while (count_after > 0) {
            --count_after;
            std::swap(*(it - 1), *it);
            --it;
        }
        return it;
    }

    iterator erase(const_iterator pos) {
        const_iterator finish = end() - 1;
        iterator pos2 = (iterator) pos;
        iterator res = nullptr;
        while (pos2 < finish) {
            std::swap(*pos2, *(pos2 + 1));
            if (res == nullptr) {
                res = pos2;
            }
            ++pos2;
        }
        pop_back();
        return res;
    }

    iterator erase(const_iterator first, const_iterator last) {
        const_iterator finish = end();
        iterator elems_after_last = (iterator) last;
        iterator space = (iterator) first;
        size_t del_count = 0;
        while (first < last) {
            ++first;
            ++del_count;
        }
        iterator res = nullptr;
        while (elems_after_last < finish) {
            std::swap(*space, *elems_after_last);
            if (res == nullptr) {
                res = space;
            }
            ++elems_after_last;
            ++space;
        }
        while (del_count > 0) {
            pop_back();
            --del_count;
        }
        return res;
    }

    friend int64_t compare(vector const &v1, vector const &v2) {
        size_t sz1 = v1.size(), sz2 = v2.size();
        for (size_t i = 0; i < sz1 && i < sz2; ++i) {
            if (v1[i] < v2[i]) {
                return -1;
            }
            if (v2[i] < v1[i]) {
                return 1;
            }
        }
        if (sz1 < sz2) {
            return -1;
        }
        if (sz2 < sz1) {
            return 1;
        }
        return 0;
    }

    friend bool operator==(vector const &v1, vector const &v2) {
        return compare(v1, v2) == 0;
    }

    friend bool operator!=(vector const &v1, vector const &v2) {
        return compare(v1, v2) != 0;
    }

    friend bool operator>(vector const &v1, vector const &v2) {
        return compare(v1, v2) > 0;
    }

    friend bool operator<(vector const &v1, vector const &v2) {
        return compare(v1, v2) < 0;
    }

    friend bool operator>=(vector const &v1, vector const &v2) {
        return compare(v1, v2) >= 0;
    }

    friend bool operator<=(vector const &v1, vector const &v2) {
        return compare(v1, v2) <= 0;
    }

    friend void swap(vector &v1, vector &v2) {
        vector v3 = v1;
        v1 = v2;
        v2 = v3;
    }

    friend std::ostream &operator<<(std::ostream &os, vector const &v) {
        os << "Out vector: ";
        for (size_t i = 0; i < v.size(); ++i) {
            os << v[i] << " ";
        }
        os << std::endl;
        return os;
    }

private:
    union {
        value_type small_obj;
        T *array;
    };
    size_t *info;

    bool is_small() const {
        return (value_type *) info == &small_obj;
    }

    bool is_null() const {
        return info == nullptr;
    }

    void from_small_to_big(size_t nw_cap) {
        if (is_null()) {
            void *tmp_data = malloc(sizeof(size_t) * 3 + sizeof(value_type) * nw_cap);
            if (tmp_data == nullptr) {
                throw std::runtime_error("Wrong allocate");
            }
            info = (size_t *) tmp_data;
            info[0] = nw_cap;
            info[1] = 0;
            info[2] = 1;
            array = (value_type *) (info + 3);
        } else if (is_small()) {
            if (nw_cap == 0) {
                nw_cap = 1;
            }
            void *tmp_data = malloc(sizeof(size_t) * 3 + sizeof(value_type) * nw_cap);
            if (tmp_data == nullptr) {
                throw std::runtime_error("Wrong allocate");
            }
            try {
                new((size_t *) tmp_data + 3) value_type(small_obj);
            } catch (...) {
                free(tmp_data);
                throw std::runtime_error("Wrong creating object copy");
            }
            info = (size_t *) tmp_data;
            info[0] = nw_cap;
            info[1] = 1;
            info[2] = 1;
            small_obj.~value_type();
            array = (value_type *) (info + 3);
        }
    }

    void free_data() {
        if (is_null()) {

        } else if (is_small()) {
            small_obj.~value_type();
        } else {
            free_info(info);
        }
        info = nullptr;
    }

    void free_info(size_t* tmp_info) {
        if (--tmp_info[2] == 0) {
            size_t sz = size();
            for (size_t elem = 0; elem < sz; ++elem) {
                (*((value_type *)(tmp_info + 3) + elem)).~value_type();
            }
            free((void *) tmp_info);
        }
    }

    bool safety_change() {
        if (links_count() > 1) {
            try {
                change_array_capacity(capacity());
            } catch (...) {
                return false;
            }
        }
        return true;
    }

    void change_array_capacity(size_t nw_capacity) {
        size_t *tmp_info = (size_t *) copy_array(nw_capacity);
        if (tmp_info == nullptr) {
            throw std::runtime_error("Wrong allocate");
        }
        value_type *arr = (value_type *) (tmp_info + 3);
        free_data();
        info = tmp_info;
        array = arr;
    }


    void *copy_array(size_t custom_capacity) {
        size_t rhs_cap = custom_capacity;
        size_t rhs_sz = size();
        if (rhs_cap < rhs_sz) {
            rhs_sz = rhs_cap;
        }
        void *tmp_data = malloc(sizeof(size_t) * 3 + sizeof(value_type) * rhs_cap);
        if (tmp_data == nullptr) {
            return nullptr;
        }
        size_t *tmp_info = (size_t *) tmp_data;
        value_type *arr = (value_type *) (tmp_info + 3);
        tmp_info[0] = rhs_cap;
        tmp_info[1] = 0;
        tmp_info[2] = 1;
        try {
            for (size_t elem = 0; elem < rhs_sz; ++elem) {
                new(arr + elem) value_type(array[elem]);
                ++tmp_info[1];
            }
        } catch (...) {
            for (size_t elem = 0; elem < tmp_info[1]; ++elem) {
                arr[elem].~value_type();
            }
            free(tmp_data);
            return nullptr;
        }
        return tmp_data;
    }

    size_t links_count() const {
        if (is_null() || is_small()) {
            return 1;
        } else {
            return info[2];
        }
    }
};