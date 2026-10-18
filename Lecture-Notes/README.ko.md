# 강의 노트

[레포지토리 안내](../README.ko.md) | [English](README.md) | [한국어](README.ko.md)

> **최종 수정일:** 2026-10-18

| 단원 | 주제 | 문서 |
|:-----|:-----|:-----|
| [1강 성능 분석](Lec01_Performance-Analysis/) | 성능 분석의 개요, 공간 복잡도(고정 공간과 가변 공간, 재귀적 공간), 연산 횟수와 단계 계수법, 최선, 최악, 평균 경우, 경과 시간과 CPU 시간 측정, `clock()`을 이용한 프로파일링과 경험적 복잡도 결정 | [강의 노트](Lec01_Performance-Analysis/Concepts_Lecture.ko.md), [연습 문제](Lec01_Performance-Analysis/Exercises.ko.md), [풀이](Lec01_Performance-Analysis/Solutions.ko.md) |
| [2강 시간 복잡도](Lec02_Time-Complexity/) | 점근적 표기법, Big-O, Big-Omega, Theta 표기법, Little-o와 Little-omega, 일반적인 성장률과 코드에서 복잡도 식별, 점화식, 분할 상환 분석 | [강의 노트](Lec02_Time-Complexity/Concepts_Lecture.ko.md), [연습 문제](Lec02_Time-Complexity/Exercises.ko.md), [풀이](Lec02_Time-Complexity/Solutions.ko.md) |
| [3강 배열과 연결 리스트](Lec03_Arrays-and-Linked-Lists/) | 선형 리스트 ADT, 수식 기반 배열 표현과 동적 배열, 연결 표현, 단일 연결 리스트, 이중 연결 리스트, 원형 리스트, 배열과 연결 리스트의 비교 | [강의 노트](Lec03_Arrays-and-Linked-Lists/Concepts_Lecture.ko.md), [연습 문제](Lec03_Arrays-and-Linked-Lists/Exercises.ko.md), [풀이](Lec03_Arrays-and-Linked-Lists/Solutions.ko.md) |
| [4강 행렬](Lec04_Matrices/) | 다차원 배열과 메모리 매핑, 행 우선 순서와 열 우선 순서, 특수 행렬(대각, 삼중 대각, 삼각, 대칭 행렬), 희소 행렬의 삼중쌍 배열 표현과 전치, 직교 리스트, 희소 행렬의 덧셈과 곱셈 | [강의 노트](Lec04_Matrices/Concepts_Lecture.ko.md), [연습 문제](Lec04_Matrices/Exercises.ko.md), [풀이](Lec04_Matrices/Solutions.ko.md) |
| [5강 스택](Lec05_Stacks/) | 스택 ADT, 배열 기반 스택과 동적 크기 조정, 연결 스택, 괄호 매칭, 함수 호출 스택, 실행 취소 연산, 하노이의 탑, 중위, 전위, 후위 표기법, 중위에서 후위로의 변환과 후위 수식 평가 | [강의 노트](Lec05_Stacks/Concepts_Lecture.ko.md), [연습 문제](Lec05_Stacks/Exercises.ko.md), [풀이](Lec05_Stacks/Solutions.ko.md) |
| [6강 큐](Lec06_Queues/) | 큐 ADT, 배열 기반 큐, 원형 큐와 가득 찬 상태와 빈 상태의 구분, 연결 큐, 양방향 큐(deque), CPU 스케줄링, 너비 우선 탐색, 버퍼 관리 | [강의 노트](Lec06_Queues/Concepts_Lecture.ko.md), [연습 문제](Lec06_Queues/Exercises.ko.md), [풀이](Lec06_Queues/Solutions.ko.md) |
| [7강 스킵 리스트와 해싱](Lec07_Skip-Lists-and-Hashing/) | 딕셔너리 ADT와 정렬된 선형 리스트, 스킵 리스트의 구조, 탐색, 삽입, 삭제와 시간 복잡도, 이상적 해싱, 해시 함수, 개방 주소법과 체이닝에 의한 충돌 해결, 성능 비교 | [강의 노트](Lec07_Skip-Lists-and-Hashing/Concepts_Lecture.ko.md), [연습 문제](Lec07_Skip-Lists-and-Hashing/Exercises.ko.md), [풀이](Lec07_Skip-Lists-and-Hashing/Solutions.ko.md) |
| [8강 이진 트리](Lec08_Binary-Trees/) | 트리 용어와 이진 트리의 정의, 이진 트리의 성질, 포화 이진 트리와 완전 이진 트리, 배열 표현과 연결 표현, 전위, 중위, 후위, 레벨 순서 순회, 수식 트리 | [강의 노트](Lec08_Binary-Trees/Concepts_Lecture.ko.md), [연습 문제](Lec08_Binary-Trees/Exercises.ko.md), [풀이](Lec08_Binary-Trees/Solutions.ko.md) |
| [9강 우선순위 큐와 힙](Lec09_Priority-Queues-and-Heaps/) | 최소 우선순위 큐와 최대 우선순위 큐, 최대 트리와 최소 트리, 힙의 배열 표현, 삽입(bubble up)과 삭제(trickle down), 힙 초기화, 좌편향 트리의 s-값과 합병 연산 | [강의 노트](Lec09_Priority-Queues-and-Heaps/Concepts_Lecture.ko.md), [연습 문제](Lec09_Priority-Queues-and-Heaps/Exercises.ko.md), [풀이](Lec09_Priority-Queues-and-Heaps/Solutions.ko.md) |
| [10강 이진 탐색 트리](Lec10_Binary-Search-Trees/) | 이진 탐색 트리의 정의와 표현, 탐색, 삽입, 삭제, 높이 분석(최선과 최악의 경우), 인덱스 이진 탐색 트리와 순위 기반 연산, 중복을 허용하는 이진 탐색 트리 | [강의 노트](Lec10_Binary-Search-Trees/Concepts_Lecture.ko.md), [연습 문제](Lec10_Binary-Search-Trees/Exercises.ko.md), [풀이](Lec10_Binary-Search-Trees/Solutions.ko.md) |
