//
// Created by Administrator on 2026/7/17.
//

#ifndef LN_MYARRAY_HPP
#define LN_MYARRAY_HPP
#include <cstring>

namespace my_std {
    template<class T>
    class MyArray {
    public:
        MyArray(size_t size) : size(size), count(0) {
            array = new T[size];
        }

        MyArray(const MyArray &arr) {
            *this = arr;
        }

        T &operator[](size_t offset) const {
            if (offset >= size)
                return array[0];
            return array[offset];
        }

        bool isEmpty() {
            return count == 0;
        }

        bool isFull() {
            return count == size;
        }

        void pushBack(const T &obj) {
            if (isFull())
                return;
            //这里的T必须拥有深拷贝的重载=操作符函数
            //否则会进行简单的浅拷贝，指向同一份内存，出现问题。
            //所以使用数组模板的类必须重载=，赋予深拷贝语义
            this->array[count++] = obj;
        }

        T &popBack() {
            // if (isEmpty())
            // return T{};
            return array[--count];
        }

        MyArray &operator=(const MyArray &arr) {
            if (this == &arr)
                return *this;
            if (this->size)
                deleteElement();
            this->size = arr.size;
            this->count = arr.count;
            array = new T[this->size];
            memcpy(this->array, arr.array, this->count * sizeof(T));
            return *this;
        }

        ~MyArray() {
            deleteElement();
            array = nullptr;
            size = 0;
            count = 0;
        }

    private:
        void deleteElement() {
            // for (int i = 0; i < this->count; i++) {
            // delete this->array[i];
            // }
            delete[] array;
        }

        size_t size;
        size_t count;
        T *array;
    };
}
#endif //LN_MYARRAY_HPP
