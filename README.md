# Singleton

My own implementation of a portable singleton in C/CPP following the stb style.

## Usage

This library need to be included in your project as a submodule. To do this, you
can run the following command:

```sh
git submodule add https://github.com/MasterLaplac   e/Singleton.git
```

This Library provides two files, `Singleton.hpp` and `singleton.h`. To use it,
you need to define `SINGLETON_IMPLEMENTATION` in one of your source files before
including the header file. This will generate the implementation of the functions
in the header file.

Here is an example of how to use the library:

#### Singleton.hpp (C++)

```cpp
#define SINGLETON_NO_THREAD_SAFETY
#define SINGLETON_IMPLEMENTATION
#include "Singleton.hpp"

class Manager : public Singleton<Manager> {
    public:
        explicit Manager(int value = 0) : _value(value) {}
        ~Manager() = default;

        void SetValue(int value)
        {
            _value = value;
        }

        int GetValue() const
        {
            return _value;
        }

        void PrintValue() const
        {
            std::cout << "Value: " << _value << std::endl;
        }

    protected:
    private:
        int _value = 0;
};

int main()
{
    std::cout << "Start" << std::endl;
    {
        Singleton<Manager>::CreateInstance(10);
        Singleton<Manager>::GetInstance().PrintValue();
        Singleton<Manager>::DestroyInstance();
    }
    std::cout << "End" << std::endl;
    return 0;
}
```

#### singleton.h (C)
