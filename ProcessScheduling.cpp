#include "ProcessScheduling.h"

//FCFS��� total turnaround
int fcfsTurnaround(int testcase, vector<vector<job>> process) {
	int numJob = process[testcase].capacity();
	int totCompletion = 0;
	int totArrival = 0;

	for (int i = 0; i < numJob; i++) {
		//Total completion time = n*Tar1 + n*Tam1 + (n-1)Tam2 + . . . + 1*TamN
		totCompletion += process[testcase][0].arrTime + process[testcase][i].amount * (numJob - i);
		totArrival += process[testcase][i].arrTime;
	}
	// 	total turnaround = totCompletion - totArrival;
	return totCompletion - totArrival;
}

//FCFS����� total response time 
int fcfsResponse(int testcase, vector<vector<job>>  process) {

	int numJob = process[testcase].capacity();
	int totFirstrun = 0;
	int totArrival = 0;

	for (int i = 0; i < numJob; i++) {
		if (i == 0) {
			//FCFS��Ŀ��� ù��°�� ������ job
			totFirstrun = process[testcase][i].arrTime;
			totArrival += process[testcase][i].arrTime;
		}
		else {
			// Total firstrun time = n*Tar1 + (n-1)*Tam1 + (n-2)Tam2 + . . . + 1*Tam(N-1)
			totFirstrun += process[testcase][0].arrTime + process[testcase][i - 1].amount * (numJob - i);
			totArrival += process[testcase][i].arrTime;
		}
	}
	//total response time = totFirstrun - totArrival;
	return totFirstrun - totArrival;
}

// ����Ʈ�� �̿��� amount ���� ���� �Լ�
void amountSort(int testcase, vector<vector<job>>& process, int startIndex, int endIndex) {
	if (startIndex >= endIndex) { //���� 1���� ���
		return; // ���Ż��
	}
	int pivot = startIndex;
	int	left = pivot + 1;// ���� ���
	int right = endIndex; //������ ���
	job temp; // swap�� ���� �ӽ�����

	while (left <= right) {
		while (left <= endIndex && process[testcase][left].amount <= process[testcase][pivot].amount) {
			left++;
		}
		while (right > startIndex&& process[testcase][right].amount >= process[testcase][pivot].amount) {
			right--;
		}
		//swap
		if (left > right) {
			temp = process[testcase][right];
			process[testcase][right] = process[testcase][pivot];
			process[testcase][pivot] = temp;
		}
		else {
			temp = process[testcase][left];
			process[testcase][left] = process[testcase][right];
			process[testcase][right] = temp;
		}
		amountSort(testcase, process, startIndex, right - 1);	// �պκ� ����
		amountSort(testcase, process, right + 1, endIndex);		// �޺κ� ����
	}
}

//SJF����� total turnaround time
int sjfTurnaround(int testcase, vector<vector<job>>  process) {
	int numJob = process[testcase].capacity();
	int indexPointer = 0;
	int currentTime = process[testcase][0].arrTime;

	//sjf �����ٸ�
	for (int i = 0; i < numJob; i++) {
		indexPointer = i;
		//�ý��ۿ� �������ִ�(=����ð����� ���ų� ���� arrival time�� ������) job���� ã�´� 
		while (process[testcase][indexPointer].arrTime <= currentTime) {
			indexPointer++;
			if (indexPointer == numJob) { // �������� �˻����� ���μ������� ��� ���ÿ� �����Ѱ��
				break;
			}
		}

		amountSort(testcase, process, i, indexPointer - 1);
		//currenttime����
		currentTime += process[testcase][i].amount;
		if (indexPointer == numJob) {
			break;
		}
	}
	return fcfsTurnaround(testcase, process);
}

//SJF����� total response time
int sjfResponse(int testcase, vector<vector<job>>  process) {
	int numJob = process[testcase].capacity();
	int indexPointer = 0;
	int currentTime = process[testcase][0].arrTime;

	//sjf �����ٸ�
	for (int i = 0; i < numJob; i++) {
		indexPointer = i;
		//�ý��ۿ� �������ִ�(=����ð����� ���ų� ���� arrival time�� ������) job���� ã�´� 
		while (process[testcase][indexPointer].arrTime <= currentTime) {
			indexPointer++;
			if (indexPointer == numJob) { // �������� �˻����� ���μ������� ��� ���ÿ� �����Ѱ��
				break;
			}
		}
		amountSort(testcase, process, i, indexPointer - 1);
		//currenttime����
		currentTime += process[testcase][i].amount;
		if (indexPointer == numJob) {
			break;
		}
	}
	return fcfsResponse(testcase, process);
}

//RoundRobin total turnaround time
int rrTurnaround(int testcase, vector<vector<job>> process) {
	int numJob = process[testcase].capacity();
	int arrJobIndex = 0;
	const int TIMESLICE = 4;
	int totCompletion = 0;
	int totArrival = 0;
	int currentTime = process[testcase][0].arrTime;

	queue<job> queJob; //request queue
	queJob.push(process[testcase][arrJobIndex]); // �� ù��° ���μ����� request queue�� push

	// Round Robin
	while (queJob.size() > 0) {
		if ((arrJobIndex + 1) < numJob) { // arrive time�� ���� ���� job�� �������� x

			// queue front�� cpu burst���� request queue�� ����(arrive)�� job
			if (queJob.front().amount >= TIMESLICE) { // timeslice��ŭ�� cpu ���
				while (process[testcase][arrJobIndex + 1].arrTime >= currentTime
					&& process[testcase][arrJobIndex + 1].arrTime <= (currentTime + TIMESLICE)) {

					queJob.push(process[testcase][arrJobIndex + 1]);

					arrJobIndex++;
					if ((arrJobIndex + 1) == numJob) { // arrive time�� ���� ���� job ���� ��� ����
						break;
					}
				}
			}
			else { // queJob.front().amount < TIMESLICE : timeslice���� ���� �ð� cpu ���
				while (process[testcase][arrJobIndex + 1].arrTime >= currentTime
					&& process[testcase][arrJobIndex + 1].arrTime <= (currentTime + queJob.front().amount)) {

					queJob.push(process[testcase][arrJobIndex + 1]);

					arrJobIndex++;
					if ((arrJobIndex + 1) == numJob) { // arrive time�� ���� ���� job ���� ��� ����
						break;
					}
				}
			}
		}

		// queue front�� cpu burst
		if (queJob.front().amount >= TIMESLICE) {
			currentTime += TIMESLICE;
		}
		else { // queJob.front().amount  TIMESLICE
			currentTime += queJob.front().amount;
		}
		queJob.front().amount -= TIMESLICE;

		//cpu burst ����
		if (queJob.front().amount > 0) { //�ٽ� request queue�� push
			queJob.push(queJob.front());
			queJob.pop();
		}
		else { // queJob.front().amount <=0 
			totCompletion += currentTime;
			queJob.pop();
		}

		//// job�� �Ϸ�� ���μ����� ���� �������� ���� job�� ���ٸ� cpu�� ������ �ʰ� �ð��� �帧
		if (queJob.size() == 0 && (arrJobIndex + 1) < numJob) {
			currentTime = process[testcase][arrJobIndex + 1].arrTime;
			queJob.push(process[testcase][arrJobIndex + 1]);
			arrJobIndex++;
		}
	}

	for (int i = 0; i < numJob; i++) {
		//total completion = n*arrive0 +  n*amount0 + (n-1)*amount1 + ... + 1*amountN-1
		totArrival += process[testcase][i].arrTime;
	}

	return totCompletion - totArrival;
}

//Round Robin total response time
int rrResponse(int testcase, vector<vector<job>>  process) {
	int numJob = process[testcase].capacity();
	int arrJobIndex = 0;
	const int TIMESLICE = 4;
	int totFirstrun = 0;
	int totArrival = 0;
	int currentTime = process[testcase][0].arrTime;

	queue<job> queJob; //request queue
	queJob.push(process[testcase][arrJobIndex]); // �� ù��° ���μ����� request queue�� push
	queJob.back().Scheduled += 1;

	// Round Robin
	while (queJob.size() > 0) {
		if ((arrJobIndex + 1) < numJob) { // arrive time�� ���� ���� job�� �������� x

			// queue front�� cpu burst���� request queue�� ����(arrive)�� job
			if (queJob.front().amount >= TIMESLICE) {
				while (process[testcase][arrJobIndex + 1].arrTime >= currentTime
					&& process[testcase][arrJobIndex + 1].arrTime <= (currentTime + TIMESLICE)) {

					queJob.push(process[testcase][arrJobIndex + 1]);
					queJob.back().Scheduled += 1;

					arrJobIndex++;
					if ((arrJobIndex + 1) == numJob) { // arrive time�� ���� ���� job ���� ��� ����
						break;
					}
				}
			}
			else { // queJob.front().amount < TIMESLICE
				while (process[testcase][arrJobIndex + 1].arrTime >= currentTime
					&& process[testcase][arrJobIndex + 1].arrTime <= (currentTime + queJob.front().amount)) {

					queJob.push(process[testcase][arrJobIndex + 1]);
					queJob.back().Scheduled += 1;

					arrJobIndex++;
					if ((arrJobIndex + 1) == numJob) { // arrive time�� ���� ���� job ���� ��� ����
						break;
					}
				}
			}
		}

		// queue front�� cpu burst
		if (queJob.front().amount >= TIMESLICE) {
			if (queJob.front().Scheduled == 1) {
				totFirstrun += currentTime;
			}
			currentTime += TIMESLICE;
		}
		else { // queJob.front().amount  TIMESLICE
			if (queJob.front().Scheduled == 1) {
				totFirstrun += currentTime;
			}
			currentTime += queJob.front().amount;
		}
		queJob.front().amount -= TIMESLICE;

		//cpu burst ����
		if (queJob.front().amount > 0) { //�ٽ� request queue�� push
			queJob.push(queJob.front());
			queJob.back().Scheduled += 1;
			queJob.pop();
		}
		else { // queJob.front().amount <=0 
			//totResponse += currentTime;
			queJob.pop();
		}

		//// job�� �Ϸ�� ���μ����� ���� �������� ���� job�� ���ٸ� cpu�� ������ �ʰ� �ð��� �帧
		if (queJob.size() == 0 && (arrJobIndex + 1) < numJob) {
			currentTime = process[testcase][arrJobIndex + 1].arrTime;
			queJob.push(process[testcase][arrJobIndex + 1]);
			queJob.back().Scheduled += 1;

			arrJobIndex++;
		}
	}

	for (int i = 0; i < numJob; i++) {
		//total completion = n*arrive0 +  n*amount0 + (n-1)*amount1 + ... + 1*amountN-1
		totArrival += process[testcase][i].arrTime;
	}

	return totFirstrun - totArrival;
}