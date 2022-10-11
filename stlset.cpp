#include <iostream>
#include <set>
//#include <time.h>
#include <unordered_set>
using namespace std;

int main () {
        set <int> s;
        //set emplace
        long st_s_e = clock();
        for(int i =0; i < 100000; ++i) {
                s.emplace(rand() % 10000 +1);
        }
        long end_s_e = clock();
        //set find
        /*
        long st_s_f = clock();
        for(int i =0; i < 100000; ++i) {
                s.find(rand() % 10000 +1);
        }
        long end_s_f = clock();
        */
        //set cout
        long set_emplace_time = end_s_e - st_s_e;
        cout << "set emplace duration is equal : " << set_emplace_time  << endl;
        //long set_find_time = end_s_f - st_s_f;
        //cout << "set find duration is equal : " << set_find_time << endl;

        unordered_set <int> us;
        //unorderd set emplace
        long st_us_e = clock();
        for(int i =0; i < 100000; ++i) {
                us.emplace(rand() % 10000 +1);
        }
        long end_us_e = clock();
        //unorderd set find
        /*
        long st_us_f = clock();
        for(int i =0; i < 100000; ++i) {
                us.find(rand() % 10000 +1);
        }
        long end_us_f = clock();
        */
        //unorderd set cout
        long uset_emplace_time = end_us_e - st_us_e;
        cout << "us emplace duration is equal :" << uset_emplace_time  << endl;
        //long uset_find_time = end_us_f - st_us_f;
        //cout << "us find duration is equal :" << uset_find_time  << endl;

        set_emplace_time < uset_emplace_time ? cout << "set emplace is faster" << endl : cout << "unordered set emplace is faster" << endl;
        //set_find_time < uset_find_time ? cout << "set find is faster" << endl : cout << "unordered set find is faster" << endl;
        return 0;
}