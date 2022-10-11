#include <iostream>
#include <fstream>
#include <regex>

using namespace std;
int main(){
	regex vivacell("(\\(?0(77|94|98)\\)?|\\+(\\(?374\\)?)\\s?(77|94|98))\\s?([0-9]{2}[-\\s]?){2}[0-9]{2}");
	regex teams("(\\(?0(33|43|91|96|99)\\)?|\\+(\\(?374\\)?)\\s?(33|43|91|96|99))\\s?([0-9]{2}[-\\s]?){2}[0-9]{2}");
	regex ucom("(\\(?0(55|95)\\)?|\\+(\\(?374\\)?)\\s?(55|95))\\s?([0-9]{2}[-\\s]?){2}[0-9]{2}");
	regex passport("[A][A-Z][0-9]{7}");
	regex date("(([0-2][0-9])|(3[0-1]))[\\/\\.\\-]((0[0-9])|(1[0-2]))[\\/\\.\\-][0-2][0-9]{3}");
    regex name("\\b[A-Z][a-z]{1,50}\\s+[A-Z][a-z]+\\b");
    regex ipv4("(([0-9])|([1-9][0-9])|((1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.){3}([0-9])|([1-9][0-9])|((1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))");
	regex ipv6("([1-9a-f][0-9a-f]{3}:){7}[1-9a-f][0-9a-f]{3}");


    ifstream read;
    read.open("./source.txt");
    string s;
    while(getline(read,s)){
        cout<<"read"<<endl;
    }
    read.close();

    ofstream write;
    write.open("./Destination.txt",ios::app);
    smatch match;
    while(regex_search(s, match, name)){
        write<<match[0]<<"\n";
        s = match.suffix().str();
    }
    write.close();

    return 0;
}