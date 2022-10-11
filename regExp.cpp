#include <iostream>
#include <regex>
using namespace std;
int main(){
	regex r1("^Arm[a-z]*");
	regex greedy("J.*n");
	regex lazy("J.*?n");
	smatch match;
	
	string text1 = "Armeny asac Armanin gnel Armenia konyaky";
	string text2 = "John Jeferson is not an Armenian";

	while(regex_search(text1, match, r1)){
		cout << match[0] << endl;
		text1 = match.suffix().str();
	}
	while(regex_search(text2, match,lazy)){
		cout << match[0] << endl;
		text2 = match.suffix().str();
	}
	return 0;	
}