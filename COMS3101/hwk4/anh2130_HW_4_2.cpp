//******************************************************************************
// Filename:    anh2130_HW_4_2.cpp
// Author:      Adam Hadar, anh2130
// Purpose:     Defining a Map class.
// Edited:      2016-10-16
//******************************************************************************

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

template <class K, class V>
class MyMap
{
    private:
        // 2-I
        K keys[100];
        // 2-II
        V values[100];
        // 2-III
        int count;
    public:
        // 2-IV
        MyMap(void): count(0){}
        // 2-V
        void insert(K key, V& val)
        {
            keys[count] = key;
            values[count++] = val;
            return;
        }
        // 2-VI
        bool findValue(K key, V& val)
        {
            for(int i = 0; i < count; ++i)
                if(keys[i] == key)
                {
                    val = values[i];
                    return true;
                }
            return false;
        }
        // 2-VII
        bool findKey(K& key, V val)
        {
            for(int i = 0; i < count; ++i)
                if(values[i] == val)
                {
                    key = keys[i];
                    return true;
                }
            return false;
        }
};

// 2-VIII
int main(void)
{
    // 2-VIII-i
    MyMap<string,int> phonebook;
    string t_name, t_str_number;
    int t_int;
    // 2-VIII-ii
    while(1)
    {
        cout << "Enter name, then number:" << endl;
        cin >> t_name;
        if(t_name=="DONE")
            break;
        cin >> t_str_number;
        if(t_str_number=="DONE")
            break;
        else
        {
            t_int = atoi(t_str_number.c_str());
            phonebook.insert(t_name, t_int);
        }
    }
    // 2-VIII-iii
    cout << "Search by string:" << endl;
    cin >> t_name;
    if (phonebook.findValue(t_name,t_int))
        cout << t_int << endl;
    else
        cout << "not present" << endl;
    // 2-VIII-iv
    cout << "Search by int:" << endl;
    cin >> t_int;
    cout << (phonebook.findKey(t_name,t_int)? t_name: "not present") << endl;
    return 0;
}
