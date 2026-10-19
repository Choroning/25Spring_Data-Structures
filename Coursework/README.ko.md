# 수업 결과물

[레포지토리 안내](../README.ko.md) | [English](README.md) | [한국어](README.ko.md)

> **최종 수정일:** 2026-10-19

| 항목 | 내용 | 문서 |
|:-----|:-----|:-----|
| [HW01_Circular-Linked-List-with-Head-Node](HW01_Circular-Linked-List-with-Head-Node/) | 1차 프로그래밍 과제. 헤드 노드가 있는 원형 연결 리스트의 `InsertFront`와 `InsertRear` 구현, 실행 화면, 헤드 노드의 장점과 위치에 관한 서술형 답을 다룬다. 3강과 이어진다 | [과제 해설](HW01_Circular-Linked-List-with-Head-Node/Assignment-Explanation.ko.md), [코드 총정리](HW01_Circular-Linked-List-with-Head-Node/Code-Walkthrough.ko.md), [과제 안내문](HW01_Circular-Linked-List-with-Head-Node/Original/Assignment.ko.md) |
| [HW02_Linked-Queue-Push-and-Pop](HW02_Linked-Queue-Push-and-Pop/) | 2차 프로그래밍 과제. 링크의 방향이 다른 두 표현(type 1, type 2)으로 연결 큐의 `push`와 `pop`을 구현하고, 원소 200,000개를 모두 pop하는 시간을 비교한다. 6강과 이어진다 | [과제 해설](HW02_Linked-Queue-Push-and-Pop/Assignment-Explanation.ko.md), [코드 총정리](HW02_Linked-Queue-Push-and-Pop/Code-Walkthrough.ko.md), [과제 안내문](HW02_Linked-Queue-Push-and-Pop/Original/Assignment.ko.md) |
| [Lab01_Performance-Analysis](Lab01_Performance-Analysis/) | `std::chrono`로 함수 실행 시간을 반복 측정해 평균을 내는 타이머, O(1), O(log n), O(n), O(n log n), O(n²) 알고리즘(배열 접근, 이진 탐색, 최댓값 탐색, 병합 정렬, 버블 정렬)의 입력 크기별 실행 시간 비교, 단계 수 계산과 공간 복잡도 예제, `clock()`을 이용한 CPU 시간 측정을 다루는 실습 코드. 1강과 이어진다 | [Lab_PerformanceMeasurement.cpp](Lab01_Performance-Analysis/Lab_PerformanceMeasurement.cpp) |
| [Lab02_Time-Complexity](Lab02_Time-Complexity/) | O(1)(인덱스 접근, 짝수 판별), O(log n)(이진 탐색, 정수 로그), O(n)(선형 탐색, 합계, 최댓값), O(n log n)(병합 정렬), O(n²)(선택 정렬, 중복 검사) 알고리즘의 예제, 병합 정렬과 선택 정렬의 실행 시간 비교, 성장률별 연산 횟수 비교를 다루는 실습 코드. 2강과 이어진다 | [Lab_ComplexityExamples.cpp](Lab02_Time-Complexity/Lab_ComplexityExamples.cpp) |
| [Lab03_Arrays-and-Linked-Lists](Lab03_Arrays-and-Linked-Lists/) | 가득 차면 용량을 두 배로 늘리는 템플릿 동적 배열 리스트(반복자, 범위 검사 접근, 탐색, 삽입, 삭제)와, 반복자를 갖춘 템플릿 단일 연결 리스트(앞, 뒤, 지정 위치 삽입과 삭제, 탐색, 제자리 역순화) 및 센티넬 노드를 쓰는 이중 연결 리스트를 다루는 실습 코드. 3강과 이어진다 | [Lab_ArrayList.cpp](Lab03_Arrays-and-Linked-Lists/Lab_ArrayList.cpp), [Lab_LinkedList.cpp](Lab03_Arrays-and-Linked-Lists/Lab_LinkedList.cpp) |
| [Lab04_Matrices](Lab04_Matrices/) | 삼중쌍 배열로 저장한 희소 행렬(값 설정과 조회, O(terms + cols) 빠른 전치, 덧셈)과 직교 리스트로 표현한 희소 행렬을 다루는 실습 코드. 4강과 이어진다 | [Lab_SparseMatrix.cpp](Lab04_Matrices/Lab_SparseMatrix.cpp) |
| [Lab05_Stacks](Lab05_Stacks/) | 동적 크기 조정 배열 스택과 그 응용(괄호 매칭, 중위에서 후위로의 변환, 후위 수식 평가), 단일 연결 리스트 스택과 그 응용(10진수의 2진수 변환, 문자열 뒤집기, 하노이의 탑)을 다루는 실습 코드. 5강과 이어진다 | [Lab_ArrayStack.cpp](Lab05_Stacks/Lab_ArrayStack.cpp), [Lab_LinkedStack.cpp](Lab05_Stacks/Lab_LinkedStack.cpp) |
| [Lab06_Queues](Lab06_Queues/) | 한 칸을 비워 가득 찬 상태와 빈 상태를 구분하는 템플릿 원형 배열 큐와 Hot Potato 시뮬레이션(요세푸스 문제의 변형)을 다루는 실습 코드. 6강과 이어진다 | [Lab_ArrayQueue.cpp](Lab06_Queues/Lab_ArrayQueue.cpp) |
| [Lab07_Skip-Lists-and-Hashing](Lab07_Skip-Lists-and-Hashing/) | 무작위 레벨을 쓰는 스킵 리스트의 탐색, 삽입, 삭제와 레벨별 출력, 분리 체이닝 해시 테이블과 지연 삭제를 쓰는 선형 조사 해시 테이블을 다루는 실습 코드. 7강과 이어진다 | [Lab_SkipList.cpp](Lab07_Skip-Lists-and-Hashing/Lab_SkipList.cpp), [Lab_HashTable.cpp](Lab07_Skip-Lists-and-Hashing/Lab_HashTable.cpp) |
| [Lab08_Binary-Trees](Lab08_Binary-Trees/) | 연결 표현 이진 트리의 전위, 중위, 후위, 레벨 순서 순회와 높이, 노드 수 계산, 후위 수식으로 수식 트리를 만들어 계산하는 실습 코드. 8강과 이어진다 | [Lab_BinaryTree.cpp](Lab08_Binary-Trees/Lab_BinaryTree.cpp) |
| [Lab09_Priority-Queues-and-Heaps](Lab09_Priority-Queues-and-Heaps/) | 1부터 시작하는 인덱스를 쓰는 배열 최대 힙(삽입, 최댓값 삭제, 상향식 초기화, 힙 성질 검사)과 힙 정렬, 합병 연산으로 삽입과 최솟값 삭제를 구현한 최소 좌편향 트리를 다루는 실습 코드. 9강과 이어진다 | [Lab_MaxHeap.cpp](Lab09_Priority-Queues-and-Heaps/Lab_MaxHeap.cpp), [Lab_LeftistTree.cpp](Lab09_Priority-Queues-and-Heaps/Lab_LeftistTree.cpp) |
| [Lab10_Binary-Search-Trees](Lab10_Binary-Search-Trees/) | 연결 표현 이진 탐색 트리의 탐색, 삽입, 세 가지 경우(리프, 차수 1, 차수 2)의 삭제, 중위, 전위, 레벨 순서 순회, 높이 계산, 정렬된 순서로 삽입한 최악의 경우와 중복 키 삽입을 다루는 실습 코드. 10강과 이어진다 | [Lab_BinarySearchTree.cpp](Lab10_Binary-Search-Trees/Lab_BinarySearchTree.cpp) |
| [Project_Database-Index-Engine](Project_Database-Index-Engine/) | 관계형 데이터베이스의 인덱스에 쓰이는 B+ 트리를 C++ 템플릿으로 구현한 텀 프로젝트. 점 질의, 리프 연결 리스트를 이용한 범위 질의, 노드 분할을 동반한 삽입, 언더플로 처리를 동반한 삭제, 차수를 정하는 템플릿 매개변수를 다루며, CMU 15-445와 Stanford CS245를 참고했다. 8강과 10강의 트리 내용과 이어진다 | [README](Project_Database-Index-Engine/README.md) |
| [Project_Huffman-Coding](Project_Huffman-Coding/) | 문자 빈도에 따라 가변 길이 이진 부호를 붙이는 허프만 부호화 압축 도구를 C++로 구현한 텀 프로젝트. 빈도 분석, 최소 힙 우선순위 큐를 이용한 허프만 트리 구성, 부호화와 복호화, 비트 단위 입출력, 압축 통계를 다루며, Stanford CS106B와 Princeton COS226을 참고했다. 8강의 이진 트리와 9강의 우선순위 큐와 이어진다 | [README](Project_Huffman-Coding/README.md) |
