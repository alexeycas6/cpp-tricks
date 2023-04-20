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

class derived : public base<derived>
{
    friend class base;

private:
    void implementation()
    {
        std::cout << "derived" << std::endl;
    }
};

int main()
{
    derived *d = new derived();
    d->interface(); // print "derived"

    auto t = d->clone();
    t->interface(); // print "derived"

    return 0;
}