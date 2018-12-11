#include<iostream>
#include <cmath>
#include"m_stack.h"
#include<vector>
using namespace std;

bool compare(char item1, char item2);
float accumulate(float item1, float item2, char m_operator);
bool judge(char*p);

int main()
{
    char*express=new char[100];
    m_stack<char>M_operator;
    m_stack<float>M_num;
    do
    {
        cout << "Please input your expressions:" << endl;
        cin >> express;
    } while (!judge(express));
    int num_count = 0;                     //º∆ ˝’ª÷––° ˝µƒ ˝¡ø
    int char_count = 0;                    //º∆ ˝’ª÷–◊÷∑˚µƒ ˝¡ø
    float point_num = 0;                   //¥Ê–° ˝µƒ≤ø∑÷
    float int_num = 0;                     //¥Ê’˚ ˝µƒ≤ø∑÷
    vector<int>point_arry;                    //¥Ê–° ˝µƒ ˝◊÷
    vector<int> int_arry;                      //¥Ê’˚ ˝µƒ ˝◊÷
    int i = 0;
    int flag = 1;                          //≈–∂œ «∑Òº”∏∫∫≈;
    int step = 0;
    while(i<strlen(express))
    {
        if (express[i] == '-')
        {
            if(express[i-1]>=48&&express[i-1]<=57&&i!=0||express[i-1]==')')
            {
                M_operator.push('+');
                char_count++;
            }
            flag ++;
            i++;
        }
        else if (express[i] == '.')
        {
            i++;
            while (i < strlen(express)&&express[i]>=48&&express[i]<=57)
            {
                point_arry.push_back(express[i]-48);
                i++;
            }
            for (int i = 0; i < int_arry.size(); i++)
            {
                int_num += int_arry[i] * pow(10, int_arry.size() - i - 1);
            }
            for (int i = 0; i < point_arry.size(); i++)
            {
                point_num += point_arry[i] * pow(10, -(i + 1));
            }
            int_arry.clear();
            point_arry.clear();
            M_num.push((flag%2==0? -int_num - point_num:int_num+point_num));
            flag = 1;
            num_count++;
            int_num = 0;
            point_num = 0;
        }
        else if (express[i]>=48&&express[i]<=57)
        {
            while (i < strlen(express) && express[i] >= 48 && express[i] <= 57)
            {
                int_arry.push_back(express[i] - 48);
                i++;
            }
            if (express[i] != '.')
            {
                for (int i = 0; i < int_arry.size(); i++)
                {
                    int_num += int_arry[i] * pow(10, int_arry.size() - i - 1);
                }
                int_arry.clear();
                M_num.push((flag%2==0?-int_num:int_num));
                flag = 1;
                int_num = 0;
                num_count++;
            }
        }
        else
        {
            char_count++;
            M_operator.push(express[i]);
            i++;
        }
        if ((num_count >= 2 && char_count >= 2 )||express[i-1]=='#')
        {
            char temp = M_operator.pop();
            char_count--;
            while (compare(M_operator.top(), temp))
            {
                float num_temp1 = M_num.pop();
                float num_temp2 = M_num.pop();
                M_num.push(accumulate(num_temp2,num_temp1,M_operator.pop()));
                num_count--;
                char_count--;
                if (M_operator.empty())
                    break;
            }
            if (temp == ')')
            {
                M_operator.pop();
                char_count--;
            }
            else
            {
                M_operator.push(temp);
                char_count++;
            }
        }
        step++;
        cout << "≤Ω÷Ë" << step << ":" << "‘ÀÀ„∑˚’ª£∫";
        M_operator.print();
        cout << " ˝æ›’ª£∫";
        M_num.print();
        cout << endl;
    }
    cout << M_num.top()<<endl;
    //system("pause");
}
bool compare(char item1, char item2)
{
    if (item1 == '(')
        return false;
    char m_operator[5][2] = { {'#'} ,{ ')' },{ '+','-' },{ '*','/' },{ '(' } };
    int index1 = 0, index2 = 0;
    for (int i = 0; i<=4; i++)
    {
        for (int j = 0; j<2; j++)
        {
            if (m_operator[i][j] == item1)
                index1 = i;
            else if (m_operator[i][j] == item2)
                index2 = i;
        }
    }
    if (index2 <= index1)
        return true;
    else
        return false;
}
float accumulate(float item1, float item2, char m_operator)
{
    switch (m_operator)
    {
        case '+':
            return item1 + item2;
            break;
        case '-':
            return item1 - item2;
            break;
        case'*':
            return item1 * item2;
            break;
        case '/':
            return item1 / item2;
            break;
    }
    return 1.0;
}
bool judge(char*p)
{
    int left = 0, right = 0;
    for (int i = 0; i < strlen(p); i++)
    {
        if (i == 0 && (p[i] == ')' || p[i] == '.' || p[i] == '/' || p[i] == '*' || p[i] == '#' || p[i] == '+'))                   //≈≈≥˝µ⁄“ª∏ˆŒª÷√µƒ≤ª∫œ¬ﬂº≠µƒ∑˚∫≈
        {
            cout << "Invalid Synatx In " << (i + 1) << " Position!!! " << endl;
            return false;
        }
        else if ((p[i] == ')' || p[i] == '/' || p[i] == '*' || p[i] == '#' || p[i] == '+') && ((p[i - 1] > 57 || p[i - 1] < 48) && p[i - 1] != ')'))           //¡Ω∏ˆ∑˚∫≈¡¨‘⁄“ª∆µƒ«Èøˆ
        {
            cout << "Invalid Synatx: The" << p[i] << " in " << i + 1 << "position is invalid!!! " << endl;
            return false;
        }
        else if (p[i] == '.' && (p[i - 1] > 57 && p[i - 1] < 48))                                                                  //–° ˝µ„∫Û∑« ˝◊÷
        {
            cout << "Invalid Synatx: The " << p[i] << " in " << i + 1 << " position is invalid!!!  " << endl;
            return false;
        }
        else if (p[i] == ')')
        {
            for (int j = i; j >= 0; j--)
            {
                if (p[j] == '(')
                {
                    break;
                }
                if (j == 0 && p[j] != '(')
                {
                    cout << "Invalid Synatx: No valid '(' match to ')'!!!" << endl;                                         //¿®∫≈≤ª∆•≈‰
                    return false;
                }
            }
        }
        if (p[i] == '(')
            left++;
        if (p[i] == ')')
            right++;
        if (i == strlen(p) - 1 && p[i] != '#')
        {
            cout << "No # end!!!";
            return false;
        }
    }
    if (left != right)
    {
        cout << "Invalid Synatx: The number of '(' is not equal to ')'" << endl;
        return false;
    }
    return true;
}

