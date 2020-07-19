#pragma once
#include <iostream>	// 표준입출력
#include <iomanip>	// 출력화면 정렬
#include <vector>	// testcase별 job들의 저장하는 vector
#include <queue>	// Round Robin의 request queue
using namespace std;

struct job {
	int arrTime; //도착시간
	int amount; // 작업시간
	int Scheduled = 0; // 0 =  스케줄링 아직 한번도 안됨, 0 !=  스케쥴링 적어도 한번 됨
};

//FCFS방식 total turnaround, total response time 출력 함수
int fcfsTurnaround(int testcase, vector<vector<job>> process);
int fcfsResponse(int testcase, vector<vector<job>> process);

// 퀵소트를 이용한 amount 기준 정렬 함수
void amountSort(int testcase, vector<vector<job>>& process, int startIndex, int endIndex);

//SJF방식 total turnaround, total response time 출력 함수
int sjfTurnaround(int testcase, vector<vector<job>>  process);
int sjfResponse(int testcase, vector<vector<job>>  process);

//RR방식 total turnaround, total response time 출력 함수
int rrTurnaround(int testcase, vector<vector<job>>  process);
int rrResponse(int testcase, vector<vector<job>>  process);