#include <interface.hpp>

list_seq<Mutability::Mutable, int> my_list_i;
array_seq<Mutability::Mutable, int> my_array_i;
list_seq<Mutability::Mutable, float> my_list_f;
array_seq<Mutability::Mutable, float> my_array_f;
list_seq<Mutability::Mutable, char> my_list_c;
array_seq<Mutability::Mutable, char> my_array_c;
// list_seq<Mutability::Mutable, std::string> my_list_s;
// array_seq<Mutability::Mutable, std::string> my_array_s;
using BitType = unsigned long long;
bit_seq<Mutability::Mutable, BitType>    my_bit_seq;

std::vector<std::string> display_items; 

std::vector<std::string> container = {"list", "array"};
std::vector<std::string> data_type  = {"int", "float", "char"};
std::vector<std::string> mode = {"append", "prepend", "insert", "map", "reduce", "where"};

std::vector<std::string> map_func_for_int = {"x+1", "x*2", "x-1", "x/2", "x = 0"};
std::vector<std::string> map_func_for_float = {"x+1", "x*2", "x-1", "x/2", "x = 0"};
std::vector<std::string> map_func_for_char = {"Изменить регистр", "заменить следующим char в кодировке", "заменить предыдущим char в кодировке"};
std::vector<std::string> map_func_bit    = {"побитовое NOT", "сдвиг влево", "сдвиг вправо", "AND 0x5555", "обнулить"};

std::vector<std::string> where_func_for_int = {"x mod 3 == 0", "x <= 0", "x >= 0", "трехзначные", "четырехначные"};
std::vector<std::string> where_func_for_float = {"x - abs(x) != 0", "x <= 0", "x >= 0"};
std::vector<std::string> where_func_for_char = {"Только заглавные", "Только строчные", "только буквы", "только цифры"};
std::vector<std::string> where_func_bit = {"не ноль", "нечётные", ">256"};


std::vector<std::string> reduce_func_for_int = {"min", "max", "sum", "product"};
std::vector<std::string> reduce_func_for_float = {"min", "max", "sum", "product", "среднее арифметическое"};
std::vector<std::string> reduce_func_for_char = {"кол-во гласных", "кол-во цифр", "кол-во согласных", "самый большой ascii код"};

int selected_item =0, selected_container = 0, selected_data_type = 0, selected_mode = 0,
    func_choice = 0, selected_map_func = 0, selected_reduce_func = 0, selected_where_func = 0;
std::string last_result;

template<typename V>
V parse_value(const std::string& s, bool& ok) { //string->other_type
    ok = true;
    if constexpr (std::is_same_v<V, int>) {
        try {
            size_t pos;
            int val = std::stoi(s, &pos);
            ok = (pos == s.size());
            return val;
        } catch(...) { ok = false; return 0; }
    } else if constexpr (std::is_same_v<V, float>) {
        try {
            size_t pos;
            float val = std::stof(s, &pos);
            ok = (pos == s.size());
            return val;
        } catch(...) { ok = false; return 0.0f; }
    } else if constexpr (std::is_same_v<V, char>) {
        ok = !s.empty();
        return ok ? s[0] : '\0';
    } else if constexpr (std::is_same_v<V, BitType>) {
        try {
            size_t pos;
            BitType val = std::stoull(s, &pos);
            ok = (pos == s.size());
            return val;
        } catch(...) { ok = false; return 0; }
    }
}

template<typename T>
std::string to_string_impl(const T& value) {
    if constexpr (std::is_same_v<T, char>) {
        return std::string(1, value);
    } else if constexpr (std::is_same_v<T, float>) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << value;
        return oss.str();
    } else if constexpr (std::is_same_v<T, BitType>) {
        return std::to_string(value);
    } else {
        return std::to_string(value);
    }
}


template<typename Seq>
void erase_at(Seq& seq, unsigned idx) {
    if (idx >= seq.size()) return;
    Seq temp;
    for (unsigned i = 0; i < seq.size(); ++i) {
        if (i != idx) temp.append(seq[i]);
    }
    seq = temp;
}

void update_display_items() {
    display_items.clear();
    auto add_from_seq = [&](auto& seq) {
        for (unsigned i = 0; i < seq.size(); ++i)
            display_items.push_back(to_string_impl(seq[i]));
    };
    if (selected_container == 0) { // list
        switch (selected_data_type) {
            case 0: add_from_seq(my_list_i); break;
            case 1: add_from_seq(my_list_f); break;
            case 2: add_from_seq(my_list_c); break;
        }
    } else if (selected_container == 1) { // array
        switch (selected_data_type) {
            case 0: add_from_seq(my_array_i); break;
            case 1: add_from_seq(my_array_f); break;
            case 2: add_from_seq(my_array_c); break;
        }
    }else if (selected_container == 2) { // bit sequence
        add_from_seq(my_bit_seq);
    }
    if (selected_item >= (int)display_items.size() && !display_items.empty())
        selected_item = (int)display_items.size() - 1;
    if (display_items.empty())
        selected_item = 0;
}

void delete_selected() {
    if (selected_item < 0 || selected_item >= (int)display_items.size()) return;
    unsigned idx = selected_item;
    try {
        if (selected_container == 0) { // list
            switch (selected_data_type) {
                case 0: erase_at(my_list_i, idx); break;
                case 1: erase_at(my_list_f, idx); break;
                case 2: erase_at(my_list_c, idx); break;
            }
        } else if (selected_container == 1) { // array
            switch (selected_data_type) {
                case 0: erase_at(my_array_i, idx); break;
                case 1: erase_at(my_array_f, idx); break;
                case 2: erase_at(my_array_c, idx); break;
            }
        } else if (selected_container == 2) { // bit sequence
            erase_at(my_bit_seq, idx);
        }
        update_display_items();
    } catch (const index_out_of_range&) {
        last_result = "Ошибка: индекс вне диапазона";
    } catch (const empty_container&) {
        last_result = "Ошибка: контейнер пуст";
    } catch (const null_ptr&) {
        last_result = "Ошибка: потеря памяти";
    } catch (const exception_& e) {
        last_result = "Ошибка: " + std::string(e.what());
    } catch (const std::exception& e) {
        last_result = "Ошибка: " + std::string(e.what());
    } catch (...) {
        last_result = "Неизвестная ошибка";
    }
}
template<typename Seq, Mutability M, typename T>
void apply_modify_op(Seq& seq, const std::string& val_str, int idx, int /*func_choice*/) {
    try {
        if (selected_mode == 0 || selected_mode == 1 || selected_mode == 2) { // append/prepend/insert
            bool ok = false;
            T val = parse_value<T>(val_str, ok);
            if (!ok) throw invalid_argument();

            if (selected_mode == 0) {
                seq.append(val);
            } else if (selected_mode == 1) {
                seq.prepend(val);
            } else if (selected_mode == 2) {
                if (idx < 0 || static_cast<unsigned>(idx) > seq.size())
                    throw index_out_of_range();
                seq.insert(val, static_cast<unsigned>(idx));
            }
            update_display_items();
        }
        else if (selected_mode == 3) { // map
            std::function<T(const T&)> f;
            if constexpr (std::is_same_v<T, int>) {
                switch (selected_map_func) {
                    case 0: f = [](int x) { return x + 1; }; break;
                    case 1: f = [](int x) { return x * 2; }; break;
                    case 2: f = [](int x) { return x - 1; }; break;
                    case 3: f = [](int x) { return x / 2; }; break;
                    case 4: f = [](int)   { return 0; }; break;
                    default: f = [](int x) { return x; };
                }
            } else if constexpr (std::is_same_v<T, float>) {
                switch (selected_map_func) {
                    case 0: f = [](float x) { return x + 1.0f; }; break;
                    case 1: f = [](float x) { return x * 2.0f; }; break;
                    case 2: f = [](float x) { return x - 1.0f; }; break;
                    case 3: f = [](float x) { return x / 2.0f; }; break;
                    case 4: f = [](float)   { return 0.0f; }; break;
                    default: f = [](float x) { return x; };
                }
            } else if constexpr (std::is_same_v<T, char>) {
                switch (selected_map_func) {
                    case 0: // изменение регистра
                        f = [](char c) {
                            if (std::isupper(static_cast<unsigned char>(c)))
                                return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                            else if (std::islower(static_cast<unsigned char>(c)))
                                return static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
                            return c;
                        }; break;
                    case 1: f = [](char c) { return c + 1; }; break;
                    case 2: f = [](char c) { return c - 1; }; break;
                    default: f = [](char c) { return c; };
                }
            } else if constexpr (std::is_same_v<T, bit<BitType>>) { // BitType
                switch (selected_map_func) {
                    case 0: f = [](bit<BitType> x) { return ~x; }; break;
                    case 1: f = [](bit<BitType> x) { return x << 1; }; break;
                    case 2: f = [](bit<BitType> x) { return x >> 1; }; break;
                    case 3: f = [](bit<BitType> x) { return x & 0x5555ULL; }; break;
                    case 4: f = [](bit<BitType>)   { return 0ULL; }; break;
                    default: f = [](bit<BitType> x) { return x; };
                }
            }
            seq.map(f);
            update_display_items();
        }
        else if (selected_mode == 4) { // reduce
            std::string result_str;
            if constexpr (std::is_same_v<T, int>) {
                switch (selected_reduce_func) {
                    case 0: { // min
                        int min_val = seq.reduce([](int a, int b) { return std::min(a, b); }, seq[0]);
                        result_str = std::to_string(min_val);
                        break;
                    }
                    case 1: { // max
                        int max_val = seq.reduce([](int a, int b) { return std::max(a, b); }, seq[0]);
                        result_str = std::to_string(max_val);
                        break;
                    }
                    case 2: { // sum
                        int sum = seq.reduce([](int a, int b) { return a + b; }, 0);
                        result_str = std::to_string(sum);
                        break;
                    }
                    case 3: { // product
                        int prod = seq.reduce([](int a, int b) { return a * b; }, 1);
                        result_str = std::to_string(prod);
                        break;
                    }
                    default: result_str = "неизвестная функция reduce";
                }
            } else if constexpr (std::is_same_v<T, float>) {
                switch (selected_reduce_func) {
                    case 0: { // min
                        float min_val = seq.reduce([](float a, float b) { return std::min(a, b); }, seq[0]);
                        std::ostringstream oss; oss << std::fixed << std::setprecision(2) << min_val;
                        result_str = oss.str();
                        break;
                    }
                    case 1: { // max
                        float max_val = seq.reduce([](float a, float b) { return std::max(a, b); }, seq[0]);
                        std::ostringstream oss; oss << std::fixed << std::setprecision(2) << max_val;
                        result_str = oss.str();
                        break;
                    }
                    case 2: { // sum
                        float sum = seq.reduce([](float a, float b) { return a + b; }, 0.0f);
                        std::ostringstream oss; oss << std::fixed << std::setprecision(2) << sum;
                        result_str = oss.str();
                        break;
                    }
                    case 3: { // product
                        float prod = seq.reduce([](float a, float b) { return a * b; }, 1.0f);
                        std::ostringstream oss; oss << std::fixed << std::setprecision(2) << prod;
                        result_str = oss.str();
                        break;
                    }
                    case 4: { // average
                        float sum = seq.reduce([](float a, float b) { return a + b; }, 0.0f);
                        float avg = sum / static_cast<float>(seq.size());
                        std::ostringstream oss; oss << std::fixed << std::setprecision(2) << avg;
                        result_str = oss.str();
                        break;
                    }
                    default: result_str = "неизвестная функция reduce";
                }
            } else if constexpr (std::is_same_v<T, char>) {
                auto is_vowel = [](char c) {
                    char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                    return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
                };
                auto is_consonant = [is_vowel](char c) {
                    return std::isalpha(static_cast<unsigned char>(c)) && !is_vowel(c);
                };
                auto is_digit_char = [](char c) {
                    return std::isdigit(static_cast<unsigned char>(c));
                };
                switch (selected_reduce_func) {
                    case 0: { // количество гласных
                        int count = seq.reduce([is_vowel](int acc, char c) { return acc + (is_vowel(c) ? 1 : 0); }, 0);
                        result_str = std::to_string(count);
                        break;
                    }
                    case 1: { // количество цифр
                        int count = seq.reduce([is_digit_char](int acc, char c) { return acc + (is_digit_char(c) ? 1 : 0); }, 0);
                        result_str = std::to_string(count);
                        break;
                    }
                    case 2: { // количество согласных
                        int count = seq.reduce([is_consonant](int acc, char c) { return acc + (is_consonant(c) ? 1 : 0); }, 0);
                        result_str = std::to_string(count);
                        break;
                    }
                    case 3: { // максимальный ASCII-код
                        int max_ascii = seq.reduce([](int a, char c) { return std::max(a, static_cast<int>(c)); }, static_cast<int>(seq[0]));
                        result_str = std::to_string(max_ascii);
                        break;
                    }
                    default: result_str = "неизвестная функция reduce";
                }
            } else if constexpr (std::is_same_v<T, bit<BitType>>) { // BitType
                // Для битовых последовательностей reduce не был определён в интерфейсе, но на всякий случай реализуем
                switch (selected_reduce_func) {
                    case 0: { // не ноль (количество ненулевых)
                        int count = seq.reduce([](int acc, bit<BitType> x) { return acc + (x != 0 ? 1 : 0); }, 0);
                        result_str = std::to_string(count);
                        break;
                    }
                    case 1: { // нечётные (количество)
                        int count = seq.reduce([](int acc, bit<BitType> x) { return acc + ((x & 1) ? 1 : 0); }, 0);
                        result_str = std::to_string(count);
                        break;
                    }
                    case 2: { // >256 (количество)
                        int count = seq.reduce([](int acc, bit<BitType> x) { return acc + (x > 256 ? 1 : 0); }, 0);
                        result_str = std::to_string(count);
                        break;
                    }
                    default: result_str = "неизвестная функция reduce";
                }
            }
            last_result = "Результат reduce: " + result_str;
        }
        else if (selected_mode == 5) { // where
            std::function<bool(const T&)> pred;
            if constexpr (std::is_same_v<T, int>) {
                switch (selected_where_func) {
                    case 0: pred = [](const T& x) { return x % 3 == 0; }; break;
                    case 1: pred = [](const T& x) { return x <= 0; }; break;
                    case 2: pred = [](const T& x) { return x >= 0; }; break;
                    case 3: pred = [](const T& x) { return (x >= 100 && x <= 999) || (x <= -100 && x >= -999); }; break;
                    case 4: pred = [](const T& x) { return (x >= 1000 && x <= 9999) || (x <= -1000 && x >= -9999); }; break;
                    default: pred = [](const T&) { return true; };
                }
            } else if constexpr (std::is_same_v<T, float>) {
                switch (selected_where_func) {
                    case 0: pred = [](const T& x) { return std::abs(x - std::round(x)) > 1e-6; }; break; // не целое
                    case 1: pred = [](const T& x) { return x <= 0.0f; }; break;
                    case 2: pred = [](const T& x) { return x >= 0.0f; }; break;
                    default: pred = [](const T&) { return true; };
                }
            } else if constexpr (std::is_same_v<T, char>) {
                switch (selected_where_func) {
                    case 0: pred = [](char c) { return std::isupper(static_cast<unsigned char>(c)) != 0; }; break;
                    case 1: pred = [](char c) { return std::islower(static_cast<unsigned char>(c)) != 0; }; break;
                    case 2: pred = [](char c) { return std::isalpha(static_cast<unsigned char>(c)) != 0; }; break;
                    case 3: pred = [](char c) { return std::isdigit(static_cast<unsigned char>(c)) != 0; }; break;
                    default: pred = [](char) { return true; };
                }
            } else if constexpr (std::is_same_v<T, bit<BitType>>) { // BitType
                switch (selected_where_func) {
                    case 0: pred = [](bit<BitType> x) { return x != 0; }; break;
                    case 1: pred = [](bit<BitType> x) { return (x & 1) != 0; }; break;
                    case 2: pred = [](bit<BitType> x) { return x > 256; }; break;
                    default: pred = [](bit<BitType> x) { return true; };
                }
            }
            seq.where(pred);
            update_display_items();
        }
    } catch (const index_out_of_range& e) {
        last_result = "Ошибка: " + std::string(e.what());
    } catch (const invalid_argument& e) {
        last_result = "Ошибка: " + std::string(e.what());
    } catch (const empty_container& e) {
        last_result = "Ошибка: " + std::string(e.what());
    } catch (const null_ptr& e) {
        last_result = "Ошибка: " + std::string(e.what());
    } catch (const size_mismatch& e) {
        last_result = "Ошибка: " + std::string(e.what());
    } catch (const std::exception& e) {
        last_result = "Ошибка: " + std::string(e.what());
    } catch (...) {
        last_result = "Неизвестная ошибка";
    }
}

void start_() {
    using namespace ftxui;
    auto screen = ScreenInteractive::Fullscreen();

    std::string input_str;
    std::string input_idx;

    // Компоненты выбора
    Component container_settings = Container::Vertical({
        Dropdown(container, &selected_container),
        Dropdown(data_type, &selected_data_type),
        Dropdown(mode, &selected_mode)
    });

    // Поля ввода
    Component input_value_append = Input(&input_str, "введите значение") | border;
    Component input_value_prepend = Input(&input_str, "введите значение") | border;
    Component input_value_insert = Container::Vertical({
        Input(&input_idx, "введите индекс") | border,
        Input(&input_str, "введите значение") | border
    });

    // Вкладки выбора функций
    Component map_functions_int = Dropdown(map_func_for_int, &selected_map_func);
    Component map_functions_float = Dropdown(map_func_for_float, &selected_map_func);
    Component map_functions_char = Dropdown(map_func_for_char, &selected_map_func);
    Component map_tab = Container::Tab({
        map_functions_int, map_functions_float, map_functions_char
    }, &selected_data_type);

    Component where_functions_int = Dropdown(where_func_for_int, &selected_where_func);
    Component where_functions_float = Dropdown(where_func_for_float, &selected_where_func);
    Component where_functions_char = Dropdown(where_func_for_char, &selected_where_func);
    Component where_tab = Container::Tab({
        where_functions_int, where_functions_float, where_functions_char
    }, &selected_data_type);

    Component reduce_functions_int = Dropdown(reduce_func_for_int, &selected_reduce_func);
    Component reduce_functions_float = Dropdown(reduce_func_for_float, &selected_reduce_func);
    Component reduce_functions_char = Dropdown(reduce_func_for_char, &selected_reduce_func);
    Component reduce_tab = Container::Tab({
        reduce_functions_int, reduce_functions_float, reduce_functions_char
    }, &selected_data_type);

    Component mode_handler = Container::Tab({
        input_value_append,   // 0
        input_value_prepend,  // 1
        input_value_insert,   // 2
        map_tab,              // 3
        reduce_tab,           // 4
        where_tab             // 5
    }, &selected_mode);

    // Меню отображения элементов
    auto menu = Menu(&display_items, &::selected_item);
    auto display_window = menu | Renderer([&](Element inner) {
        return window(text("Список"), inner) | size(HEIGHT, LESS_THAN, 20);
    });

    // Строка состояния
    auto status_line = Renderer([&] {
        return text(last_result) | color(Color::YellowLight);
    });

    // Основной вертикальный контейнер
    Component main_content = Container::Vertical({
        container_settings,
        mode_handler,
        display_window,
        status_line
    });

    // Получение текущей последовательности
    auto get_current_seq = [&]() -> std::variant<
        list_seq<Mutability::Mutable, int>*,
        list_seq<Mutability::Mutable, float>*,
        list_seq<Mutability::Mutable, char>*,
        array_seq<Mutability::Mutable, int>*,
        array_seq<Mutability::Mutable, float>*,
        array_seq<Mutability::Mutable, char>*,
        bit_seq<Mutability::Mutable, BitType>*
    > {
        if (selected_container == 0) { // list
            switch (selected_data_type) {
                case 0: return &my_list_i;
                case 1: return &my_list_f;
                case 2: return &my_list_c;
            }
        } else if (selected_container == 1) { // array
            switch (selected_data_type) {
                case 0: return &my_array_i;
                case 1: return &my_array_f;
                case 2: return &my_array_c;
            }
        } else if (selected_container == 2) { // bit
            return &my_bit_seq;
        }
        return &my_list_i; // fallback
    };

    // Обработчик событий
    auto event_handler = CatchEvent(main_content, [&](Event event) {
        if (event == Event::Return) {
            int idx = -1;
            if (!input_idx.empty()) {
                try { idx = std::stoi(input_idx); }
                catch (...) { idx = -1; }
            }
            auto seq_var = get_current_seq();
            std::visit([&](auto* seq) {
                if (!seq) return;
                using SeqType = std::decay_t<decltype(*seq)>;
                using T = typename SeqType::value_type;
                apply_modify_op<SeqType, Mutability::Mutable, T>(*seq, input_str, idx, 0);
                update_display_items();
                input_str.clear();
                input_idx.clear();
            }, seq_var);
            return true;
        }
        else if (event == Event::Delete) {
            delete_selected();
            update_display_items();
            return true;
        }
        return false;
    });

    // Финальный рендерер
    auto final_renderer = Renderer(event_handler, [&] {
        return hbox({
            vbox({container_settings->Render()}) | vcenter,
            separator(),
            vbox({mode_handler->Render()}) | vcenter,
            separator(),
            vbox({
                text("Элементы (выберите и нажмите Delete)") | center,
                menu->Render() | vscroll_indicator | frame | size(HEIGHT, GREATER_THAN, 10),
                separator(),
                status_line->Render() | center
            }) | flex
        }) | border | bgcolor(LinearGradient().Angle(180)
                              .Stop(Color::DeepSkyBlue1, 0.f)
                              .Stop(Color::Cyan2, 1.f));
    });

    screen.Loop(final_renderer);
}



int main(){
    start_();
    return 0;
}