#pragma once

template<typename T>
class dyn_arr :
{
    private:
        T* data;
        unsigned size;
    public:
        dyn_arr () : data(nullptr), size(0) {}
        explicit dyn_arr(unsigned initial_size): data(new T[initial_size]), size(initial_size) {
            for (unsigned i = 0; i < initial_size; ++i) {
                data[i] = T();  // или nullptr для указателей
            }
        }
        dyn_arr(T* item, unsigned initial_size): size(initial_size), data(new T[initial_size]){
            for (int i = 0; i < count; ++i) data[i] = item;
        }
        dyn_arr(const dyn_arr& other) : size(other.size), data(new T[other.size]){
            for (int i = 0; i < size; ++i) data[i] = other.data[i];
        }
        ~dyn_arr() {
            delete[] data;
        }

        T& operator[](unsigned index){
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
        }

        T* begin(){return data;}

        const T* begin()const {return data;}

        T* end(){return data+size;}

        const T* end()const {return data+size;}

        dyn_arr(const vector& ) = delete;

        dyn_arr& operator=(const vector&) = delete;

        dyn_arr& operator=(dyn_arr other){
            std::swap(data, other.data);
            std::swap(size, other.size);
            return *this;
        }

        T* data() { return data;}

        const T* data() const { return data;}
        
        unsigned len() const { return size;}

        void resize(unsigned new_size) {
            T* new_data = new T[new_size];
            for (unsigned i = 0; i < new_size; ++i) {
                new_data[i] = std::move(data_[i]);
            }
            delete[] data;
            data = new_data;
            size = new_size;
        }
        template <typename U> friend class array_sec;
};
