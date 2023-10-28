#include <iostream>
#include <memory>
using namespace std;

class MyClass
{
public:
    MyClass()
    {
        cout << "Constructor" << endl;
    }

    ~MyClass()
    {
        cout << "Destructor" << endl;
    }

    void pretty_print()
    {

        cout << "Pretty_print" << endl;
    };
};

int main()
{
    cout << "Unique pointer Scope starts " << endl;
    {
        unique_ptr<MyClass> unPtr1 = make_unique<MyClass>();
        unPtr1->pretty_print();
        unique_ptr<MyClass> unPtr2 = move(unPtr1);
        unPtr2->pretty_print();
        unPtr1->pretty_print(); // should get an error depending on the compiler used
    }
    cout << "Unique pointer Scope finished " << endl;

    cout << "Shared pointer Scope starts " << endl;
    {
        shared_ptr<MyClass> shPtr1 = make_shared<MyClass>();

        cout << "Share count: " << shPtr1.use_count() << endl;

        {
            shared_ptr<MyClass> shPtr2 = shPtr1;
            cout << "Share count: " << shPtr1.use_count() << endl;
        }
        cout << "Share count: " << shPtr1.use_count() << endl;
    }

    cout << "Shared pointer Scope finished " << endl;

    cout << "Weak pointer Scope starts: Used only to read data, the weak pointer is not kept alive, event withing the scope" << endl;
    weak_ptr<MyClass> wePtr1;
    {

        shared_ptr<MyClass> shPtr1 = make_shared<MyClass>();
        wePtr1 = shPtr1;

        cout << "Share count: " << shPtr1.use_count() << endl;

        {
            wePtr1 = shPtr1;
            std::shared_ptr<MyClass> sharedPtr = wePtr1.lock();
            sharedPtr->pretty_print();
            cout << "Share count: " << shPtr1.use_count() << endl;
        }
        cout << "Share count: " << shPtr1.use_count() << endl;
    }

    cout << "Weak pointer Scope finished " << endl;

    return 0;
}