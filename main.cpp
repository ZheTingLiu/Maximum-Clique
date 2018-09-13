#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstring>
#include <thread>
#include <mutex>
#include <time.h>
#include <algorithm>

using namespace std;

#define MAX_ROW 82168
#define MAX_COLUMN 10271
// function define
void find_clique(int start,int end);
void Writetotxt();
// globoal variable
char adjMatrix[MAX_ROW][MAX_COLUMN];
int maxlength = 0;
int *maxclique;
int *keep;
int total_length;
int condition;
time_t t_start;
const char* inputFile;
const char* outputFile;
mutex m;



int main(int argc, char *argv[]){
    t_start = time(NULL);
    inputFile = argv[1];
    outputFile = argv[2];
    cout<<"Load File"<<endl;
    maxclique = new int[MAX_ROW];
    int idx[2] = {-1,-1};
    keep = new int[MAX_ROW];
    total_length = 0;
    freopen(inputFile,"r", stdin);
    string line;
    while(!getline(cin, line).eof())
    {
        vector<int> arr;
        istringstream ssline(line);
        string number;
        int i=0;
        while(getline(ssline, number, ' '))
        {
            idx[i] = (atoi(number.c_str()));
            i++;
            
        }
        adjMatrix[idx[0]][idx[1]/8]|= 1 << (7-idx[1]%8);
        adjMatrix[idx[1]][idx[0]/8]|= 1 << (7-idx[0]%8);
    }
    fclose(stdin);
    //int degree=0;
    /*
    for(int i=0; i<82168;i++)
    {
        degree = 0;
        for(int j=0; j<82169; j++)
        {
            if((adjMatrix[i][j/8]>>(7-(j%8)))&1==1)
                degree++;
        }
        if(degree>=1200)
            *(keep+length)=i;
    }
    */
    cout<<"Finish load. Cost "<<time(NULL)-t_start<<"s"<<endl;
    int index = 0;
    int start,end;
    index = MAX_ROW/8;
    start = 0; end = index;
    thread thread1(find_clique,start,end);//
    start = index; end = index*2;
    thread thread2(find_clique,start,end);
    start = index*2; end = index*3;
    thread thread3(find_clique,start,end);
    start = index*3; end = index*4;
    thread thread4(find_clique,start,end);
    start = index*4; end = index*5;
    thread thread5(find_clique,start,end);
    start = index*5; end = index*6;
    thread thread6(find_clique,start,end);
    start = index*6; end = index*7;
    thread thread7(find_clique,start,end);
    start = index*7; end = MAX_ROW;
    thread thread8(find_clique,start,end);




    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();
    thread8.join();

    cout<<"Total cost "<<time(NULL)-t_start<<"s"<<endl;
    
    return 0;
}

void find_clique(int start,int end)
{  
    int *clique;
    clique = new int[MAX_ROW];
    for(int i=0;i<MAX_ROW;i++)
    {   
        *(clique+i)=-1;
    }
    int now = 0;
    int xx = 0;
    int length=0;
    int *tmp = new int[MAX_ROW];
    for(int i=start; i<end;i++)
    {   
        //if(i%5000==0)
        //    cout<<"Row "<<i<<endl;
        clique[0]=i;
        for(int j=i+1; j<MAX_ROW;j++)
        {
            if((adjMatrix[i][j/8]>>(7-(j%8)))&1==1)
            {
                length=2;
                clique[1]=j;
                for(int k=0;k<MAX_ROW;k++)
                {
                    xx=0;
                    while(xx!=length)
                    {
                        now = clique[xx];
                        if (adjMatrix[now][k/8] >>(7-(k%8))&1==1)
                            xx++;
                        else 
                            break;
                    }
                    if(xx==length)
                    {
                        clique[xx]=k;
                        length++;
                    }
                }
                m.lock();
                if(maxlength < length)
                {
                    maxclique = clique;
                    maxlength = length;
                    Writetotxt();
                }
                m.unlock();
            }
            if(time(NULL)-t_start >= 170)
                return;
        }
    }
}

void Writetotxt()
{
    cout<<"Max Clique : "<<maxlength<<endl;
    int i=0;
    fstream file;
    file.open(outputFile,ios::out);
    if(file.fail())
    {
        cout<<"GG";
    }
    else{
        sort(maxclique, maxclique + maxlength);
        while(*(maxclique+i)!=-1)
        {
            file<<*(maxclique+i)<<endl;
            i++;
        }
        file.close();
    }
}