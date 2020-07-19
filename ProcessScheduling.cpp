#include "ProcessScheduling.h"

//FCFS방식 total turnaround
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

//FCFS방식의 total response time 
int fcfsResponse(int testcase, vector<vector<job>>  process) {

	int numJob = process[testcase].capacity();
	int totFirstrun = 0;
	int totArrival = 0;

	for (int i = 0; i < numJob; i++) {
		if (i == 0) {
			//FCFS방식에서 첫번째로 도착한 job
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

// 퀵소트를 이용한 amount 기준 정렬 함수
void amountSort(int testcase, vector<vector<job>>& process, int startIndex, int endIndex) {
	if (startIndex >= endIndex) { //원소 1개인 경우
		return; // 재귀탈출
	}
	int pivot = startIndex;
	int	left = pivot + 1;// 왼쪽 출발
	int right = endIndex; //오른쪽 출발
	job temp; // swap을 위해 임시저장

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
		amountSort(testcase, process, startIndex, right - 1);	// 앞부분 정렬
		amountSort(testcase, process, right + 1, endIndex);		// 뒷부분 정렬
	}
}

//SJF방식의 total turnaround time
int sjfTurnaround(int testcase, vector<vector<job>>  process) {
	int numJob = process[testcase].capacity();
	int indexPointer = 0;
	int currentTime = process[testcase][0].arrTime;

	//sjf 스케줄링
	for (int i = 0; i < numJob; i++) {
		indexPointer = i;
		//시스템에 도착해있는(=현재시간보다 같거나 작은 arrival time을 가지는) job들을 찾는다 
		while (process[testcase][indexPointer].arrTime <= currentTime) {
			indexPointer++;
			if (indexPointer == numJob) { // 마지막에 검색에서 프로세스들이 모두 동시에 도착한경우
				break;
			}
		}

		amountSort(testcase, process, i, indexPointer - 1);
		//currenttime갱신
		currentTime += process[testcase][i].amount;
		if (indexPointer == numJob) {
			break;
		}
	}
	return fcfsTurnaround(testcase, process);
}

//SJF방식의 total response time
int sjfResponse(int testcase, vector<vector<job>>  process) {
	int numJob = process[testcase].capacity();
	int indexPointer = 0;
	int currentTime = process[testcase][0].arrTime;

	//sjf 스케줄링
	for (int i = 0; i < numJob; i++) {
		indexPointer = i;
		//시스템에 도착해있는(=현재시간보다 같거나 작은 arrival time을 가지는) job들을 찾는다 
		while (process[testcase][indexPointer].arrTime <= currentTime) {
			indexPointer++;
			if (indexPointer == numJob) { // 마지막에 검색에서 프로세스들이 모두 동시에 도착한경우
				break;
			}
		}
		amountSort(testcase, process, i, indexPointer - 1);
		//currenttime갱신
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
	queJob.push(process[testcase][arrJobIndex]); // 맨 첫번째 프로세스를 request queue에 push

	// Round Robin
	while (queJob.size() > 0) {
		if ((arrJobIndex + 1) < numJob) { // arrive time이 가장 늦은 job이 아직도착 x

			// queue front의 cpu burst동안 request queue에 도착(arrive)할 job
			if (queJob.front().amount >= TIMESLICE) { // timeslice만큼만 cpu 사용
				while (process[testcase][arrJobIndex + 1].arrTime >= currentTime
					&& process[testcase][arrJobIndex + 1].arrTime <= (currentTime + TIMESLICE)) {

					queJob.push(process[testcase][arrJobIndex + 1]);

					arrJobIndex++;
					if ((arrJobIndex + 1) == numJob) { // arrive time이 가장 늦은 job 까지 모두 도착
						break;
					}
				}
			}
			else { // queJob.front().amount < TIMESLICE : timeslice보다 적은 시간 cpu 사용
				while (process[testcase][arrJobIndex + 1].arrTime >= currentTime
					&& process[testcase][arrJobIndex + 1].arrTime <= (currentTime + queJob.front().amount)) {

					queJob.push(process[testcase][arrJobIndex + 1]);

					arrJobIndex++;
					if ((arrJobIndex + 1) == numJob) { // arrive time이 가장 늦은 job 까지 모두 도착
						break;
					}
				}
			}
		}

		// queue front의 cpu burst
		if (queJob.front().amount >= TIMESLICE) {
			currentTime += TIMESLICE;
		}
		else { // queJob.front().amount  TIMESLICE
			currentTime += queJob.front().amount;
		}
		queJob.front().amount -= TIMESLICE;

		//cpu burst 이후
		if (queJob.front().amount > 0) { //다시 request queue로 push
			queJob.push(queJob.front());
			queJob.pop();
		}
		else { // queJob.front().amount <=0 
			totCompletion += currentTime;
			queJob.pop();
		}

		//// job이 완료된 프로세스와 아직 도착하지 않은 job이 없다면 cpu는 사용되지 않고 시간만 흐름
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
	queJob.push(process[testcase][arrJobIndex]); // 맨 첫번째 프로세스를 request queue에 push
	queJob.back().Scheduled += 1;

	// Round Robin
	while (queJob.size() > 0) {
		if ((arrJobIndex + 1) < numJob) { // arrive time이 가장 늦은 job이 아직도착 x

			// queue front의 cpu burst동안 request queue에 도착(arrive)할 job
			if (queJob.front().amount >= TIMESLICE) {
				while (process[testcase][arrJobIndex + 1].arrTime >= currentTime
					&& process[testcase][arrJobIndex + 1].arrTime <= (currentTime + TIMESLICE)) {

					queJob.push(process[testcase][arrJobIndex + 1]);
					queJob.back().Scheduled += 1;

					arrJobIndex++;
					if ((arrJobIndex + 1) == numJob) { // arrive time이 가장 늦은 job 까지 모두 도착
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
					if ((arrJobIndex + 1) == numJob) { // arrive time이 가장 늦은 job 까지 모두 도착
						break;
					}
				}
			}
		}

		// queue front의 cpu burst
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

		//cpu burst 이후
		if (queJob.front().amount > 0) { //다시 request queue로 push
			queJob.push(queJob.front());
			queJob.back().Scheduled += 1;
			queJob.pop();
		}
		else { // queJob.front().amount <=0 
			//totResponse += currentTime;
			queJob.pop();
		}

		//// job이 완료된 프로세스와 아직 도착하지 않은 job이 없다면 cpu는 사용되지 않고 시간만 흐름
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