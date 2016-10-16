//******************************************************************************
// Filename:    anh2130_HW_4_1.cpp
// Author:      Adam Hadar, anh2130
// Purpose:     Defining a Set class.
// Edited:      2016-10-16
//******************************************************************************

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Set
{
    private:
        // 1-I
        T values[100];
        // 1-II
        int count;
    public:
        // 1-III
        Set(void): count(0){}
        // 1-IV
        void insert(T val)
        {
            values[count++] = val;
            return;
        }
        // 1-V
        bool findValue(T val)
        {
            for(int i = 0; i < count; ++i)
                if(values[i] == val)
                    return true;
            return false;
        }
};

// 1-VI
int main(void)
{
    // 1-VI-i
    Set<string> mySet;
    string temp;
    // 1-VI-ii
    while(1)
    {
        cout << "Insert string:" << endl;
        cin >> temp;
        if (temp == "DONE")
            break;
        else
            mySet.insert(temp);
    }
    // 1-VI-iii
    cout << "Search for string:" << endl;
    cin >> temp;
    cout << ((mySet.findValue(temp) == false)? "not ": "") << "present" << endl;
    return 0;
}
