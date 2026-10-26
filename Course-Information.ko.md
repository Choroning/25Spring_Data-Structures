# 강의 정보

[레포지토리 안내](README.ko.md) | [English](Course-Information.md) | [한국어](Course-Information.ko.md)

> **최종 수정일:** 2026-10-26

## 목차

- [1. 교수자, 조교 및 연구실](#1-교수자-조교-및-연구실)
- [2. 수업 일정 및 형식](#2-수업-일정-및-형식)
- [3. 평가](#3-평가)
- [4. 수업 운영 규정](#4-수업-운영-규정)
- [5. 주차별 계획 및 진도](#5-주차별-계획-및-진도)
- [6. 참고 자료](#6-참고-자료)

---

<br>

## 1. 교수자, 조교 및 연구실

- **교수자:** 조민호 교수, 컴퓨터소프트웨어학과
- **연구실:** IoT & AI Lab
- **면담 시간:** 월요일 16:00 ~ 18:00, 수요일 15:00 ~ 16:00, 목요일 14:00 ~ 15:00
- **조교:** 임경민(Kyungmin Lim). 2차 프로그래밍 과제의 설명 자료를 만들었다.

---

<br>

## 2. 수업 일정 및 형식

- **학점(시간):** 3(3)
- **수강 대상:** 2학년, 3학년, 4학년
- **강의 언어:** 영어. 강의계획서의 과목명은 "Data Structures (SEMO Class, 영강. Taught in English)"이다.
- **강의 시간:** 월요일 10:00 ~ 10:50, 11:00 ~ 11:50, 수요일 10:00 ~ 10:50
- **강의실:** 7-310호(월)
- **수업 방법:** 강의, 실습, 질의응답으로 진행하며, 강의와 과제가 이 과목의 핵심 교수 방법이다.
  - 개념과 이론 수업에서는 자료구조와 알고리즘의 이론적 내용을 공부한다.
  - 과제에서는 실제 문제를 풀고, C/C++, Java, Python 같은 자신의 프로그래밍 언어로 풀이를 프로그래밍한다.
- **출석:** 매 수업 시간에 출석을 확인한다.
- **시험 감독:** 시험은 무감독으로 치르지 않는다.
- **교과목 개요:** 이 과목은 자료구조와 자료구조를 다루는 알고리즘에 초점을 맞춘다. 표, 리스트, 트리, 큐, 스택에 정보를 저장하는 자료구조를 다루며, 자료구조는 소프트웨어 프로그래밍에 매우 중요하다. 기초적인 그래프 알고리즘과 이산 변환 알고리즘도 가르치고, "long-life" 소프트웨어를 위한 좋은 프로그래밍 습관 같은 소프트웨어 공학의 기본 원리도 소개한다.
- **학습 목표:**
  1. 자료구조와 알고리즘의 시간 복잡도와 공간 복잡도를 이해한다.
  2. 자료구조와 알고리즘의 개념을 이해한다.
  3. 현재의 최신 자료구조를 접한다.
  4. 중요하고 널리 쓰이는 자료구조와 알고리즘을 배운다.
  5. 문제 해결을 위한 자료구조 설계 방법을 배운다.
- **과목 목표와 학과 목표:** 자료구조를 설계하는 방법과 자료구조를 다루는 알고리즘을 적용하는 방법을 이해하는 것이 이 과목의 핵심 역량이다. 학과의 목표 중 하나는 학생이 스스로의 힘과 창의력으로 소프트웨어를 개발할 수 있도록 준비시키는 것이며, 이 과목의 핵심 목표는 자신의 소프트웨어를 위해 공간과 시간 면에서 효율적으로 데이터를 저장하고 검색하는 자료구조를 자신 있게 설계할 수 있는 학생을 가르치고 훈련하는 것이다.
- **핵심역량:** 강의계획서는 Frontier Spirit과 Pragmatic Practice를 관련성이 매우 높은 역량으로, Creative Convergence와 Global Leadership을 관련성이 높은 역량으로 표시했다.
- **전공능력:** 이 과목은 학과의 전공능력(Ethics & Leadership, Think & Technology, Network & Application) 중 Think & Technology와 Network & Application에 해당한다.
- **선수 과목:** Python, Java, C/C++ 같은 프로그래밍 언어 능력이 필요하다.

---

<br>

## 3. 평가

| 항목 | 비율 |
|:-----|-----:|
| 퀴즈 | 60% |
| 온라인 토론(Online Q&A) | 10% |
| 오프라인 토론(Off-line Q&A) | 5% |
| 출석 | 5% |
| 프로그래밍 과제 | 20% |

- 절대평가이며, 평가 결과에 대한 피드백을 제공한다.
- 강의계획서는 장마다 수업을 마친 뒤 과제를 낸다고 밝혔다. 과제는 수업 내용을 완전히 이해하는 데 중요하다.
- 퀴즈는 장마다 LMS에서 치렀으며, 제목은 "Quiz for Chapter 1"부터 "Quiz for Chapter 10"까지이다.
- **1차 프로그래밍 과제 (Programming Homework #1):** 헤드 노드가 있는 원형 연결 리스트(Circular Linked List with Head Node)의 연산을 프로그래밍한다. 풀이와 해설은 [`HW01_Circular-Linked-List-with-Head-Node`](Coursework/HW01_Circular-Linked-List-with-Head-Node/)에 있다.
  - `InsertFront` 연산 (20점): 새 노드의 링크가 원래의 첫 노드를 가리키게 하고(10점), 새 노드를 새로운 첫 노드로 만든다(10점).
  - `InsertRear` 연산 (50점): 첫 노드를 `cur` 포인터에 저장하고(10점), while 반복문으로 마지막 노드를 찾아 `cur`에 저장하며(20점), 새 노드를 마지막 노드 뒤에 삽입하고(10점), 마지막 노드가 항상 헤드 노드를 가리키게 한다(10점).
  - 완성한 코드로 프로그램을 실행하고 결과 화면을 캡처한다(20점).
  - 헤드 노드에 관한 질문에 답한다(10점): (1) 원형 연결 리스트에서 헤드 노드를 쓰는 장점, (2) 헤드 노드를 앞에 두는 것과 뒤에 두는 것의 차이.
- **2차 프로그래밍 과제 (Programming Homework #2):** 연결 큐의 push와 pop 연산(Linked Queue Pop and Push Operation)을 프로그래밍한다. 풀이와 해설은 [`HW02_Linked-Queue-Push-and-Pop`](Coursework/HW02_Linked-Queue-Push-and-Pop/)에 있다.
  - `Queue` 클래스의 `push` 연산 (30점): type 1(20점)과 type 2(10점)의 push를 구현한다.
  - `pop` 연산 (50점): type 1(20점)과 type 2(30점)의 pop을 구현한다.
  - 완성한 코드로 프로그램을 실행하고 결과 화면을 캡처한다(20점).
  - 조교가 연결 큐의 두 가지 표현(type 1, type 2)과 각각의 push, pop 과정을 그림으로 설명한 자료(Linked Queue: pushing and popping operation)를 배포했다.

---

<br>

## 4. 수업 운영 규정

- 모든 과제와 그 밖의 정보는 학교 포털 시스템의 Blackboard 게시판(BBS)에 공지하며, 과제 제출물은 마감까지 Blackboard의 과제 메뉴에 올려야 한다.
- 참여가 중요하므로 수업에 결석하지 않기를 권한다.
- **장애 학생 지원:** 수업 참여에 어려움이 있는 장애 학생은 언제든지 교수자에게 도움을 요청할 수 있다.
- **학습 윤리:** 학생은 강의 수강, 과제물 작성과 제출, 시험 등 교육과정을 이수하는 모든 과정에서 다음의 일반 의무를 가진다.
  1. 대학의 목적과 교육 이념에 따라 정직하고 열정적인 태도로 모든 학습에 적극적으로 참여한다.
  2. 고등 교육을 받는 학생으로서의 위치를 자각하고, 도덕적 민감성을 바탕으로 창의적 학습에 정진한다.
  3. 교육 활동과 관련하여 교원 또는 동료 학생과 약속한 사항을 성실히 이행한다.
  4. 교원과 다른 학생의 인격을 존중하고 기본적인 예의를 지킨다.
- 표절, 다른 수업 과제물의 중복 사용, 시험 부정행위 등 정직하지 못한 행위나 그 밖의 부당한 방법으로 학점을 취득한 것으로 판명되면 이미 인정된 학점이라도 취소하며, 행위의 정상을 참작하여 정학, 제적, 퇴학 등의 징계를 할 수 있다.
- 학교는 학습 윤리 의식을 높이고 창의력을 북돋우기 위해 표절검사시스템(Blackboard)을 운용하며, 학생은 과제를 제출할 때 표절에 해당하는지 미리 확인해야 한다.

---

<br>

## 5. 주차별 계획 및 진도

| 주차 | 수업일 (월, 수) | 계획된 주제 | 진행한 강의자료 |
|:-----|:-----|:-----|:-----|
| 1주차 | 3/3, 3/5 | Introduction and program performance measurement | - |
| 2주차 | 3/10, 3/12 | Program Performance measurement | L1 Program Performance Analysis and Measurement<br>L2 Time Complexity Theory for Performance Measurement |
| 3주차 | 3/17, 3/19 | Time complexity theory | - |
| 4주차 | 3/24, 3/26 | Array-based linear list and linked-based linear list | L3 Array and Link |
| 5주차 | 3/31, 4/2 | Array and matrices | L4 Arrays and Matrices |
| 6주차 | 4/7, 4/9 | Stacks | L5 Stacks |
| 7주차 | 4/14, 4/16 | Queues | L6 Queues |
| 8주차 | 4/21, 4/23 | 중간고사 | 휴강 |
| 9주차 | 4/28, 4/30 | Skip lists and hashing | - |
| 10주차 | 5/5, 5/7 | Binary and other trees | 과제 대체 휴강<br>1차 프로그래밍 과제 |
| 11주차 | 5/12, 5/14 | Priority queues, heap, leftist trees | 과제 대체 휴강<br>2차 프로그래밍 과제 |
| 12주차 | 5/19, 5/21 | Priority queues, heap, leftist trees | L7 Skip List and Hashing |
| 13주차 | 5/26, 5/28 | Tournament trees and bin packing | L8 Binary and Other Trees |
| 14주차 | 6/2, 6/4 | Binary search trees | L9 Priority Queues, Heaps, Leftist Trees |
| 15주차 | 6/9, 6/11 | Binary search trees | L10 Binary Search Trees<br>종강 |
| 16주차 | 6/16, 6/18 | 기말고사 | - |

- 계획된 주제는 강의계획서의 주별 일정을 따르며, 강의계획서는 시험 주차를 뺀 모든 주차의 자료를 PPT 슬라이드로 계획했다.
- L2 Time Complexity Theory for Performance Measurement는 2주차와 3주차에 걸쳐 다뤘다.
- 8주차는 휴강했고, 10주차와 11주차는 과제로 수업을 대체하여 휴강했으며, 15주차에 종강했다. 평가 항목에는 시험이 없다.
- 실제 진도는 7주차까지 계획을 따랐고, L7부터는 계획보다 3주 늦은 12주차부터 진행했다. 13주차에 계획된 Tournament trees and bin packing을 다룬 강의자료는 없다.
- 강의자료의 번호 L1\~L10과 LMS 퀴즈 제목 "Quiz for Chapter N"의 번호는 이 레포지토리의 `Lec01`\~`Lec10`에 대응한다. 단원 목록은 [`Lecture-Notes` 색인](Lecture-Notes/README.ko.md)에 있다.

---

<br>

## 6. 참고 자료

| 유형 | 내용 |
|:-----|:-----|
| 강의자료 | 교수자가 제공한 PPT 슬라이드(L1\~L10)와 필기 노트. L1\~L5에는 필기본이, L1\~L3에는 번역본이 함께 있다. |
| 강의 영상 | L1~L10의 강의 영상. L1과 L9는 두 편으로 나뉘어 있다. |
| 참고 도서 | F. M. Carrano and T. M. Henry, *Data Structures and Abstractions with Java*, 4th ed. Boston, MA, USA: Pearson, 2015. |

- 강의계획서는 지정 교재 없이 교수자가 PPT 강의 노트를 제공하며, 위의 Carrano와 Henry의 책을 참고 교재로 두었다.
