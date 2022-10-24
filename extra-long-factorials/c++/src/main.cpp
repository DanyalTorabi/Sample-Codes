#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'extraLongFactorials' function below.
 *
 * The function accepts INTEGER n as parameter.
 */

///
/// \brief makeVector converts a number to a vector of its digits.
/// \param n determines the number should be converted. The range of input is 1 to (2^31-1).
/// \return A vector of digits is returned.
///
vector<int> makeVector(int n)
{
    vector<int> result;
    
    while(n)
    {
        //! Insert the first right digit of the number in to the left of the result.
        result.insert(result.begin(), n%10);
        //! Remove the first right digit.
        n /= 10;
    }
    return result;
}

///
/// \brief bigIntSum adds the `second` parameter to the `first` parameter.
/// \param first determines the result parameter which is a vector of digits. This vector should have at least one item.
/// \param second determines the value should be which is a vector of digits. This vector should have at least one item.
///
void bigIntSum(vector<int> &first, vector<int> &second)
{
    int carry(0);
    //! Iterate over two numbers from right digit to left digit.
    for(int fInx=first.size()-1, sInx=second.size()-1; fInx>=0 || sInx>=0 ; fInx--, sInx--)
    {
        //! Calculate sum of two digits and the carry digit from last calculation.
        int val( ((fInx<0)?0:first[fInx]) + ((sInx<0)?0:second[sInx]) + carry);
        if(fInx<0)
            ///! Length of first number is less than length of second number. So the result digit should be insert into the result.
            first.insert(first.begin(), val%10);
        else
            //! Replace the result digit into first digit.
            first[fInx] = val%10;
        //! Calculate the next carry.
        carry = val/10;
    }
    if(carry>0)
        //! Insert the carry in to the result array at largest value position.
        first.insert(first.begin(), carry);
}

///
/// \brief bigIntMultiply multiplies two numbers (in vector of digits).
/// \param first determines the first numebr should be multiplied. It is a vector of digits in which the largest value has the lowest index.
/// \param second determines the second number should be multiplied. It is a vector of digits in which the largest value has the lowest index.
/// \return The vectorized result of multiplication of two numbers is returned.
///
vector<int> bigIntMultiply(vector<int> &first, vector<int> second)
{
    //! The strategy is like below for 123*45=5658
    //!   123
    //!  * 46
    //! -----
    //!   138
    //! + 920
    //! +4600
    //! -----
    //!  5658

    vector<int> result;
    int firstSize(first.size());

    //! Iterate over the digits of first number
    for(int firstInx=firstSize-1; firstInx>=0; firstInx--)
    {
        int carry(0);
        vector<int> tmpRes;

        //! Increase the value of temporary result according to the position of digit in the first digit.
        tmpRes.resize(firstSize-1-firstInx, 0);
        //! Multiply one digit of the first number to second number.
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

///
/// \brief extraLongFactorials converts numbers to array of digits to calulate large number factorials.
/// \param n is the input whose factorial should be calculated.
///
void extraLongFactorials(int n)
{
    vector<int> result;
    //! Insert the first result of 1!.
    result.push_back(1);
    while(n)
    {
        result = bigIntMultiply(result, makeVector(n));
        n--;
    }
    /// print the output of digits to screen.
    for(auto digit: result)
        cout << digit;
    cout << endl;
}

int main()
{
    string n_temp;
    //! Read the input line
    getline(cin, n_temp);

    //! Convert the input string to number
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

