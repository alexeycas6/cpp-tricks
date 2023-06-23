#include "cache_invalidation.hpp"

using namespace std::chrono_literals;
int main() {

    {
        cache_invalidation c(1s);
        c.start();
    }
}