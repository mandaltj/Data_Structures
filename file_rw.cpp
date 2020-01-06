#include <fstream>    //Required for ifstream and ofstream
#include <iostream>
#include <vector>

//Code to read from a file and store all the words seprated by space into a vector string
int main(){
    std::string filename = "README.md";
    std::ifstream infile(filename);
    if(!infile) {
        infile.close();
        throw std::runtime_error("Could not load file: " + filename);
    }

    //Storing the strings in a Vector of strings
    std::vector<std::string> file_string_list;

    std::string line;
    while (std::getline(infile, line)){
        while(line.length() > 0){
            //std::cout<<"Length of line: "<<line.length()<<'\n';
            int char_count = 0;
            std::string single_word = "";
            for (char c : line){
                if (c == ' '){
                    line = line.substr(char_count+1);
                    break;
                }
                char_count++;
                single_word += c;
                //std::cout<<single_word<<'\n';
            }

            if (char_count == line.length()){
                line = line.substr(char_count);
            }
            file_string_list.push_back(single_word);
        }
    }

    std::cout<<"Printing out the strings: \n";
    for(auto get_str: file_string_list){
        std::cout<<get_str<<'\n';
    }

    return 0;
}
