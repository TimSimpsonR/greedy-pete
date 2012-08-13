#include <iostream>
#include <string>
#include <unistd.h>

const size_t MB = 1024 * 1024;

struct Segment;

struct Segment {
    Segment * prev;
    size_t size;

    Segment(Segment * p, size_t s)
    :prev(p), size(s)
    {
    }
};

void go_on() {
    std::string unused_input;
    std::cerr << "Hit enter to proceed.";
    std::cin >> unused_input;
}

int main(int argc, char* argv[]) {
    std::cerr << "Hello. My name is Greedy Pete." << std::endl;
    std::cerr << "My proc id is " << getpid() << " and I liked to eat and eat."
              << std::endl;
    go_on();
    size_t sum = 0;
    Segment * current = 0;
    while (sum <= MB * 2048) {
        size_t size = MB;
        void * next = ::operator new(size);
        char * chars = reinterpret_cast<char *>(next); //::operator new(size);
        for (size_t i = 0; i < size; i ++) {
            chars[i] = 'a';
        }
        Segment * new_segment = new (next) Segment(current, size);
        current = new_segment;
        sum += size;
        std::cerr << "Current = " << current << ", Sum = " << sum
                  << " (" << (sum / MB) << " MB)" << std::endl;
    }

    go_on();

    while(current != 0) {
        Segment * old = current;
        current = current->prev;
        sum -= old->size;
        delete old;
        std::cerr << "Sum = " << sum << " (" << (sum / MB) << " MB)"
                  << std::endl;
    }
    std::cerr << "Bye!" << std::endl;
    go_on();

}
