OS : process scheduling

implementation of process scheduling

1. First Come First Served
2. Shortest Job First
3. Round Robin

<설명>

OSTEP의 “7. Scheduling: Introduction”에 나온
스케줄링 기법 중 3가지, First Come First Served(FCFS), Shorted Job First(SJF), Round Robin(RR) 기법을 구현. 
여기서 RR기법의 time slice는 4로 정의.

프로그램의 입력으로는 먼저 testcase의 개수가 주어집니다. 그 뒤, job의 개수를 입력 받고
그 수만큼의 job arrival time, job amount가 주어지며, 사용자는 입력을 받고
스케줄링 기법 3가지를 각각 total turnaround time과 total response time을 차례대로 출력합니다.
(단, 입력의 job arrival time은 오름차순으로 주어집니다.) 이를 testcase만큼 반복하며 입력과 출력을 합니다.

같은 arrival time을 갖는 job이 여러 개 있다면, 입력이 먼저 주어진 job부터 수행합니다.
예를 들어, FCFS의 경우 job의 입력으로 0 5, 0 4, 0 3이 왔다고 생각해보면
3개의 job이 모두 시간이 0일 때 같이 도착했지만, 0 5의 job을 먼저 처리하는 것으로 구현합니다.

1≤ testcase ≤10000, 1≤ job ≤256, 0≤ job arrival time, job amount
(모든 입/출력 값은 signed int의 최대값 2147483647을 넘지 않습니다.)
※ turnaround time과 response time의 정의 및 계산은 7장의 기준을 따릅니다. ※

<예제 및 출력 형식>

input

2
3
0 10
0 6
0 4
4
0 100
0 80
10 50
20 30

output

case1
46 26 // FCFS
34 14 // SJF
50 12 // RR

case2
740 480 // FCFS
580 320 // SJF
804 18  // RR
