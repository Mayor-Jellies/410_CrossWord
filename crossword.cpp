//
// Created by James O'Reilly on 1/18/22.
//

#include "crossword.h"


__attribute__((unused)) char crossword::get_char(const unsigned int &r,const unsigned int &c) const{
    return cross[r][c];
}
/*
 * constructor of object takes O(rows*cols) or O(n^2).
 * This is constant as vector resize only once and its time complexity is added IE:
 *      O(rows*cols)+O(rows*cols) = O(2(rows*cols)) ~ O(rows*cols);
 * removing cross.resize does not make code more efficient as it means
 *      addition conditions in the nested loops and
 *      amortization of time complexity due to vector dynamic resizing
 */
crossword::crossword(const unsigned int &r, const unsigned int &c, const std::string &in) : rows(r), cols(c){
    cross.resize(rows, std::vector<char>(cols)); //O(rows*cols)
    char temp;//O(1)
    //loop is O(rows*cols)
    for(int Ri = 0; Ri < rows; ++Ri){
        for (int Ci = 0; Ci < cols; ++Ci) {
            temp = in.at((Ri*cols)+Ci);
            if(temp==' ')
                temp='.';
            cross[Ri][Ci] = temp;
        }
    }
}

__attribute__((unused)) std::string crossword::printCross() const{
    std::stringstream out;
    out<<"Rows: "<<rows<<"\n";
    out<<"Columns: "<<cols<<"\n";
    for (int i = 0; i < rows; i++) {
        out<<std::string(cross[i].begin(),cross[i].end())<<'\n';
    }
    return out.str();
}
/*
 * time complexity of get_word_across is constant with respect to rows. But is variable do to crossword data sensitivity.
 * We will assume amortized constant time complexity due to the high data sensitivity and this function being called
 *      only on cells with valid words.
 * TODO: unsure if 1 letter answers are considered valid
 */
void crossword::get_word_across(std::string &out, const unsigned int &row, const unsigned int &col) const {
    //unsigned int len = 0;
    out.clear();
    for(unsigned i = col; i<cols; i++){
        if(cross[row][i] == '.')
            break;
        out+=cross[row][i];
        //len++;
    }
}
/*
 * time complexity of get_word_down is constant with respect to cols. But is variable do to crossword data sensitivity.
 * We will assume amortized constant time complexity due to the high data sensitivity and this function being called
 *      only on cells with valid words.
 * TODO: unsure if 1 letter answers are considered valid
 */
void crossword::get_word_down(std::string &out, const unsigned int &row, const unsigned int &col) const {
    //unsigned int len = 0;
    out.clear();
    for(unsigned int i = row; i<rows; i++){
        if(cross[i][col] == '.')
            break;
        out+=cross[i][col];
        //len++;
    }
}
/*
 *
 */
bool crossword::valid_word_across(std::string &out, int row, int col) const {
    out.clear();
    if((col-1) < 0){
        if(cross[row][col] != '.'){
            get_word_across(out,row,col);
            return true;
        }
        else{
            return false;
        }
    }
    else if(cross[row][col-1] == '.' && cross[row][col] != '.'){
        get_word_across(out,row,col);
        return true;
    }
    return false;

    //throw std::domain_error("unknown error no condition met in word_across");
}
bool crossword::valid_word_down(std::string &out,  int row,  int col) const {
    out.clear();
    if((row-1) < 0){
        if(cross[row][col] != '.'){
            get_word_down(out,row,col);
            return true;
        }
        else{
            return false;
        }
    }
    else if(cross[row-1][col] == '.' && cross[row][col] != '.'){
        get_word_down(out,row,col);
        return true;
    }
    return false;

    //throw std::domain_error("unknown error no condition met in word_down");

}




