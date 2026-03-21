# Chapter 03 — 배열과 연결 리스트

> **최종 수정일:** 2026-03-21

---

## 목차

1. [선형 리스트](#1-선형-리스트)
2. [배열 표현](#2-배열-표현)
3. [연결 표현](#3-연결-표현)
4. [단일 연결 리스트](#4-단일-연결-리스트)
5. [이중 연결 리스트](#5-이중-연결-리스트)
6. [원형 리스트](#6-원형-리스트)
7. [비교: 배열 vs. 연결 리스트](#7-비교-배열-vs-연결-리스트)
8. [요약](#요약)
9. [부록](#부록)

---

## 1. 선형 리스트

### 1.1 정의

**선형 리스트**(또는 순서 리스트)는 $(e_1, e_2, \ldots, e_n)$ 형태의 데이터 객체로, 다음을 만족한다:
- $e_i$는 $i$번째 원소
- $n \geq 0$은 원소의 개수(유한)
- $e_1$은 첫 번째 원소, $e_n$은 마지막 원소

### 1.2 ADT 연산

| 연산 | 설명 |
|------|------|
| `empty()` | 리스트가 비어 있는지 확인 |
| `size()` | 원소의 개수를 반환 |
| `get(index)` | 주어진 인덱스의 원소를 반환 |
| `indexOf(element)` | 첫 번째 출현 위치의 인덱스를 반환 |
| `insert(index, element)` | 주어진 인덱스에 원소를 삽입 |
| `erase(index)` | 주어진 인덱스의 원소를 삭제 |

---

## 2. 배열 표현

### 2.1 수식 기반 표현

일차원 배열을 매핑 공식과 함께 사용한다:
$$\text{location}(i) = i - 1 \quad \text{(0-indexed)}$$

원소 $e_i$는 `array[i-1]`에 저장된다.

### 2.2 연산 복잡도

| 연산 | 시간 복잡도 |
|------|-------------|
| `get(index)` | $O(1)$ |
| `indexOf(element)` | $O(n)$ |
| `insert(index, element)` | $O(n)$ (이동 필요) |
| `erase(index)` | $O(n)$ (이동 필요) |

### 2.3 삽입 연산

위치 $k$에 삽입하려면 원소 $k, k+1, \ldots, n-1$을 오른쪽으로 한 칸씩 이동해야 한다:

```cpp
// 인덱스 k에 원소를 삽입
for (int i = size - 1; i >= k; i--)
    arr[i + 1] = arr[i];  // 오른쪽으로 이동
arr[k] = element;
size++;
```

최악 경우 (위치 0에 삽입): $O(n)$ 이동. 최선 경우 (끝에 삽입): $O(1)$.

### 2.4 동적 배열

배열이 가득 찼을 때 **두 배 크기의 새 배열**을 할당하고 원소를 복사한다:
- 개별 최악 경우: $O(n)$
- 삽입당 분할 상환 비용: $O(1)$

---

## 3. 연결 표현

### 3.1 노드 구조

각 노드는 다음을 포함한다:
- **데이터 필드**: 원소를 저장
- **링크(포인터) 필드**: 다음 노드를 가리킴

```cpp
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(const T& d, Node<T>* n = nullptr) : data(d), next(n) {}
};
```

### 3.2 배열 대비 장점

- 동적 크기 (사전 할당 불필요)
- 알려진 위치에서의 효율적인 삽입/삭제: $O(1)$
- 미사용 용량으로 인한 공간 낭비 없음

### 3.3 단점

- 임의 접근 불가: 원소 $i$에 도달하는 데 $O(n)$
- 포인터를 위한 추가 메모리
- 캐시 비친화적 (노드가 메모리에 분산)

---

## 4. 단일 연결 리스트

### 4.1 구조

```
head -> [data|next] -> [data|next] -> [data|next] -> nullptr
```

### 4.2 핵심 연산

**앞에 삽입**: $O(1)$
```cpp
Node<T>* newNode = new Node<T>(value);
newNode->next = head;
head = newNode;
```

**앞에서 삭제**: $O(1)$
```cpp
Node<T>* temp = head;
head = head->next;
delete temp;
```

**검색**: $O(n)$
```cpp
Node<T>* curr = head;
while (curr != nullptr) {
    if (curr->data == target) return curr;
    curr = curr->next;
}
return nullptr;
```

**주어진 노드 뒤에 삽입**: $O(1)$
```cpp
Node<T>* newNode = new Node<T>(value);
newNode->next = prev->next;
prev->next = newNode;
```

---

## 5. 이중 연결 리스트

### 5.1 노드 구조

```cpp
template <typename T>
struct DNode {
    T data;
    DNode<T>* prev;
    DNode<T>* next;
};
```

### 5.2 장점

- 양방향 순회 가능
- 알려진 노드의 삭제가 $O(1)$ (선행자를 찾을 필요 없음)
- 실행 취소 연산, 브라우저 히스토리 등에 유용

### 5.3 절충점

노드당 추가 포인터(더 많은 메모리)가 필요하지만, 양방향 순회와 더 간단한 삭제가 가능하다.

---

## 6. 원형 리스트

### 6.1 원형 단일 연결 리스트

마지막 노드의 `next` 포인터가 `nullptr` 대신 첫 번째 노드를 다시 가리킨다.

### 6.2 활용 사례

- 라운드 로빈 스케줄링
- 원형 버퍼
- 요세푸스 문제(Josephus problem)

---

## 7. 비교: 배열 vs. 연결 리스트

| 특성 | 배열 | 연결 리스트 |
|------|------|-------------|
| 인덱스 접근 | $O(1)$ | $O(n)$ |
| 앞에 삽입 | $O(n)$ | $O(1)$ |
| 끝에 삽입 | $O(1)$ 분할 상환 | 꼬리 포인터 있으면 $O(1)$ |
| 중간에 삽입 | $O(n)$ | 위치를 찾은 후 $O(1)$ |
| 앞에서 삭제 | $O(n)$ | $O(1)$ |
| 메모리 오버헤드 | 없음 (연속) | 노드당 추가 포인터 |
| 캐시 성능 | 우수 | 불량 |
| 메모리 할당 | 연속 블록 | 분산 |

---

## 요약

| 개념 | 핵심 포인트 |
|------|-------------|
| 선형 리스트 | 순서 있는 컬렉션 $(e_1, \ldots, e_n)$ |
| 배열 | 직접 접근 $O(1)$; 삽입/삭제 $O(n)$ |
| 단일 연결 리스트 | 순차 접근; 알려진 위치에서 효율적인 삽입/삭제 |
| 이중 연결 리스트 | 양방향 순회; 알려진 노드의 $O(1)$ 삭제 |
| 원형 리스트 | 마지막 노드가 첫 번째로 연결; 순환 프로세스에 유용 |
| 동적 배열 | 배가 전략을 통한 분할 상환 $O(1)$ 추가 |

---

## 부록

### 반복자 디자인 패턴

반복자(Iterator)는 배열과 연결 리스트 모두를 순회하는 통일된 방법을 제공한다:

```cpp
template <typename T>
class LinkedListIterator {
    Node<T>* current;
public:
    LinkedListIterator(Node<T>* node) : current(node) {}
    T& operator*() { return current->data; }
    LinkedListIterator& operator++() { current = current->next; return *this; }
    bool operator!=(const LinkedListIterator& other) { return current != other.current; }
};
```

### 일반적인 면접 질문

1. **연결 리스트 뒤집기** (반복적 및 재귀적)
2. **사이클 검출** (Floyd의 거북이와 토끼 알고리즘)
3. **중간 원소 찾기** (투 포인터 기법)
4. **정렬된 두 연결 리스트 병합**
