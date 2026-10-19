# HW1 과제 안내문 — 헤드 노드가 있는 원형 연결 리스트

[레포지토리 안내](../../../README.ko.md) | [English](Assignment.md) | [한국어](Assignment.ko.md)

> **최종 수정일:** 2026-10-19

자료구조 1차 프로그래밍 과제(Programming Homework #1), 헤드 노드가 있는 원형 연결 리스트(Circular Linked List with Head Node)이다. 과제는 네 문제로 이루어지며 모두 100점이다. 문제 1과 2는 헤드 노드가 있는 원형 연결 리스트의 멤버 함수 본문을 채운다.

---

<br>

## 문제 1. InsertFront (20점)

헤드 노드가 있는 원형 연결 리스트의 연산 `InsertFront`를 프로그래밍하라.

```cpp
void InsertFront(const T& item) {
    ChainNode<T>* newNode = new ChainNode<T>(item);

    // (1-1) The Link of newNode points out the original first node. (10 points)

    // (1-2) The newNode will be a new first node. (10 points)

}
```

---

<br>

## 문제 2. InsertRear (50점)

헤드 노드가 있는 원형 연결 리스트의 연산 `InsertRear`를 프로그래밍하라.

```cpp
void InsertRear(const T& item) {
    ChainNode<T>* newNode = new ChainNode<T>(item);

    ChainNode<T>* cur; // (2-1) The first node is stored at the *cur pointer. (10 points)

    // (2-2) We will find the last node through the while loop, and the last node is stored at the *cur pointer. (20 points)

    // (2-3) The newNode will be inserted after the last node. (10 points)

    // (2-4) The last node should always point out the head node. (10 points)

}
```

---

<br>

## 문제 3. 실행 화면 (20점)

완성한 코드로 프로그램을 실행하고 결과 화면을 캡처하라. 안내문은 두 번의 실행 결과를 예시로 든다. 첫 번째 실행은 검색 프롬프트에 4를 입력한다.

```text
Inserting nodes using operation 'InsertFront':

1

2->1

3->2->1


Inserting nodes using operation 'InsertRear':

3->2->1->2

3->2->1->2->4

3->2->1->2->4->6


Print a Circular Linked List:

3->2->1->2->4->6


Which data is searching for? : 4

4 is at the index 5

Node<3> is deleted
Node<2> is deleted
Node<1> is deleted
Node<2> is deleted
Node<4> is deleted
Node<6> is deleted

Destructor is executed successfully!
```

두 번째 실행은 리스트에 없는 9를 입력한다. 리스트를 출력하는 부분까지는 첫 번째 실행과 같고, 그 뒤는 다음과 같다.

```text
Which data is searching for? : 9

There's no data you want to search!

Node<3> is deleted
Node<2> is deleted
Node<1> is deleted
Node<2> is deleted
Node<4> is deleted
Node<6> is deleted

Destructor is executed successfully!
```

---

<br>

## 문제 4. 헤드 노드에 관한 질문 (10점)

원형 연결 리스트의 헤드 노드에 관한 다음 질문에 답하라.

1. 원형 연결 리스트에서 헤드 노드를 쓰는 장점을 설명하라.
2. 헤드 노드를 앞에 두는 것과 뒤에 두는 것의 차이를 설명하라.
