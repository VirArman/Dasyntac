#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream> 
#include <regex>
#include <vector>

using namespace std;

vector<uint8_t> myVector;
uint8_t pars = 0;

void parsing();
void read();
void logic();
void swop();
void utf16be_utf8();
void utf16le_utf8();
void utf8_utf16le();
void utf8_utf16be();

char* argv1;
char* argv2;
char* argv3;
char* argv4;


int main(int argc, char** argv)
{
    if(argc != 5)
    {
        cout << "Wrong quantity of arguments" << endl;
        cout << "As first argument enter the coding type of the source file" << endl;
        cout << "As second argument enter the codng type of the result" << endl;
        cout << "As third argument enter the name of source file" << endl;
        cout << "As fourth argument enter the name of result file" << endl;
        cout << "For example \" ./a.out utf8 utf16 source.txt destination.txt \"" << endl;
    }
    else
    {
        try
        {
            argv1 = argv[1];
            argv2 = argv[2];
            argv3 = argv[3];
            argv4 = argv[4];
            parsing();
            read();
            logic();
        }
        catch(const out_of_range& ex)
        {
            cout << ex.what() << endl << endl;
        }

    }
    
    
    return 0;
    
}

void parsing()
{
    string temp;
    smatch matches; 
    regex txt("(\\.txt)$", regex_constants::icase);
    regex utf8("^(utf[\\-\\_]?8)$", regex_constants::icase);
    regex utf16be("^(utf[\\-\\_]?16be)$", regex_constants::icase);
    regex utf16le("^(utf[\\-\\_]?16le)$", regex_constants::icase); 
    regex utf16("^(utf[\\-\\_]?16)$", regex_constants::icase);

    temp = argv3;
    regex_search(temp, matches, txt);
    if (!matches.empty())
    {
        pars = pars | 0b00000010;
    }

    temp = argv4;
    regex_search(temp, matches, txt);
    if (!matches.empty())
    {
        pars = pars | 0b00000001;
    }

    temp = argv1;
    regex_search(temp, matches, utf8);
    if (!matches.empty())
    {
        pars = pars | 0b00001000;
    }
    regex_search(temp, matches, utf16be);
    if (!matches.empty())
    {
        pars = pars | 0b01000000;
    }
    regex_search(temp, matches, utf16le);
    if (!matches.empty())
    {
        pars = pars | 0b10000000;
    }
    regex_search(temp, matches, utf16);
    if (!matches.empty())
    {
        pars = pars | 0b11000000;
    }

    temp = argv2;
    regex_search(temp, matches, utf8);
    if (!matches.empty())
    {
        pars = pars | 0b00000100;
    }
    regex_search(temp, matches, utf16be);
    if (!matches.empty())
    {
        pars = pars | 0b00010000;
    }
    regex_search(temp, matches, utf16le);
    if (!matches.empty())
    {
        pars = pars | 0b00100000;
    }
    regex_search(temp, matches, utf16);
    if (!matches.empty())
    {
        pars = pars | 0b00110000;
    }
}

void read()
{    
    FILE* frptr = fopen(argv3, "r");

    fseek(frptr, 0L, SEEK_END);

    size_t  size = ftell(frptr);

    myVector.resize(size); 
    
    fseek(frptr, 0L, SEEK_SET);

    fread(&myVector[0], 1, size, frptr); 
    fclose(frptr);

}

void logic()
{
    switch (pars)
    {
    case 0:

        cout << "None of the argument is right" << endl;
        break;
    case 1:

        cout << "You have entered wrong extentions" << endl;
        cout << "Please use only .txt extension" << endl;
        break;
    case 3:
        cout << "You have entered wrong encoding type" << endl;
        cout << "Please enter  utf8 or utf16 or utf16be or utf16be" << endl;
        break;
    case 15:
        cout << "I will not convert from utf8 to utf8" << endl;
        break;
    case 27:
        read();
        if (!((myVector.at(0) == 0xfe) || (myVector.at(0) == 0xff)))
        {
            utf8_utf16be();
        }
        break;
    case 43:
        read();
        if (!((myVector.at(0) == 0xfe) || (myVector.at(0) == 0xff)))
        {   
            utf8_utf16le();
        }
        break;
    case 59:
        read();
        if (!((myVector.at(0) == 0xfe) || (myVector.at(0) == 0xff)))
        {   
            utf8_utf16be();
        }
        break;
    case 71:
        read();
        if ((myVector.at(0) == 0xfe) && (myVector.at(1) == 0xff))
        {  
            utf16be_utf8();
        }
        else
        {
            cout << "File encoding does not look like utf16be" << endl;
        }
        break;
    case 83:
        cout << "I will not convert from utf16be to utf16be" << endl;
        break;
    case 99:
        read();
        if ((myVector.at(0) == 0xfe) && (myVector.at(1) == 0xff))
        {
            swop();
        }
        else
        {
            cout << "File encoding does not look like utf16be" << endl;
        }
        break;
    case 115:
        read();
        if ((myVector.at(0) == 0xfe) && (myVector.at(1) == 0xff))
        {   
            swop();
        }
        else
        {
            cout << "File encoding does not look like utf16be"<< endl;
        }
        break;
    case 135:
        read();
        if ((myVector.at(0) == 0xff) && (myVector.at(1) == 0xfe))
        {   
            utf16le_utf8();
        }
        else
        {
            cout << "File encoding does not look like utf16le" << endl;
        }
        break;
    case 147:
        read();
        if ((myVector.at(0) == 0xff) && (myVector.at(1) == 0xfe))
        {   
            swop();
        }
        else
        {
            cout << "File encoding does not look like utf16le" << endl;
        }
        break;
    case 163:
        cout << "I will not convert from utf16le to utf16le" << endl;
        break;
    case 179:
        read();
        if ((myVector.at(0) == 0xff) && (myVector.at(1) == 0xfe))
        {   
            swop();
        }
        else
        {
            cout << "File encoding does not look like utf16le" << endl;
        }
        break;
    case 199:
        read();
        if ((myVector.at(0) == 0xff) && (myVector.at(1) == 0xfe))
        {   
            utf16le_utf8();
        }
        else if ((myVector.at(0) == 0xfe) && (myVector.at(1) == 0xff))
        {   
            utf16be_utf8();
        }
        else
        {
            cout << "File encoding does not look like utf16" << endl;
        }
        break;
    case 243:
        read();
        if (((myVector.at(0) == 0xff) && (myVector.at(1) == 0xfe)) || ((myVector.at(0) == 0xfe) && (myVector.at(1) == 0xff)))
        {
            swop();
        }
        else
        {
            cout << "File encoding does not look like utf16" << endl;
        }
        break;

    default:
        cout << "Some argument were given wrong" << endl;
        break;
    }
    
}

void swop()
{
    FILE* fwptr = fopen(argv4, "w");

    for(int i = 0; i < myVector.size(); i+=2)
    {                          
        fwrite(&myVector[i + 1], 1, 1, fwptr); 
        fwrite(&myVector[i], 1, 1, fwptr);
    }
    fclose(fwptr);
}

void utf16be_utf8()
{
    FILE* fwptr = fopen(argv4, "w"); 
    
    for (int i = 2; i < myVector.size(); ++i)
    {
        if (myVector[i] == 0)
        {   
            ++i;
            fwrite(&myVector[i], 1, 1, fwptr);  
        }
        else
        {
            uint8_t highByte = myVector[i];
            ++i;
            uint8_t lowByte = myVector[i]; 
            lowByte = lowByte & 0b00111111;     
            lowByte = lowByte | 0b10000000;     
            highByte = highByte << 2;           
            uint8_t temp = myVector[i] >> 6;    
            highByte = highByte | temp;         
            highByte = highByte | 0b11000000;   
            fwrite(&highByte, 1, 1, fwptr);
            fwrite(&lowByte, 1, 1, fwptr);
        }
    }
    fclose(fwptr);
}

void utf16le_utf8()
{
    FILE* fwptr = fopen(argv4, "w"); 
    
    for (int i = 2; i < myVector.size(); ++i)
    {
        if (myVector[i + 1] == 0) 
        {   
            fwrite(&myVector[i], 1, 1, fwptr);
            ++i;
        }
        else
        {
            uint8_t lowByte = myVector[i];     
            uint8_t temp = myVector[i];         
            temp = temp >> 6;                  
            ++i;
            uint8_t highByte = myVector[i];    

            highByte = highByte << 2;            
            highByte = highByte | temp;         
            highByte = highByte | 0b11000000;   
            lowByte = lowByte & 0b00111111;      
            lowByte = lowByte | 0b10000000;     
            fwrite(&highByte, 1, 1, fwptr);
            fwrite(&lowByte, 1, 1, fwptr);
        }
    }
    fclose(fwptr);
}

void utf8_utf16le()
{
    uint8_t bom1 = 0xff;
    uint8_t bom2 = 0xfe;
    uint8_t zero = 0;
    uint8_t highByte;
    uint8_t lowByte;
    uint8_t temp;
    FILE* fwptr = fopen(argv4, "w"); 
  
    fwrite(&bom1, 1, 1, fwptr);
    fwrite(&bom2, 1, 1, fwptr);
    for (int i = 0; i < myVector.size(); ++i)
    {
        if (myVector[i] > 0 && myVector[i] < 127)
        {
            fwrite(&myVector[i], 1, 1, fwptr);
            fwrite(&zero, 1, 1, fwptr);
        }
        else if (myVector[i] >= 192 && myVector[i] <= 223) 
        {
            highByte = myVector[i] & 0b00011111; 
            temp = myVector[i] << 6;
            highByte = highByte >> 2;
            ++i;
            lowByte = myVector[i] & 0b00111111; 
            lowByte = lowByte | temp;
            fwrite(&lowByte, 1, 1, fwptr);
            fwrite(&highByte, 1, 1, fwptr);

        }
        
    }
    fclose(fwptr);
}
void utf8_utf16be()
{
    uint8_t bom1 = 0xfe;
    uint8_t bom2 = 0xff;
    uint8_t zero = 0;
    uint8_t highByte;
    uint8_t lowByte;
    uint8_t temp;
    FILE* fwptr = fopen(argv4, "w"); 
  
    fwrite(&bom1, 1, 1, fwptr);
    fwrite(&bom2, 1, 1, fwptr);
    for (int i = 0; i < myVector.size(); ++i)
    {
        if (myVector[i] > 0 && myVector[i] < 127)
        {
            fwrite(&zero, 1, 1, fwptr);
            fwrite(&myVector[i], 1, 1, fwptr);
        }
        else if (myVector[i] >= 192 && myVector[i] <= 223) 
        {
            highByte = myVector[i] & 0b00011111; 
            temp = myVector[i] << 6;
            highByte = highByte >> 2;
            ++i;
            lowByte = myVector[i] & 0b00111111; 
            lowByte = lowByte | temp;
            fwrite(&highByte, 1, 1, fwptr);
            fwrite(&lowByte, 1, 1, fwptr);
        }
    }
    fclose(fwptr);
} 