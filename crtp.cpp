#include <iostream>
#include <memory>

using namespace std;

template <class T>
class base
{
public:
    void interface()
    {
        static_cast<T *>(this)->implementation();
    }
    std::unique_ptr<T> clone()
    {
        return std::make_unique<T>(static_cast<T const &>(*this));
    }
};

class derived1 : public base<derived1>
{
    friend class base;

private:
    void implementation()
    {
        std::cout << "derived 1" << std::endl;
    }
};

class derived2 : public base<derived2>
{
    friend class base;

private:
    void implementation()
    {
        std::cout << "derived 2" << std::endl;
    }
};

int main()
{
    auto der1 = std::make_unique<derived1>();
    der1->interface();               // print "derived 1"
    auto der1_clone = der1->clone(); // clone() works
    der1_clone->interface();         // print "derived 1"

    auto der2 = std::make_unique<derived2>();
    der2->interface();               // print "derived 2"
    auto der2_clone = der2->clone(); // clone() also already works
    der2_clone->interface();         // print "derived 2"

    return 0;
}