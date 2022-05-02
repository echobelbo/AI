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
struct cmp {
    bool operator()(status* a, status* b)
    {
        return ((a->h + a->depth) >= (b->h + b->depth));
    }

};
struct status* status_init(status* p)
{
    p = (struct status*)malloc(sizeof(status));
    p->zero = -1;
    p->h = MAX;
    p->depth = -1;
    return p;
}
H_type h_1(const int now[5][5], const int target[5][5])
{
    H_type result = 0;
    for (int i = 0;i < 5;i++)
    {
        for (int j = 0;j < 5;j++)
        {
            if (now[i][j] > 0 && now[i][j] != target[i][j]) result++;
        }
    }
    return result;
}
// H_type h_2(const int now[5][5], const int target[5][5])
// {

// }
// struct status* move(status *p, )  

status* up(status* p, status* target)
{
    target = status_init(target);
    for (int i = 0;i < 5;i++)
    {
        for (int j = 0;j < 5;j++)
            target->now[i][j] = p->now[i][j];
    }
    target->zero = p->zero;
    target->depth = p->depth + 1;
    for (int i = 0;i < target->depth - 1;i++)
    {
        target->path[i] = p->path[i];
    }
    target->path[target->depth - 1] = 'U';
    // int temp = p->now[p->zero/5 - 1][p->zero%5];
    if (target->zero == 2)
    {
        if (target->now[4][2] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[4][2];
            target->now[4][2] = 0;
            target->zero = 22;
        }
        else return NULL;
    }
    else if (target->zero < 5)
        return NULL;
    else
    {
        if (target->now[target->zero / 5 - 1][target->zero % 5] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[target->zero / 5 - 1][target->zero % 5];
            target->now[target->zero / 5 - 1][target->zero % 5] = 0;
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
    target = status_init(target);
    for (int i = 0;i < 5;i++)
    {
        for (int j = 0;j < 5;j++)
            target->now[i][j] = p->now[i][j];
    }
    target->zero = p->zero;
    target->depth = p->depth + 1;
    for (int i = 0;i < target->depth - 1;i++)
    {
        target->path[i] = p->path[i];
    }
    target->path[target->depth - 1] = 'D';
    // int temp = p->now[p->zero/5 - 1][p->zero%5];
    if (target->zero == 22)
    {
        if (target->now[0][2] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[0][2];
            target->now[0][2] = 0;
            target->zero = 2;
        }
        else return NULL;
    }
    else if (target->zero >= 20)
        return NULL;
    else
    {
        if (target->now[target->zero / 5 + 1][target->zero % 5] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[target->zero / 5 + 1][target->zero % 5];
            target->now[target->zero / 5 + 1][target->zero % 5] = 0;
            target->zero = target->zero + 5;
        }
        else return NULL;
    }
    return target;
}

status* right(status* p, status* target)
{
    target = status_init(target);
    for (int i = 0;i < 5;i++)
    {
        for (int j = 0;j < 5;j++)
            target->now[i][j] = p->now[i][j];
    }
    target->zero = p->zero;
    target->depth = p->depth + 1;
    for (int i = 0;i < target->depth - 1;i++)
    {
        target->path[i] = p->path[i];
    }
    target->path[target->depth - 1] = 'R';
    // int temp = p->now[p->zero/5 - 1][p->zero%5];
    if (target->zero == 14)
    {
        if (target->now[2][0] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[2][0];
            target->now[2][0] = 0;
            target->zero = 10;
        }
        else return NULL;
    }
    else if (target->zero % 5 == 4)
        return NULL;
    else
    {
        if (target->now[target->zero / 5][target->zero % 5 + 1] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[target->zero / 5][target->zero % 5 + 1];
            target->now[target->zero / 5][target->zero % 5 + 1] = 0;
            target->zero = target->zero + 1;
        }
        else return NULL;
    }
    return target;
}

status* left(status* p, status* target)
{
    target = status_init(target);
    for (int i = 0;i < 5;i++)
    {
        for (int j = 0;j < 5;j++)
            target->now[i][j] = p->now[i][j];
    }
    target->zero = p->zero;
    target->depth = p->depth + 1;
    for (int i = 0;i < target->depth - 1;i++)
    {
        target->path[i] = p->path[i];
    }
    target->path[target->depth - 1] = 'L';
    // int temp = p->now[p->zero/5 - 1][p->zero%5];
    if (target->zero == 10)
    {
        if (target->now[2][4] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[2][4];
            target->now[2][4] = 0;
            target->zero = 14;
        }
        else return NULL;
    }
    else if (target->zero % 5 == 0)
        return NULL;
    else
    {
        if (target->now[target->zero / 5][target->zero % 5 - 1] > 0)
            // return true;
        {
            target->now[target->zero / 5][target->zero % 5] = target->now[target->zero / 5][target->zero % 5 - 1];
            target->now[target->zero / 5][target->zero % 5 - 1] = 0;
            target->zero = target->zero - 1;
        }
        else return NULL;
    }
    return target;
}



void A_h1(const int start[5][5], const int target[5][5])
{
    priority_queue<status*, vector<status*>, cmp> Q;
    status* start_status = NULL;
    // status* target_status = NULL;
    start_status = status_init(start_status);
    start_status->depth = 0;
    // target_status = status_init(target_status);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5;j++)
        {
            start_status->now[i][j] = start[i][j];
            // target_status->now[i][j] = target[i][j];
            if (start_status->now[i][j] == 0) start_status->zero = i * 5 + j;
            // if (target_status->now[i][j] == 0) target_status->zero = i + j * 5;
        }
    }
    start_status->h = h_1(start_status->now, target);
    start_status->depth = 0;
    Q.push(start_status);
    while (!Q.empty())
    {
        status* next = Q.top();
        Q.pop();

        bool check = true;
        for (int i = 0;i < 5;i++)
        {
            for (int j = 0;j < 5;j++)
            {
                if (next->now[i][j] != target[i][j])
                {
                    check = false;
                    break;
                }
            }
            if (!check) break;
        }

        if (check)
        {
            cout << next->path;
            break;
        }
        status* U, * D, * L, * R;
        U = D = L = R = NULL;
        if (U = up(next, U))
        {
            h_1(U->now, target);
            Q.push(U);
        }
        if (D = down(next, D))
        {
            h_1(U->now, target);
            Q.push(D);
        }
        if (L = left(next, L))
        {
            h_1(L->now, target);
            Q.push(L);
        }
        if (R = right(next, R))
        {
            h_1(R->now, target);
            Q.push(R);
        }
    }
    return;
}

int main(/*int argc, char *argv[]*/)
{
    ifstream start_file, target_file;
    start_file.open("./data/input11.txt");
    target_file.open("./data/target11.txt");
    // if (start_file.is_open()) cout << "success\n";


    int start[5][5];
    int target[5][5];
    // start = status_init(start);
    // start->depth = 0;
    // target = status_init(target);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5;j++)
        {
            start_file >> start[i][j];
            target_file >> target[i][j];
        }
    }
    A_h1(start, target);

    start_file.close();
    target_file.close();

    return 0;
}