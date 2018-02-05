#ifndef MIPSASSEMBLERSIMULATOR_CODEGEN_H
#define MIPSASSEMBLERSIMULATOR_CODEGEN_H

#include <iostream>
#include <map>

struct writeback_position_t {
    writeback_position_t() = default;
    writeback_position_t(std::streampos pos, std::ostream *os) : position(pos), stream(os) {}

    std::streampos position;
    std::ostream *stream;
};

class Codegen {
  public:
    Codegen(const writeback_position_t &text, const writeback_position_t &data)
        : text(text), data(data), current(const_cast<writeback_position_t *>(&text)) {}

    void in_text_section() { current = &text; }

    void in_data_section() { current = &data; }

    template <typename T> void emit(const T &val) {
        current->stream->write(reinterpret_cast<char *>(&val), sizeof(T));
    }

    template <typename T, size_t n> void emit_n(const T &val) {
        for (size_t i = 0; i < n; ++i) {
            current->stream->write(reinterpret_cast<char *>(&val), sizeof(T));
        }
    };

    void emit_string(const std::string &str) { current->stream->write(str.c_str(), str.size()); }

    void label_here(const std::string &name);

  private:
    using labels_t = std::map<std::string, writeback_position_t>;
    using pending_balance_t = std::multimap<std::string, writeback_position_t>;

  private:
    labels_t labels;
    pending_balance_t pending_balance;
    writeback_position_t text;
    writeback_position_t data;
    writeback_position_t *current;
};

#endif // MIPSASSEMBLERSIMULATOR_CODEGEN_H
