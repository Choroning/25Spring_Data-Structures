# Chapter 06 — 큐 (Queues)

> **최종 수정일:** 2026-04-01
>
> Carrano & Henry, Data Structures and Abstractions with Java 4th Ed. Ch 6

> **선수 지식**: [프로그래밍언어] Java. [자료구조] 스택 (제5장).
>
> **학습 목표**:
> 1. 배열과 연결 리스트를 사용하여 큐를 구현할 수 있다
> 2. 효율적인 큐 연산을 위해 원형 배열 기법을 적용할 수 있다
> 3. 큐 변형(덱, 우선순위 큐)을 구분할 수 있다

---

## 목차

1. [Queue ADT](#1-queue-adt)
2. [배열 기반 큐](#2-배열-기반-큐)
3. [원형 큐](#3-원형-큐)
4. [연결 큐](#4-연결-큐)
5. [양방향 큐 (Deque)](#5-양방향-큐-deque)
6. [큐의 응용](#6-큐의-응용)
7. [요약](#요약)
8. [부록](#부록)

---

<br>

## 1. Queue ADT

### 1.1 정의

**큐(queue)** 는 다음과 같은 선형 리스트이다:
- 삽입(enqueue)은 **후단(rear)** 에서만 수행
- 삭제(dequeue)는 **전단(front)** 에서만 수행

이는 **FIFO**(First In, First Out) 원칙을 따른다.

> **핵심:** 스택에서는 push와 pop이 모두 top에서 이루어진다(LIFO). 큐에서는 push는 rear에서, pop은 front에서 이루어진다(FIFO).

### 1.2 주요 연산

| 연산 | 설명 | 시간 복잡도 |
|------|------|------------|
| `push(x)` / `enqueue(x)` | 후단에 원소 삽입 | $O(1)$ |
| `pop()` / `dequeue()` | 전단에서 원소 삭제 | $O(1)$ |
| `front()` | 전단 원소 반환 | $O(1)$ |
| `back()` | 후단 원소 반환 | $O(1)$ |
| `empty()` | 큐가 비어있는지 확인 | $O(1)$ |
| `size()` | 원소의 개수 반환 | $O(1)$ |

---

<br>

## 2. 배열 기반 큐

### 2.1 단순 배열 큐

`front`를 왼쪽 끝, `rear`를 오른쪽 끝으로 사용:
- `front`는 항상 0
- `push(x)`: `array[++rear] = x` — $O(1)$
- `pop()`: 모든 원소를 왼쪽으로 이동 — $O(n)$

`pop()` 연산이 $O(n)$의 이동을 요구하므로 비효율적이다.

### 2.2 수정된 위치 공식

`front`가 오른쪽으로 이동할 수 있는 수정된 위치 공식을 사용:
$$\text{location}(i) = \text{location}(1) + i - 1$$

- `pop()`: `front`를 1 증가 — $O(1)$
- 문제점: `rear = MaxSize - 1`이고 `front > 0`일 때, 전단의 공간이 낭비됨

---

<br>

## 3. 원형 큐

### 3.1 개념

나머지(modulo) 연산을 사용하여 배열을 **원형** 으로 취급:

$$\text{location}(i) = (\text{location}(1) + i - 1) \% \text{MaxSize}$$

삽입과 삭제 연산이 모두 $O(1)$이 된다.

### 3.2 구현 세부사항

- **시계 방향 이동**: `rear = (rear + 1) % queue.length`
- 정수 변수 `theFront`과 `theBack` 사용:
  - `theFront`은 첫 번째 원소에서 반시계 방향으로 한 칸 앞의 위치
  - `theBack`은 마지막 원소의 위치
- 초기화: `front = rear = 0`

### 3.3 가득 참(Full) vs. 비어 있음(Empty) 구분

삽입으로 큐가 가득 찰 때: `front == rear`.
삭제로 큐가 비게 될 때: `front == rear`.

`front`와 `rear`만으로는 가득 찬 상태와 비어 있는 상태를 **구분할 수 없다**.

**해결 방법**: 한 칸을 낭비한다 — 큐가 가득 찬 상태는 `(rear + 1) % capacity == front`일 때이다. 이는 최대 $\text{capacity} - 1$개의 원소를 저장할 수 있음을 의미한다.

### 3.4 삽입 연산 (Enqueue)

```cpp
void push(const T& element) {
    int newRear = (rear + 1) % capacity;
    if (newRear == front)
        throw std::overflow_error("Queue is full");
    rear = newRear;
    queue[rear] = element;
}
```

### 3.5 삭제 연산 (Dequeue)

```cpp
T pop() {
    if (front == rear)
        throw std::underflow_error("Queue is empty");
    front = (front + 1) % capacity;
    return queue[front];
}
```

---

<br>

## 4. 연결 큐

### 4.1 구현

`front`와 `rear` 포인터를 가진 단일 연결 리스트를 사용:
- `enqueue`: 후단에 삽입 — $O(1)$
- `dequeue`: 전단에서 삭제 — $O(1)$

```cpp
struct Node {
    T data;
    Node* next;
};
Node* frontNode;
Node* rearNode;
```

### 4.2 장점

- 크기 제한 없음 (동적 메모리)
- 원형 배열의 슬롯 낭비 없음

---

<br>

## 5. 양방향 큐 (Deque)

**덱(deque)** 은 양쪽 끝에서 삽입과 삭제가 가능하다:
- `pushFront`, `pushBack`, `popFront`, `popBack`
- 모든 연산 $O(1)$

---

<br>

## 6. 큐의 응용

### 6.1 CPU 스케줄링

- 라운드 로빈 스케줄링: 프로세스들이 번갈아가며 CPU를 사용
- 준비 큐(ready queue)가 실행 대기 중인 프로세스를 보유

### 6.2 너비 우선 탐색 (BFS)

```
enqueue(start)
while queue is not empty:
    node = dequeue()
    for each neighbor of node:
        if not visited:
            mark visited
            enqueue(neighbor)
```

### 6.3 버퍼 관리

- 인쇄 작업 스풀링
- 키보드 입력 버퍼
- 네트워크 패킷 버퍼링

---

<br>

## 요약

| 개념 | 핵심 |
|------|------|
| 큐 | FIFO 자료구조; 후단에서 삽입, 전단에서 삭제 |
| 단순 배열 큐 | Pop에 $O(n)$ 이동 필요 |
| 원형 배열 큐 | 나머지 연산 사용; 모든 연산 $O(1)$; 한 칸 낭비 |
| 가득 참 vs. 비어 있음 | 둘 다 `front == rear`; capacity-1 또는 카운터 사용 |
| 연결 큐 | front와 rear 포인터; 진정한 동적 구조 |
| 덱 | 양방향; 양쪽 끝에서 삽입/삭제 |

---

<br>

## 부록

### 원형 큐 vs. 선형 큐

| 속성 | 선형 큐 | 원형 큐 |
|------|---------|---------|
| Pop | $O(n)$ 또는 공간 낭비 | $O(1)$ |
| 공간 활용 | 전단에 빈 공간 발생 가능 | 해제된 공간 재사용 |
| 가득 참 감지 | `rear == capacity - 1` | `(rear+1) % cap == front` |
| 구현 | 단순 | 나머지 연산 필요 |

### 큐의 변형

- **우선순위 큐(Priority Queue)**: 우선순위에 따라 삭제 (Chapter 9)
- **원형 버퍼(Circular Buffer)**: 고정 크기, 가장 오래된 데이터를 덮어씀
- **메시지 큐(Message Queue)**: 프로세스 간 통신 (운영체제 개념)
