# Singleton

My own implementation of a portable singleton in C/CPP following the stb style.

## Usage

This library is designed to be used as a submodule in your project. To do this,
you can run the following command:

```sh
git submodule add https://github.com/MasterLaplace/Singleton.git
```

Or you can add it as a dependency in your `CMakeLists.txt` file:

```cmake
INCLUDE(FetchContent)

FetchContent_Declare(
    Singleton
    GIT_REPOSITORY https://github.com/MasterLaplace/Singleton.git
    GIT_TAG v1.0.2
)

FetchContent_MakeAvailable(Singleton)
target_include_directories(target PRIVATE ${singleton_SOURCE_DIR})
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
        Manager::CreateInstance(10);
        Manager::GetInstance().PrintValue();
        // Manager::UnlockInstance();
        Manager::DestroyInstance();
    }
    std::cout << "End" << std::endl;
    return 0;
}
```

#### singleton.h (C)

```c
#define SINGLETON_NO_THREAD_SAFETY
#define SINGLETON_H_IMPLEMENTATION
#include "Singleton/singleton.h"

typedef struct {
    int _value;
} manager_t;

void *manager_create(va_list args)
{
    manager_t *manager = malloc(sizeof(manager_t));

    if (!manager)
        return nullptr;

    manager->_value = va_arg(args, int);
    return manager;
}

void manager_SetValue(singleton_t *instance, int value)
{
    ((manager_t *)instance->data)->_value = value;
}

int manager_GetValue(singleton_t *instance)
{
    manager_t *manager = (manager_t *)instance->data;

    return manager->_value;
}

void manager_print_value(singleton_t *instance)
{
    manager_t *manager = (manager_t *)instance->data;

    printf("Value: %d\n", manager->_value);
}

void manager_destroy(void *data)
{
    free((manager_t *)data);
}

int main()
{
    printf("Start\n");
    {
        instance_create(&manager_create, &manager_destroy, 10);
        manager_print_value(instance_get());
        // instance_unlock();
        instance_destroy();
    }
    printf("End\n");
    return 0;
}
```
