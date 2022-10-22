#include <bits/stdc++.h>
#include "test.h"

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'extraLongFactorials' function below.
 *
 * The function accepts INTEGER n as parameter.
 */

vector<int> makeVector(int n)
{
    vector<int> result;
    
    while(n)
    {
        result.insert(result.begin(), n%10);
        n /= 10;
    }
    return result;
}

void bigIntSum(vector<int> &first, vector<int> &second)
{
    int carry(0);
    
    for(int fInx=first.size()-1, sInx=second.size()-1; fInx>=0 || sInx>=0 ; fInx--, sInx--)
    {
        int val( ((fInx<0)?0:first[fInx]) + ((sInx<0)?0:second[sInx]) + carry);
        if(fInx<0)
            first.insert(first.begin(), val%10);
        else
            first[fInx] = val%10;
        carry = val/10;
    }
    if(carry>0)
        first.insert(first.begin(), carry);
}

vector<int> bigIntMultiply(vector<int> &first, vector<int> second)
{
    vector<int> result;
    int firstSize(first.size());
    for(int firstInx=firstSize-1; firstInx>=0; firstInx--)
    {
        int carry(0);
        vector<int> tmpRes;
        for(int inx=firstSize-1; inx>firstInx; inx--)
            tmpRes.push_back(0);
        for(int secondInx=second.size()-1; secondInx>=0; secondInx--)
        {
            int val(first[firstInx] * second[secondInx] + carry);
            tmpRes.insert(tmpRes.begin(), val%10);
            carry = val / 10;
        }
        if(carry>0)
            tmpRes.insert(tmpRes.begin(), carry);
        bigIntSum(result, tmpRes);
    }
    return result;
}

void extraLongFactorials(int n) {
    vector<int> result;
    result.push_back(1);
    while(n)
    {
        result = bigIntMultiply(result, makeVector(n));
        n--;
    }
    for(auto digit: result)
        cout << digit;
    cout << endl;
}

int main()
{
    MYMIN(10,11);
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    extraLongFactorials(n);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

