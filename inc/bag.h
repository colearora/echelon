#ifndef LA_BAG_H
#define LA_BAG_H

namespace la
{

/**
 * Bag: a generic, unsorted, dynamically resizing container of objects
 * that exist elsewhere. Supports addition and iteration
 * but not deletion. Objects added by reference are freed
 * by the caller, while objects added by pointer are freed
 * by the Bag.
 */
template <typename T>
class Bag
{
public:
    Bag()
    : _n{0},
      _cap{1},
      _items{new T*[1]},
      _owns{new bool[1]}
    {}

    ~Bag()
    {
        for (int i = 0; i < _n; ++i)
        {
            if (_owns[i])
            {
                delete _items[i];
            }
        }
        delete[] _items;
        delete[] _owns;
    }

    void add(T& r)
    {
        checkSize();
        _items[_n] = &r;
        _owns[_n] = false;
        ++_n;
    }

    void add(T* p)
    {
        checkSize();
        _items[_n] = p;
        _owns[_n] = true;
        ++_n;
    }

    const T& operator[](int i)
    {
        assert(i >= 0 && i < _n);
        return *(_items[i]);
    }

    int size() const
    {
        return _n;
    }

private:
    void checkSize()
    {
        if (_n == _cap)
        {
            resize(2 * _cap);
        }
    }

    void resize(int newCap)
    {
        T** newItems = new T*[newCap];
        bool* newOwns = new bool[newCap];
        for (int i = 0; i < _n; ++i)
        {
            newItems[i] = _items[i];
            newOwns[i] = _owns[i];
        }
        delete[] _items;
        delete[] _owns;
        _items = newItems;
        _owns = newOwns;
        _cap = newCap;
    }

    int _n, _cap;
    T** _items;
    bool* _owns;
};

}  // namespace la

#endif