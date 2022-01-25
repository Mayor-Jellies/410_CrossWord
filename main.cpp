#include <iostream>
#include <fstream>
#include "crossword.h"
#include <stdexcept>
#include <queue>
/*
 * This function is O(1) assuming file buffer>>to string is constant. This time complexity is constant non amortized assuming a valid file is given.
 * */
void parse_file(unsigned int &rows, unsigned int &cols, std::string &out, const std::string &filename){
    std::ifstream infile(filename, std::ios::in);
    if( !infile.is_open() ){
        throw std::invalid_argument("unknown error no condition met in word_down");
    }
    double version;
    infile>>version;
    if(version != 1.0){
        throw std::bad_function_call();
    }
    infile>>out;
    if(out!="Crossword"){
        throw std::bad_function_call();
    }
    out.clear();
    infile>>rows;
    infile>>cols;
    infile.get(); //remove extra new line
    std::getline(infile,out);
    infile.close();
}
/*
 * This function runs in O(rows*cols) or O(n^2) amortized. This assumes valid_word_down() is constant.
 * Valid_word_down() is constant with respect to rows and cols but is data-sensitive to the underling crossword.
 * Exception handling is ignored with respect to time complexity.
 * */
void getWords(const crossword &cross, std::queue<std::pair<int, std::string>> &words_across, std::queue<std::pair<int, std::string>> &words_down){
    int clue_num=1;
    bool flag;

    std::string temp;

    for(int r=0; r < cross.rows; r++){
        for(int c=0; c < cross.cols; c++){
            flag=false;
            try{
                if(cross.valid_word_down(temp, r, c)) {
                    words_down.emplace(clue_num, temp);
                    flag = true;
                }
            }catch(const std::domain_error& error){
                std::cerr<<error.what()<<std::endl;
            }
            try{
                if (cross.valid_word_across(temp, r, c)) {
                    words_across.emplace(clue_num, temp);
                    flag = true;
                }
            }catch(const std::domain_error& error){
                std::cerr<<error.what()<<std::endl;
            }
            clue_num+=flag; //this avoids a comparison operation but is less readable.
        }
    }
}
/*
 * This function waits for user input time complexity is irrelevant. The time complexity would be O(1) assuming perfect user.
 */
std::string get_testFile(){
    using namespace std;
    string input;
    cout<<"Test File Path/Name: "<<flush;
    getline(cin,input);
    return input;
}
/*
 *
 */
int main() {
    std::string a;
    unsigned int row,col;
    while(true) { //error handling loop, not considered for time complexity.
        try {
            parse_file(row, col, a, get_testFile());
            break;
        } catch (const std::invalid_argument& error) {
            std::cout << "404 file not found" << std::endl;
        }
    }
    crossword test(row,col,a);

    std::queue<std::pair<int,std::string>> words_across;
    std::queue<std::pair<int,std::string>> words_down;

    getWords(test,words_across,words_down); //O(rows*cols)


    std::cout<<"########\n"<<"Words Across:\n"<<std::endl;
    while(!words_across.empty()){
        std::cout<<std::to_string(words_across.front().first)<<" : "<<words_across.front().second<<std::endl;
        words_across.pop();
    }

    std::cout<<"########\n"<<"Words Down:\n";
    while(!words_down.empty()){
        std::cout<<std::to_string(words_down.front().first)<<" : "<<words_down.front().second<<std::endl;
        words_down.pop();
    }
}




