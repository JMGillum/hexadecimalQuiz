#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>
#include <limits>


/*

Command-line arguments structure should be: 
    -n --number ~ their number to be converted
    -n flag is optional. Anything without a flag will be interpreted as this
    -b --base ~ the base their number is in ~ Default is base 16 (hexadecimal)
    -o --output ~ the desired base of the output ~ Default is base 10 (decimal)
    -h --help ~ displays a help message then quits

*/

const char validDigits[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void display(uint64_t num, int base = 0);
uint64_t convertBase(std::string str, unsigned base);
void printHelp();

int main(int argc, char *argv[]) {
    bool numberSpecified = false;
    bool baseSpecified = false;
    bool outputSpecified = false;

    std::string numberStr = "";
    std::string baseStr = "";
    std::string outputBaseStr = "";

    int base = 0;
    int outputBase = 0;
    
    if(argc == 1){
        printHelp();
        exit(1);
    }

    if(argc >1){
        std::string argument = "";
        for(int i = 1; i < argc; ++i){
            argument = *(argv+i);
            if(argument == "-n" || argument == "--number"){
                if(numberSpecified){
                    std::cout << "Multiple uses of -n flag is not allowed" << std::endl;
                    exit(1);
                }
                numberSpecified = true;
                if(i+1 < argc){ // If there is another argument after flag
                    if(*(argv+i+1)[0] != '-'){ // If the next argument does not start with '-'
                        numberStr = *(argv+i+1);
                        ++i;
                    } else {
                        std::cout << "No number detected after -n flag" << std::endl;
                        exit(1);
                    }
                } else {
                    std::cout << "No number detected after -n flag" << std::endl;
                    exit(1);
                }
            } 
            
            
            else if(argument == "-b" || argument == "--base"){
                if(baseSpecified){
                    std::cout << "Multiple uses of -b flag is not allowed" << std::endl;
                    exit(1);
                }
                baseSpecified = true;
                if(i+1 < argc){ // If there is another argument after flag
                    if(*(argv+i+1)[0] != '-'){ // If the next argument does not start with '-'
                        baseStr = *(argv+i+1);
                        ++i;
                    } else {
                        std::cout << "No number detected after -b flag" << std::endl;
                        exit(1);
                    }
                } else {
                    std::cout << "No number detected after -b flag" << std::endl;
                    exit(1);
                }
            } 
            
            
            else if(argument == "-o" || argument == "--output"){
                if(outputSpecified){
                    std::cout << "Multiple uses of -o flag is not allowed" << std::endl;
                    exit(1);
                }
                outputSpecified = true;
                if(i+1 < argc){ // If there is another argument after flag
                    if(*(argv+i+1)[0] != '-'){ // If the next argument does not start with '-'
                        outputBaseStr = *(argv+i+1);
                        ++i;
                    } else {
                        std::cout << "No number detected after -o flag" << std::endl;
                        exit(1);
                    }
                } else {
                    std::cout << "No number detected after -o flag" << std::endl;
                    exit(1);
                }
            }


            else if(argument == "-h" || argument == "--help"){
                printHelp();
                exit(1);
            }


            else if(i == argc-1 && !numberSpecified){
                numberStr = argument;
            }
        }
    }

    if(numberStr == ""){
        std::cout << "A number must be specified. Place the number after your flags." << std::endl;
        exit(1);
    }

    if(baseSpecified){
        if(baseStr == "2"){
            base = 2;
        } else if(baseStr == "8"){
            base = 8;
        } else if(baseStr == "10"){
            base = 10;
        } else if(baseStr == "16"){
            base = 16;
        } else {
            std::cout << "Invalid base specified. Supported bases are 2,8,10,16" << std::endl;
            exit(1);
        }
    } else {
        if(numberStr.size() > 2){
            if(numberStr[0] == '0'){
                if(numberStr[1] == 'b' || numberStr[1] == 'B'){
                    base = 2;
                    numberStr.assign(numberStr,2);
                } else if(numberStr[1] == 'o' || numberStr[1] == 'O'){
                    base = 8;
                    numberStr.assign(numberStr,2);
                } else if(numberStr[1] == 'x' || numberStr[1] == 'X'){
                    base = 16;
                    numberStr.assign(numberStr,2);
                } else {
                    base = 8;
                    numberStr.assign(numberStr,1);
                }
            } else {
                base = 10;
            }
        } else {
            base = 10;
        }
    }


    if(outputSpecified){
        if(outputBaseStr == "2"){
            outputBase = 2;
        } else if(outputBaseStr == "8"){
            outputBase = 8;
        } else if(outputBaseStr == "10"){
            outputBase = 10;
        } else if(outputBaseStr == "16"){
            outputBase = 16;
        } else {
            std::cout << "Invalid output base specified. Supported bases are 2,8,10,16" << std::endl;
            exit(1);
        }
    }

    uint64_t num = convertBase(numberStr,base);
    //std::cout << "NUM: " << num << std::endl;
    display(num,outputBase);
    


    return 0;
}

void display(uint64_t num, int base){

    // Displays the numbers
    std::cout << std::showbase;
    if(base == 16 || base == 0){
        std::cout << std::hex << "Hexadecimal: " << num << std::endl;
    }
    if(base == 10 || base == 0){
        std::cout << std::dec << "Decimal: " << num << std::endl;
    }
    if(base == 18 || base == 0){
        std::cout << std::oct << "Octal: " << num << std::endl;
    }
    if(base == 2 || base == 0){
        // Gets the binary representation of the number
        std::string binary = "";
        while(num>0){
            if(num&1){
                binary = '1' + binary;
            } else {
                binary = '0' + binary;
            }
            num >>= 1;
        }
        while(binary.size() > 1 && binary[0] == '0'){
            binary.assign(binary,1);
        }
        std::cout << "Binary: " << binary <<std::endl;
    }
    // Resets display settings
    std::cout << std::dec << std::noshowbase;
}


uint64_t convertBase(std::string str, unsigned base){
    if(base != 2 && base != 8 && base != 10 && base != 16) {
        std::cout << "Invalid base entered" << std::endl;
        exit(1);
    }
    uint64_t value = 0;
    int charVal;
    int powerOfTwo = 0;
    if(base == 2){
        powerOfTwo = 1;
    } else if(base == 8){
        powerOfTwo = 3;
    } else if(base == 16){
        powerOfTwo = 4;
    }
    
    for(unsigned i = 0; i < str.size(); ++i){
        //std::cout << i << ": " << str[i];
        charVal = -1;
        for(unsigned j = 0; j < base; ++j){
            if(std::tolower(validDigits[j]) == std::tolower(str[i])){
                charVal = j;
                break;
            }
        }
        //std::cout << "~" << charVal << std::endl;
        if(charVal < 0){
            std::cout << "Invalid character detected" << std::endl;
            exit(1);
        }
        
        if(base != 10){
            uint64_t val = std::pow(2,(((str.size()-1)*powerOfTwo)-(powerOfTwo*i))) * charVal;
            value += val;
            //std::cout << std::hex << std::left << std::setw(17) << val << ": " << value << std::endl;
        } else {
            uint64_t val = std::pow(10,((str.size()-1)-i)) * charVal;
            value += val;
            //std::cout << std::hex << std::left << std::setw(17) << val << ": " << value << std::endl;
        }
    }
    return value;
}


void printHelp(){
    std::cout << "Usage: <executable> [options] <number>" << std::endl;
    std::cout << "Options:\n  <number>\tNumber to be converted. Required. Base specifiers " << std::endl;
    std::cout << "\t\t(0b=2,0=8,0x=16) can preceed the number to allow inferring\n";
    std::cout << "\t\tthe base of the number"<< std::endl;
    std::cout << "  -b <number>\tBase of the specified number. Can be 2,8,10,16. Default is 10" << std::endl;
    std::cout << "  -o <number>\tBase of the number output. Can be 2,8,10,16. If not specified\n";
    std::cout << "\t\tthe value will be displayed in the 4 bases" << std::endl;
}