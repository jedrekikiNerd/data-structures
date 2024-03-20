// TODO: Start with definition of all methods and variables and then start implementing in cpp


template <typename Type>
class DynamicArray
{private:
    Type *arr;
    int capacity;
    int size;

public:
    DynamicArray() {
        capacity = 1;
        size = 0;
        arr = new Type[capacity];
    }

     ~DynamicArray() {
        delete[] arr;
    }

    void add_back(Type value) {};
    void add_front(Type value) {};
    void add_at(Type value,int index) {};

    void pop_front() {};
    void remove_back() {};
    void remove_at(int index) {};
    void clear() {};
    
    int& operator[](int index) {
        return arr[index];
    };

    int size() const {};

    int getCapacity() const {};

    int getElement(int index) const {};
};
