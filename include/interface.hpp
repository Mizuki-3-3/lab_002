#include <string>
#include <memory>
#include <cctype>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "list_seq.hpp"
#include "array_seq.hpp"
#include "bit_seq.hpp"
#include "Mutability.hpp"
#include <cmath>

template<typename T>
std::string to_string_impl(const T& value);

class ElementArray {
    std::unique_ptr<ftxui::Element[]> data_;
    size_t size_;
public:
    explicit ElementArray(size_t size) : data_(new ftxui::Element[size]), size_(size) {}
    ftxui::Element& operator[](size_t i) { return data_[i]; }
    const ftxui::Element& operator[](size_t i) const { return data_[i]; }
    ftxui::Element* begin() { return data_.get(); }
    ftxui::Element* end()   { return data_.get() + size_; }
    const ftxui::Element* begin() const { return data_.get(); }
    const ftxui::Element* end()   const { return data_.get() + size_; }
    size_t size() const { return size_; }
};

void start_();