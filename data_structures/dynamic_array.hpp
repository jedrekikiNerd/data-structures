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

    void push_back(Type value) {};

    void push_front(Type value) {};

    void push_at(Type value,int index) {};

    void pop_front(Type value) {};

    int& operator[](int index) {
        return arr[index];
    }

    int getSize() const {}

    int getCapacity() const {}

    int getElement(int index) const {}
};