#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<set>
#include<map>
#include<queue>
#include<vector>

#define H_type int

#define MAX 100000000


using namespace std;
void A_h1(const int start[5][5], const int target[5][5]);
void A_h2(const int start[5][5], const int target[5][5]);
void IDA_h1(const int start[5][5], const int target[5][5]);
void IDA_h2(const int start[5][5], const int target[5][5]);
struct status {
    int zero;
    int now[5][5];
    H_type h;
    int depth;
    char path[50];
};
struct cmp{
    bool operator()(status &a, status &b){
        return ( (a.h + a.depth) >= (b.h + b.depth));
    }
};

H_type h_1(const int now[5][5], const int target[5][5])
{
    H_type result = 0;
    for(int i = 0;i < 5;i++)
    {
        for(int j = 0;j < 5;j++)
        {
            if(now[i][j] > 0 && now[i][j] != target[i][j]) result++;               
        }
    }
    return result;
}
H_type h_2(const int now[5][5], const int target[5][5])
{

}
// struct status* move(status *p, )  
void A_h1(const int start[5][5], const int target[5][5])
{

}
status* up(status* p, status* target)
{
    status_init(target);
    for(int i = 0;i < 5;i++)
    {
        for(int j = 0;j < 5;j++)
            target->now[i][j] = p->now[i][j];
    }
    target->zero = p->zero;
    target->depth = p->depth + 1;
    for(int i = 0;i < p->depth;i++)
    {
        
    }
    // int temp = p->now[p->zero/5 - 1][p->zero%5];
    if(target->zero == 2)
    {
        if(target->now[4][2] > 0)
            // return true;
        {
            target->now[target->zero/5][target->zero%5] = target->now[4][2];
            target->now[4][2] = 0;
            target->zero = 22;
        }
        else return NULL;
    }
    else if(target->zero < 5)
        return NULL;
    else
    {
        if(target->now[target->zero/5 - 1][target->zero%5] > 0)
            // return true;
        {
            target->now[target->zero/5][target->zero%5] = target->now[target->zero/5 - 1][target->zero%5];
            target->now[target->zero/5 - 1][target->zero%5] = 0;
            target->zero = target->zero - 5;     
        }
        else return NULL;
    }
    return target;
}

// bool down(status* p)
// {
//     if(p->zero == 22)
//     {
//         if(p->now[0][2] > 0)
//             return true;
//         else return false;
//     }
//     else if(p->zero >= 20)
//         return false;
//     else
//     {
//         if(p->now[p->zero/5 + 1][p->zero%5] > 0)
//             return true;
//         else return false;
//     }
// }
status* down(status* p, status* target)
{
    status_init(target);
    for(int i = 0;i < 5;i++)
    {
        for(int j = 0;j < 5;j++)
            target->now[i][j] = p->now[i][j];
    }
    target->zero = p->zero;
    target->depth = p->depth + 1;
    target->from = 'D';
    // int temp = p->now[p->zero/5 - 1][p->zero%5];
    if(target->zero == 22)
    {
        if(target->now[0][2] > 0)
            // return true;
        {
            target->now[target->zero/5][target->zero%5] = target->now[0][2];
            target->now[0][2] = 0;
            target->zero = 2;
        }
        else return NULL;
    }
    else if(target->zero >= 20)
        return NULL;
    else
    {
        if(target->now[target->zero/5 + 1][target->zero%5] > 0)
            // return true;
        {
            target->now[target->zero/5][target->zero%5] = target->now[target->zero/5 + 1][target->zero%5];
            target->now[target->zero/5 + 1][target->zero%5] = 0;
            target->zero = target->zero + 5;     
        }
        else return NULL;
    }
    return target;
}
// bool right(status* p)
// {
//     if(p->zero == 14)
//     {
//         if(p->now[2][0] > 0)
//             return true;
//         else return false;
//     }
//     else if(p->zero%5 == 4)
//         return false;
//     else
//     {
//         if(p->now[p->zero/5][p->zero%5 + 1] > 0)
//             return true;
//         else return false;
//     }
// }
status* right(status* p, status* target)
{
    status_init(target);
    for(int i = 0;i < 5;i++)
    {
        for(int j = 0;j < 5;j++)
            target->now[i][j] = p->now[i][j];
    }
    target->zero = p->zero;
    target->depth = p->depth + 1;
    target->from = 'R';
    // int temp = p->now[p->zero/5 - 1][p->zero%5];
    if(target->zero == 14)
    {
        if(target->now[2][0] > 0)
            // return true;
        {
            target->now[target->zero/5][target->zero%5] = target->now[2][0];
            target->now[2][0] = 0;
            target->zero = 10;
        }
        else return NULL;
    }
    else if(target->zero%5 == 4)
        return NULL;
    else
    {
        if(target->now[target->zero/5][target->zero%5 + 1] > 0)
            // return true;
        {
            target->now[target->zero/5][target->zero%5] = target->now[target->zero/5][target->zero%5 + 1];
            target->now[target->zero/5][target->zero%5 + 1] = 0;
            target->zero = target->zero + 1;     
        }
        else return NULL;
    }
    return target;
}

// bool left(status* p)
// {
//     if(p->zero == 10)
//     {
//         if(p->now[2][4] > 0)
//             return true;
//         else return false;
//     }
//     else if(p->zero%5 == 0)
//         return false;
//     else
//     {
//         if(p->now[p->zero/5][p->zero%5 - 1] > 0)
//             return true;
//         else return false;
//     }
// }
status* left(status* p, status* target)
{
    status_init(target);
    for(int i = 0;i < 5;i++)
    {
        for(int j = 0;j < 5;j++)
            target->now[i][j] = p->now[i][j];
    }
    target->zero = p->zero;
    target->depth = p->depth + 1;
    target->from = 'L';
    // int temp = p->now[p->zero/5 - 1][p->zero%5];
    if(target->zero == 10)
    {
        if(target->now[2][4] > 0)
            // return true;
        {
            target->now[target->zero/5][target->zero%5] = target->now[2][4];
            target->now[2][4] = 0;
            target->zero = 14;
        }
        else return NULL;
    }
    else if(target->zero%5 == 0)
        return NULL;
    else
    {
        if(target->now[target->zero/5][target->zero%5 - 1] > 0)
            // return true;
        {
            target->now[target->zero/5][target->zero%5] = target->now[target->zero/5][target->zero%5 - 1];
            target->now[target->zero/5][target->zero%5 - 1] = 0;
            target->zero = target->zero - 1;     
        }
        else return NULL;
    }
    return target;
}
char A_star(status* p, status* target, bool mode, priority_queue<status*, vector<status*>, cmp> Q)
{
    bool check = true;
    for(int i = 0;i < 5;i++)
    {
        for(int j = 0;j < 5;j++)
        {
            if(p->now[i][j] != target->now[i][j])
            {
                check = false;
                break;
            }
                
        }
    }
    if(check)
        return (path[p->depth] = '\0');

    status* U, * L, * R, * D;
    if(U = up(p, U))
    {
        if(mode)
           U->h = h_1(U->now, target->now);
        else
           U->h = h_2(U->now, target->now);
        Q.push(U);
    }
    if(L = up(p, L))
    {
        if(mode)
           L->h = h_1(L->now, target->now);
        else
           L->h = h_2(L->now, target->now);
        Q.push(L);
    }
    if(R = up(p, R))
    {
        if(mode)
           R->h = h_1(R->now, target->now);
        else
           R->h = h_2(R->now, target->now);
        Q.push(R);
    }
    if(D = up(p, D))
    {
        if(mode)
           D->h = h_1(D->now, target->now);
        else
           D->h = h_2(D->now, target->now);
        Q.push(D);
    }
    status* next;
    next = Q.top();
    return()
}
struct status* status_init(status* p)
{
    p = (struct status*)malloc(sizeof(status));
    p->zero = -1;
    p->h = MAX;
    p->depth = -1;
    return p;
}



int main(/*int argc, char *argv[]*/)
{
    ifstream start_file, target_file;
    start_file.open("./data/input11.txt");
    target_file.open("./data/target11.txt");
    // if (start_file.is_open()) cout << "success\n";
    status* start = NULL;
    status* target = NULL;
    start = status_init(start);
    start->depth = 0;
    target = status_init(target);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5;j++)
        {
            start_file >> start->now[i][j];
            target_file >> target->now[i][j];
            if (start->now[i][j] == 0) start->zero = i + j * 5;
            if (target->now[i][j] == 0) target->zero = i + j * 5;
            // cout << start->now[i][j]<<endl;
        }
    }


    start_file.close();
    target_file.close();

    return 0;
}