#include "vstring.h"

my_stl::vstring::vstring(const char *user_string) : vector<char>() {
    add_ms(user_string);
}

my_stl::vstring::vstring(char user_char[]) : vector<char>() {
    add_ms(user_char);
}

my_stl::vstring &my_stl::vstring::add_ms(const char *user_char) {
    int element = 0;

    while (user_char[element] != '\0') {
        if (number_of_elements >= current_size - 1)
            expand_twice_the_size();
        *(main_buffer + number_of_elements) = user_char[element];
        element++;
        number_of_elements++;
    }

    *(main_buffer + number_of_elements) = '\0';

    return *this;
}

void my_stl::vstring::remove_last_char() {
    main_buffer[number_of_elements - 1] = '\0';
    number_of_elements--;
}

void my_stl::vstring::remove_white_space_end() {

    for (int i = (int) number_of_elements - 1; i >= 0; i--) {
        if (main_buffer[i] != ' ') {
            return;
        }
        remove_last_char();
    }
}

my_stl::vstring &my_stl::vstring::operator=(const char *user_char) {
    number_of_elements = 0;
    add_ms(user_char);

    return *this;
}


bool my_stl::vstring::operator==(const char *user_char) const {
    int element = 0;

    while (user_char[element] != '\0') {
        if (main_buffer[element] != user_char[element])
            return false;
        element++;
    }

    return true;
}

my_stl::vstring &my_stl::vstring::operator+(const char *user_char) {
    add_ms(user_char);

    return *this;
}


my_stl::vstring &my_stl::vstring::operator+=(const char *user_char) {
    add_ms(user_char);

    return *this;
}

namespace my_stl {
    std::istream &operator>>(std::istream &is, my_stl::vstring &vstring) {
        char user_input[1024];
        std::cin >> user_input;
        vstring.clear();

        vstring.add_ms(user_input);

        return is;
    }

    std::ostream &operator<<(std::ostream &os, const my_stl::vstring &vstring) {

        for (unsigned int i = 0; i < vstring.size(); i++) {
            os << vstring.main_buffer[i];
        }

        return os;
    }
}
