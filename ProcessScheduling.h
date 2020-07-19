#pragma once
#include <iostream>	// ǥ�������
#include <iomanip>	// ���ȭ�� ����
#include <vector>	// testcase�� job���� �����ϴ� vector
#include <queue>	// Round Robin�� request queue
using namespace std;

struct job {
	int arrTime; //�����ð�
	int amount; // �۾��ð�
	int Scheduled = 0; // 0 =  �����ٸ� ���� �ѹ��� �ȵ�, 0 !=  �����층 ��� �ѹ� ��
};

//FCFS��� total turnaround, total response time ��� �Լ�
int fcfsTurnaround(int testcase, vector<vector<job>> process);
int fcfsResponse(int testcase, vector<vector<job>> process);

// ����Ʈ�� �̿��� amount ���� ���� �Լ�
void amountSort(int testcase, vector<vector<job>>& process, int startIndex, int endIndex);

//SJF��� total turnaround, total response time ��� �Լ�
int sjfTurnaround(int testcase, vector<vector<job>>  process);
int sjfResponse(int testcase, vector<vector<job>>  process);

//RR��� total turnaround, total response time ��� �Լ�
int rrTurnaround(int testcase, vector<vector<job>>  process);
int rrResponse(int testcase, vector<vector<job>>  process);