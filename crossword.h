//
// Created by James O'Reilly on 1/18/22.
//

#ifndef CROSSWORD_CROSSWORD_H
#define CROSSWORD_CROSSWORD_H

#include <sstream>
#include <vector>

class crossword {
private:
    std::vector<std::vector<char>> cross;
public:
    const unsigned int rows;
    const unsigned int cols;

    __attribute__((unused))  __attribute__((deprecated("direct access supported"))) char get_char(const unsigned int &r, const unsigned int &c) const;

    void get_word_across(std::string &out, const unsigned int &row, const unsigned int &col) const;
    void get_word_down(std::string &out, const unsigned int &row, const unsigned int &col) const;

    crossword(const unsigned int &r, const unsigned int &c, const std::string &in);

    __attribute__((unused)) std::string printCross() const;
    bool valid_word_down(std::string &out,  int row,  int col) const;
    bool valid_word_across(std::string &out,  int row,  int col) const;

};


#endif //CROSSWORD_CROSSWORD_H
