#include "ProcessScheduling.h"

int main() {
	int numTestcase = 0;
	//testcase의 갯수 입력
	while (numTestcase < 1 || numTestcase>10000) { //범위 검사
		cout << "number of testcase (1~10000) : ";
		cin >> numTestcase;
	}
	//각 testcase의 job들을 저장하는 vector
	vector<vector<job>> process(numTestcase, vector<job>());
	//input
	for (int i = 0; i < numTestcase; i++) {
		int numJob = 0;
		// job의 갯수 입력
		while (numJob < 1 || numJob>256) { //범위 검사
			cout << endl;
			cout << "number of jobs at testcase#" << i + 1 << " (1~256) : ";
			cin >> numJob;
		}
		//job의 갯수만큼 resizing
		process[i].resize(numJob);

		//각 job의 arrival time, amount 입력
		for (int j = 0; j < numJob; j++) {
			do {
				cout << "arrival time, job amout of job #" << j + 1 << " : ";
				cin >> process[i][j].arrTime >> process[i][j].amount;
			} while (process[i][j].arrTime < 0 || process[i][j].amount < 0); //arrivaltime, amount 범위 검사
		}
	}
	cout << endl;
	cout << "----------------------------------------" << endl;
	cout << "           scheduling result            " << endl;
	cout << "----------------------------------------" << endl;
	//output
	for (int i = 0; i < numTestcase; i++) {

		cout << "case#" << i + 1 << " (total turnaround time, total reponse time)" << endl;
		cout << left;
		cout << fcfsTurnaround(i, process) << " " << setw(8) << fcfsResponse(i, process) << "// First Come First Served" << endl;
		cout << sjfTurnaround(i, process) << " " << setw(8) << sjfResponse(i, process) << "// Shortest Job First" << endl;
		cout << rrTurnaround(i, process) << " " << setw(8) << rrResponse(i, process) << "// Round Robin" << endl;
		cout << endl;
	}
	return 0;
}