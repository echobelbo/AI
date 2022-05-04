#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
// #include<set>
// #include<map>
// #include<queue>
#include<vector>
// #include<stack>



#define MAX 100000000
#define OUT cout

using namespace std;

// int sheet.work_sheet[7][7];
// int work_sheet2[7][10];//0代表未定，1代表工作，2代表休假

struct sheet1
{
    int work_sheet[7][7];
};

struct sheet2
{
    int work_sheet[7][10];
};

bool csp_1_1(int day, int worker, sheet1 sheet);
bool csp_1_2(int day, int worker, sheet1 sheet);
bool csp_2_1(int day, int worker, sheet2 sheet);
bool csp_2_2(int day, int worker, sheet2 sheet);

bool check1(int worker, int day, sheet1 sheet)
{
    //确定工作时检测
    int s = 0;
    for(int i = 0;i < 7;i++)
    {
        if(sheet.work_sheet[i][worker] == 1)
            s++;
    }
    if(s > 5) return false;
    else return true;
}

bool check1_(int worker, int day, sheet2 sheet)
{
    //确定工作时检测
    int s = 0;
    for(int i = 0;i < 7;i++)
    {
        if(sheet.work_sheet[i][worker] == 1)
            s++;
    }
    if(s > 5) return false;
    else return true;
}

bool check2(int worker, sheet1 sheet)
{
    //确定休假时需检测
    if(                                                                                   \
    (sheet.work_sheet[0][worker] == 2 && sheet.work_sheet[1][worker] == 2 && sheet.work_sheet[2][worker] == 2) || \
    (sheet.work_sheet[1][worker] == 2 && sheet.work_sheet[2][worker] == 2 && sheet.work_sheet[3][worker] == 2) || \
    (sheet.work_sheet[2][worker] == 2 && sheet.work_sheet[3][worker] == 2 && sheet.work_sheet[4][worker] == 2) || \
    (sheet.work_sheet[3][worker] == 2 && sheet.work_sheet[4][worker] == 2 && sheet.work_sheet[5][worker] == 2) || \
    (sheet.work_sheet[4][worker] == 2 && sheet.work_sheet[5][worker] == 2 && sheet.work_sheet[6][worker] == 2)    )
            return false;
    else 
        return true;
}

bool check2_(int worker, sheet2 sheet)
{
    //确定休假时需检测
    if(                                                                                   \
    (sheet.work_sheet[0][worker] == 2 && sheet.work_sheet[1][worker] == 2 && sheet.work_sheet[2][worker] == 2) || \
    (sheet.work_sheet[1][worker] == 2 && sheet.work_sheet[2][worker] == 2 && sheet.work_sheet[3][worker] == 2) || \
    (sheet.work_sheet[2][worker] == 2 && sheet.work_sheet[3][worker] == 2 && sheet.work_sheet[4][worker] == 2) || \
    (sheet.work_sheet[3][worker] == 2 && sheet.work_sheet[4][worker] == 2 && sheet.work_sheet[5][worker] == 2) || \
    (sheet.work_sheet[4][worker] == 2 && sheet.work_sheet[5][worker] == 2 && sheet.work_sheet[6][worker] == 2)    )
            return false;
    else 
        return true;
}
// bool check3(int day)
// {
//     for(int i = 0; i < 7;i++)
//     {    
//         if(sheet.work_sheet[day][i] == 0 || sheet.work_sheet[day][i] == 1) return true;
//     }
//     return false;
// }

bool check3(int day, sheet1 sheet)
{
    //确定休假时检测
    int s = 0;
    for(int i = 0; i < 7; i++)
    {
        if(sheet.work_sheet[day][i] == 2) s++;
    }
    if(s > 3)
        return false;
    else
        return true;
}

bool check3_(int day, sheet2 sheet)
{
    //确定休假时检测
    int s = 0;
    for(int i = 0; i < 10; i++)
    {
        if(sheet.work_sheet[day][i] == 2) s++;
    }
    if(s > 5)
        return false;
    else
        return true;
}

bool check4_(int day, sheet2 sheet)
{
    //确定高级人员休假时检测
    if(sheet.work_sheet[day][0] == 2 &&
    sheet.work_sheet[day][1] == 2 &&
    sheet.work_sheet[day][7] == 2 &&
    sheet.work_sheet[day][9] == 2 ) 
        return false;
    else 
        return true;
}

bool csp_1_1(int day, int worker, sheet1 sheet)
{
    bool check = true;
    sheet.work_sheet[day][worker] = 1;
    if(worker == 0) 
    {
        if(sheet.work_sheet[day][3] == 1)
            check = false;
        else
            sheet.work_sheet[day][3] = 2;
        // sheet.work_sheet[day][1] = 1;
        check = check && check2(3, sheet);
        check = check && check3(day, sheet);     
    }
    if(worker == 1)
    {
        if(sheet.work_sheet[day][2] == 1)
            check = false;
        else
            sheet.work_sheet[day][2] = 2;
        check = check && check2(2, sheet);
        check = check && check3(day, sheet);
    }
    if(worker == 2)
    {
        if(sheet.work_sheet[day][1] == 1)
            check = false;
        else
            sheet.work_sheet[day][1] == 2;
        if(sheet.work_sheet[day][5] == 1)
            check = false;
        else
            sheet.work_sheet[day][5] == 2;
        if(sheet.work_sheet[day][0] == 2)
            check = false;
        else
            sheet.work_sheet[day][0] = 1;
        check = check && check1(0, day, sheet);
        check = check && check2(1, sheet);
        check = check && check2(5, sheet);
        check = check && check3(day, sheet);
    }
    if(worker == 3)
    {
        if(sheet.work_sheet[day][0] == 1)
            check = false;
        else
            sheet.work_sheet[day][0] = 2;
        if(sheet.work_sheet[day][1] == 2)
            check = false;
        else
            sheet.work_sheet[day][1] = 1;
        check = check && check1(1, day, sheet);
        check = check && check2(0, sheet);
        check = check && check3(day, sheet);
        
    }
    if(worker == 5)
    {
        if(sheet.work_sheet[day][2] == 1)
            check = false;
        else
            sheet.work_sheet[day][2] == 2;
        check = check && check2(2, sheet);
        check = check && check3(day, sheet);
    }
    check = check && check1(worker, day, sheet);
    if(!check) return check;
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 7;j++)
        {
            if(sheet.work_sheet[i][j] != 0) continue;
            else
            {
                return csp_1_1(i, j, sheet) || csp_1_2(i, j, sheet);                
            }
        }
    }
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 7;j++)
        {
            if(sheet.work_sheet[i][j] == 1) OUT << j + 1 << " ";
        }
        OUT << endl;
    }
    return true;
}

bool csp_1_2(int day, int worker, sheet1 sheet)
{
    bool check = true;
    sheet.work_sheet[day][worker] = 2;
    if(worker == 0)
    {
        if(sheet.work_sheet[day][1] == 2)
            check = false;
        else
            sheet.work_sheet[day][1] = 1;
        if(sheet.work_sheet[day][2] == 1)
            check = false;
        else
            sheet.work_sheet[day][2] = 2;
        check = check && check2(2, sheet);
        check = check && check1(1, day, sheet);
    }
    if(worker == 1)
    {
        if(sheet.work_sheet[day][0] == 2)
            check = false;
        else
            sheet.work_sheet[day][0] = 1;
        if(sheet.work_sheet[day][3] == 1)
            check = false;
        else
            sheet.work_sheet[day][3] = 2;
        check = check && check2(3, sheet);
        check = check && check1(0, day, sheet);
    }
    check = check && check2(worker, sheet);
    check = check && check3(day, sheet);
    if(!check) return check;
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 7;j++)
        {
            if(sheet.work_sheet[i][j] != 0) continue;
            else
            {
                return csp_1_1(i, j, sheet) || csp_1_2(i, j, sheet);                
            }
        }
    }
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 7;j++)
        {
            if(sheet.work_sheet[i][j] == 1) OUT << j + 1 << " ";
        }
        OUT << endl;
    }
    return true;

}
bool csp_2_1(int day, int worker, sheet2 sheet)
{
    bool check = true;
    sheet.work_sheet[day][worker] = 1;

    if(worker == 0)
    {
        if(sheet.work_sheet[day][4] == 1)
            return false;
        else
            sheet.work_sheet[day][4] == 2;
        check = check && check2_(4, sheet);
        check = check && check3_(4, sheet);
    }
    if(worker == 1)
    {
        if(sheet.work_sheet[day][5] == 1)
            return false;
        else
            sheet.work_sheet[day][5] == 2;
        check = check && check2_(5, sheet);
        check = check && check3_(5, sheet);
    }
    if(worker == 4)
    {
        if(sheet.work_sheet[day][0] == 1)
            return false;
        else
            sheet.work_sheet[day][0] == 2;
        check = check && check2_(0, sheet);
        check = check && check3_(0, sheet);
    }
    if(worker == 5)
    {
        if(sheet.work_sheet[day][1] == 1)
            return false;
        else
            sheet.work_sheet[day][1] == 2;
        check = check && check4_(day, sheet);
        check = check && check2_(1, sheet);
        check = check && check3_(1, sheet);
    }
    if(worker == 7)
    {
        if(sheet.work_sheet[day][9] == 1)
            return false;
        else
            sheet.work_sheet[day][9] == 2;
        check = check && check4_(day, sheet);
        check = check && check2_(9, sheet);
        check = check && check3_(9, sheet);
    }
    if(worker == 9)
    {
        if(sheet.work_sheet[day][7] == 1)
            return false;
        else
            sheet.work_sheet[day][7] == 2;
        check = check && check4_(day, sheet);
        check = check && check2_(7, sheet);
        check = check && check3_(7, sheet);
    }
    check = check && check1_(worker, day, sheet);
    if(!check) return check;
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 10;j++)
        {
            if(sheet.work_sheet[i][j] != 0) continue;
            else
            {
                return csp_2_1(i, j, sheet) || csp_2_2(i, j, sheet);                
            }
        }
    }
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 10;j++)
        {
            if(sheet.work_sheet[i][j] == 1) OUT << j + 1 << " ";
        }
        OUT << endl;
    }
    return true;

}
bool csp_2_2(int day, int worker, sheet2 sheet)
{
    bool check = true;
    sheet.work_sheet[day][worker] = 2;
    if(worker == 0 || worker == 1 || worker == 7 || worker == 9)
        check = check && check4_(day, sheet);
    check = check && check2_(worker, sheet);
    check = check && check3_(day, sheet);
    if(!check) return check;
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 10;j++)
        {
            if(sheet.work_sheet[i][j] != 0) continue;
            else
            {
                return csp_2_1(i, j, sheet) || csp_2_2(i, j, sheet);                
            }
        }
    }
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 10;j++)
        {
            if(sheet.work_sheet[i][j] == 1) OUT << j + 1 << " ";
        }
        OUT << endl;
    }
    return true;

}
int main()
{
    sheet1 output1;
    sheet2 output2;
    // output1 = (sheet1*)malloc(sizeof(sheet1));
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 7;j++)
        {
            output1.work_sheet[i][j] = 0;
        }
    }
    if(!(csp_1_1(0,0, output1) || csp_1_2(0,0,output1))) OUT << "no answer" << endl;
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 10;j++)
        {
            output2.work_sheet[i][j] = 0;
        }
    }
    if(!(csp_2_1(0,0, output2) || csp_2_2(0,0,output2))) OUT << "no answer" << endl;
    return 0;
}