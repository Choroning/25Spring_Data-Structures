# HW2 코드 총정리 — 연결 큐의 push와 pop

[레포지토리 안내](../../README.ko.md) | [English](Code-Walkthrough.md) | [한국어](Code-Walkthrough.ko.md)

> **최종 수정일:** 2026-10-19

> **학습 목표:**
> 1. `push`와 `pop`의 각 분기가 두 표현에서 바꾸는 포인터를 설명할 수 있다
> 2. 테스트용 드라이버의 `Queue<T>`가 두 표현의 남은 노드를 해제하는 방법을 설명할 수 있다
> 3. 드라이버가 선입선출 순서와 pop 시간을 확인하는 방법을 설명할 수 있다
> 4. 두 표현에서 push와 pop의 실행을 단계별로 추적할 수 있다

---

## 목차

- [1. 파일 구성](#1-파일-구성)
- [2. push](#2-push)
- [3. pop: type 1](#3-pop-type-1)
- [4. pop: type 2](#4-pop-type-2)
- [5. 드라이버의 헤더와 Node](#5-드라이버의-헤더와-node)
- [6. Queue 클래스](#6-queue-클래스)
- [7. showPopOrder와 popTime](#7-showpoporder와-poptime)
- [8. main](#8-main)
- [9. 실행 추적](#9-실행-추적)
- [10. 복잡도](#10-복잡도)
- [요약](#요약)
- [점검 문제](#점검-문제)

---

<br>

## 1. 파일 구성

짝이 되는 문서 [HW2 과제 해설](Assignment-Explanation.ko.md)은 두 표현, 설계, 테스트, 실행 시간의 해석을 정리한다. 이 문서는 `Solution`의 두 파일을 처음부터 끝까지 읽는다. 줄 번호는 모두 각 파일 기준이다. `Push-and-Pop.cpp`(82줄)는 제출한 두 함수이고, `Test-Driver.cpp`(111줄)는 두 함수를 실행하기 위해 Claude Code로 작성한 테스트용 드라이버이다.

| 파일 | 줄 | 부분 | 작성 |
|:-----|:-----|:-----|:-----|
| `Push-and-Pop.cpp` | 1~12 | Doxygen 헤더 | 레포지토리 형식에 맞추어 추가 |
| `Push-and-Pop.cpp` | 14~40 | `push` | 제출한 코드 |
| `Push-and-Pop.cpp` | 42~82 | `pop` | 제출한 코드 |
| `Test-Driver.cpp` | 1~19 | 헤더 주석과 `#include` | 테스트용으로 작성 |
| `Test-Driver.cpp` | 21~32 | `Node<T>` | 테스트용으로 작성 |
| `Test-Driver.cpp` | 34~69 | `Queue<T>` (60번 줄에서 제출한 함수를 포함) | 테스트용으로 작성 |
| `Test-Driver.cpp` | 71~98 | `showPopOrder`, `popTime` | 테스트용으로 작성 |
| `Test-Driver.cpp` | 100~111 | `main` | 테스트용으로 작성 |

*표 1. 두 파일의 구성*

---

<br>

## 2. push

```cpp
void push(const T& item)
{
    Node<T>* newNode = new Node<T>(item);

    // (1-1) Program an operation push for type1 (20 Points)
    if (type == 1) {
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->link = newNode;
            rear       = newNode;
        }
    }


    // (1-2) Program an operation push for type2 (10 Points)
    else {
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            newNode->link = rear;
            rear          = newNode;
        }
    }

    queueSize++;
}
```

16번 줄은 뼈대 코드에 있던 줄로, `item`을 데이터로 갖고 링크가 `nullptr`인 새 노드를 할당한다. 19\~26번 줄은 type 1이다. 큐가 비어 있으면(20번 줄) 새 노드가 전단이자 후단이 되고(21번 줄), 그렇지 않으면 현재 후단의 링크가 새 노드를 가리키게 한 뒤(23번 줄) 후단을 새 노드로 옮긴다(24번 줄). 새 노드의 링크는 생성자가 정한 `nullptr` 그대로이므로 새 후단이 체인의 끝이 된다. 30\~37번 줄은 type 2이다. 빈 큐의 처리는 같고, 그렇지 않으면 새 노드의 링크가 현재 후단을 가리키게 한 뒤(34번 줄) 후단을 새 노드로 옮긴다(35번 줄). 27\~28번 줄의 빈 줄은 제출한 코드 그대로이다. `if` 블록과 `else` 사이에 빈 줄과 주석이 있어도 문법상 하나의 `if`-`else` 문이다. 39번 줄은 뼈대 코드의 원소 수 증가이다.

---

<br>

## 3. pop: type 1

```cpp
T pop()
{
    T popData;

    // (2-1) Program an operation pop for type1 (20 Points)
    if (type == 1) {
        if (front == nullptr) return T();

        Node<T>* popNode = front;
        popData          = popNode->data;

        front = front->link;
        if (front == nullptr)
            rear = nullptr;

        delete popNode;
    }
```

44번 줄의 `popData`는 뼈대 코드가 선언한 반환값이다. 48번 줄은 빈 큐이면 곧바로 `T()`를 반환하여 80번 줄의 원소 수 감소에 이르지 않으므로 원소 수가 줄지 않는다. 50\~51번 줄은 삭제할 전단을 `popNode`에 보관하고 그 데이터를 `popData`에 복사한다. 53번 줄은 전단을 다음 노드로 옮기고, 54\~55번 줄은 그 결과 큐가 비었으면 후단도 `nullptr`로 바꾼다. 57번 줄이 원래 전단을 해제한다. 데이터를 먼저 복사하고 전단을 옮긴 뒤 해제하므로 해제한 노드를 읽지 않는다.

---

<br>

## 4. pop: type 2

```cpp
    // (2-2) Program an operation pop for type2 (30 Points)
    else {
        if (front == nullptr) return T();

        popData = front->data;

        if (front == rear) {
            delete front;
            front = rear = nullptr;
        } else {
            Node<T>* prev = rear;
            while (prev->link != front)
                prev = prev->link;

            delete front;
            front      = prev;
            front->link = nullptr;
        }
    }

    queueSize--;
    return popData;
}
```

62번 줄은 type 1과 같은 빈 큐 처리이고, 64번 줄은 전단의 데이터를 먼저 복사한다. 66\~68번 줄은 원소가 하나인 경우로, 노드를 해제하고 두 포인터를 비운다. 70\~72번 줄은 `prev`를 후단에서 출발시켜, 링크가 전단을 가리키는 노드에 이를 때까지 링크를 따라간다. type 2의 링크는 후단에서 전단 쪽을 향하므로 이 반복은 큐의 거의 전체를 지나며, 원소가 $k$개이면 $k - 2$번 실행된다. 74번 줄이 원래 전단을 해제하고, 75번 줄이 `prev`를 새 전단으로 삼으며, 76번 줄이 새 전단의 링크를 `nullptr`로 바꾸어 방금 해제한 노드와의 연결을 끊는다. 80\~81번 줄은 뼈대 코드의 원소 수 감소와 반환이다.

---

<br>

## 5. 드라이버의 헤더와 Node

`Test-Driver.cpp`의 1\~15번 줄은 Doxygen 헤더이며, 테스트용으로 작성한 파일이라는 사실과 빌드 방법을 적는다. 17\~19번 줄은 시간 측정을 위한 `<chrono>`, 명령행 인자를 정수로 바꾸는 `std::atoi`를 위한 `<cstdlib>`, 출력을 위한 `<iostream>`이다.

```cpp
template <class T>
class Node {
public:
    explicit Node(const T& data) : data(data), link(nullptr) {}

    T data;
    Node<T>* link;
};
```

25~32번 줄의 `Node<T>`는 데이터 필드와 링크 필드를 갖고, 생성자가 링크를 `nullptr`로 둔다. 제출한 `push`는 빈 큐에 넣은 첫 노드와 type 1의 새 후단이 체인의 끝이 되는 것을 이 초기값에 맡기므로, 이 생성자는 두 함수가 올바르게 동작하기 위한 전제이다. 두 필드는 `public`이어서 `Queue<T>`의 멤버 함수가 바로 접근한다.

---

<br>

## 6. Queue 클래스

```cpp
explicit Queue(int type) : type(type), front(nullptr), rear(nullptr), queueSize(0) {}

/** @brief Delete the remaining nodes by following the links from where they start */
~Queue() {
    Node<T>* cur = (type == 1) ? front : rear;
    while (cur != nullptr) {
        Node<T>* next = cur->link;
        delete cur;
        cur = next;
    }
}
```

44번 줄의 생성자는 표현을 정하고 빈 큐를 만든다. 46\~54번 줄의 소멸자는 큐에 남은 노드를 해제한다. 링크가 시작되는 노드는 type 1에서는 `front`, type 2에서는 `rear`이므로 그 노드에서 출발하여 `nullptr`에 이를 때까지 다음 노드를 먼저 저장하고 현재 노드를 해제한다. 노드가 $m$개 남았으면 $O(m)$이다. 소멸자에서 `pop`을 반복하면 type 2에서 $O(m^2)$이 걸리므로 링크를 직접 따라간다. 56\~57번 줄은 복사 생성자와 복사 대입을 삭제한다. 복사를 허용하면 두 객체가 같은 노드를 가리키다가 각자의 소멸자에서 같은 노드를 두 번 해제하기 때문이다.

59\~60번 줄은 클래스 정의 안에서 `Push-and-Pop.cpp`를 `#include`한다. 전처리기가 이 줄을 파일의 내용으로 바꾸므로 제출한 `push`와 `pop`은 고치지 않은 채 멤버 함수가 되고, 함수 안의 `type`, `front`, `rear`, `queueSize`는 64\~68번 줄의 멤버 변수를 가리킨다. 62번 줄의 `size`는 원소 수를 돌려주며, 드라이버가 빈 큐에서 pop하지 않도록 쓴다.

---

<br>

## 7. showPopOrder와 popTime

```cpp
static void showPopOrder(int type, int count) {
    Queue<int> q(type);
    for (int i = 0; i < count; ++i)
        q.push(i);

    std::cout << "type" << type << " pop order :";
    while (q.size() > 0)
        std::cout << ' ' << q.pop();
    std::cout << '\n';
}
```

72~81번 줄의 `showPopOrder`는 0부터 `count - 1`까지 push한 뒤 큐가 빌 때까지 pop하며 꺼낸 순서대로 출력한다. 선입선출이면 넣은 순서와 같은 `0 1 2 3 4`가 나온다.

```cpp
static long long popTime(int type, int n) {
    Queue<int> q(type);
    for (int i = 0; i < n; ++i)
        q.push(i);

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) {
        if (q.pop() != i) {     // FIFO check: the i-th pop must return i
            std::cout << "type" << type << " pop order is wrong at " << i << '\n';
            break;
        }
    }
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}
```

84~98번 줄의 `popTime`은 원소 $n$개를 push한 뒤, pop $n$번에 걸린 시간만 잰다. push는 두 표현 모두 $O(1)$이므로 측정에서 뺀다. `std::chrono::steady_clock`은 시스템 시각이 조정되어도 거꾸로 가지 않는 시계이며, 두 시점의 차이를 밀리초로 바꾸어 돌려준다. 반복 안에서 $i$번째 pop이 $i$인지 비교하여 순서가 어긋나면 위치를 출력하고 멈춘다. 비교 한 번의 비용은 type 2의 pop 한 번에 비해 무시할 만큼 작다.

---

<br>

## 8. main

101번 줄은 측정할 원소 수를 제출한 실행 화면과 같은 200,000으로 두고, 102\~103번 줄은 명령행 인자가 있으면 그 값으로 바꾼다. `200'000`의 작은따옴표는 C++14부터 쓸 수 있는 자릿수 구분자이다. 105\~106번 줄은 두 표현의 pop 순서를 원소 5개로 확인하고, 108\~109번 줄은 두 표현의 pop 시간을 제출한 화면과 같은 형식(`type1 pop time : 1ms`)으로 출력한다. 각 큐는 함수 안의 지역 변수이므로 함수가 끝날 때 소멸자가 남은 노드를 해제한다.

---

<br>

## 9. 실행 추적

type 2 큐에 1, 2, 3을 push하고 두 번 pop하는 과정을 추적하면 다음과 같다. 큐는 링크를 따라 후단에서 전단 쪽으로 적는다.

| 단계 | 호출 | 실행된 분기 | 호출 뒤의 큐 (후단부터) | `front` | `rear` |
|:-----|:-----|:-----|:-----|:-----|:-----|
| 1 | `push(1)` | 빈 큐 (31~32번 줄) | `1 -> NULL` | 1 | 1 |
| 2 | `push(2)` | 34~35번 줄 | `2 -> 1 -> NULL` | 1 | 2 |
| 3 | `push(3)` | 34~35번 줄 | `3 -> 2 -> 1 -> NULL` | 1 | 3 |
| 4 | `pop()`이 1을 반환 | 70~76번 줄, 반복 1번 (`prev`: 3에서 2로) | `3 -> 2 -> NULL` | 2 | 3 |
| 5 | `pop()`이 2를 반환 | 70~76번 줄, 반복 0번 (`prev`: 3) | `3 -> NULL` | 3 | 3 |

*표 2. type 2 큐의 push와 pop 추적*

4단계에서 `prev`는 3에서 출발하는데, 3의 링크는 2이고 전단 1이 아니므로 2로 한 번 옮긴 뒤 2의 링크가 1이어서 멈춘다. 원소가 3개이므로 반복은 $3 - 2 = 1$번이다. 같은 호출을 type 1에서 하면 push는 23\~24번 줄을, pop은 50\~57번 줄을 실행하며 반복이 없다.

---

<br>

## 10. 복잡도

큐에 든 원소 수를 $k$라 하면 각 함수의 시간 복잡도는 다음과 같다.

| 함수 | type 1 | type 2 | 근거 |
|:-----|:-----|:-----|:-----|
| `push` | $O(1)$ | $O(1)$ | 링크 하나와 `rear`만 바꾼다 |
| `pop` | $O(1)$ | $\Theta(k)$ | type 2는 새 전단을 찾으려고 후단부터 $k - 2$번 이동한다 |
| 원소 $n$개를 모두 `pop` | $O(n)$ | $\Theta(n^2)$ | type 2의 반복은 모두 $(n-1)(n-2)/2$번이다 |
| 소멸자 | $O(k)$ | $O(k)$ | 링크가 시작되는 노드부터 한 번씩 해제한다 |

*표 3. 두 표현에서 각 함수의 시간 복잡도*

---

<br>

## 요약

| 개념 | 핵심 요약 |
|:-----|:-----|
| 파일 구성 | `Push-and-Pop.cpp`는 제출한 두 함수이고, `Test-Driver.cpp`는 이를 실행하기 위해 작성한 테스트용 드라이버이다. |
| `push` | 빈 큐이면 새 노드를 전단이자 후단으로 삼고, 아니면 type 1은 후단의 링크를, type 2는 새 노드의 링크를 바꾼 뒤 `rear`를 옮긴다. |
| type 1의 `pop` | 데이터를 복사하고 `front`를 다음 노드로 옮긴 뒤 원래 전단을 해제하며, 큐가 비면 `rear`도 비운다. |
| type 2의 `pop` | 원소가 하나이면 바로 해제하고, 아니면 링크가 전단인 노드를 후단부터 찾아 새 전단으로 삼고 그 링크를 끊는다. |
| `Node<T>`의 생성자 | 링크를 `nullptr`로 두어 제출한 `push`가 새 끝 노드의 링크를 따로 정하지 않아도 되게 한다. |
| 드라이버 | 소멸자가 표현에 따라 `front` 또는 `rear`부터 노드를 해제하고, `popTime`이 pop만의 시간을 재며 선입선출 순서를 함께 확인한다. |

---

<br>

## 점검 문제

1. **생성자의 초기값:** `Node<T>`의 생성자가 링크를 초기화하지 않는다면 제출한 `push`의 어느 경우에 문제가 생기는가?

   <details>
   <summary>정답</summary>

   빈 큐에 넣는 첫 노드(두 표현 모두)와 type 1에서 후단에 붙는 새 노드의 링크가 쓰레기 값이 된다. type 1에서는 후단의 링크가, type 2에서는 전단의 링크가 체인의 끝을 나타내야 하므로, 소멸자처럼 링크를 `nullptr`까지 따라가는 코드가 잘못된 주소를 읽는다. type 2의 새 노드는 34번 줄이 링크를 정하므로 영향이 없다.

   </details>

2. **소멸자의 출발점:** 소멸자가 표현과 관계없이 언제나 `front`에서 출발하면 type 2에서 어떻게 되는가?

   <details>
   <summary>정답</summary>

   type 2에서 `front`의 링크는 `nullptr`이므로 전단 노드 하나만 해제하고 반복이 끝난다. 나머지 노드는 어디에서도 해제되지 않아 메모리가 누수된다.

   </details>

3. **측정 범위:** `popTime`이 push까지 포함해 시간을 재면 표의 결과가 크게 달라지는가?

   <details>
   <summary>정답</summary>

   크게 달라지지 않는다. push는 두 표현 모두 $O(1)$이므로 원소 200,000개를 넣는 시간은 수 ms 정도이다. type 1의 결과는 몇 ms 늘 수 있지만, type 2의 결과는 $\Theta(n^2)$인 pop이 대부분을 차지하므로 거의 같다.

   </details>

4. **반복 추적:** type 2 큐에 1, 2, 3, 4가 들어 있을 때 네 번 pop하면 각 pop의 while 반복 횟수는 몇 번이며, 합은 공식 $(n-1)(n-2)/2$와 맞는가?

   <details>
   <summary>정답</summary>

   원소가 4, 3, 2개일 때 각각 2, 1, 0번이고, 원소가 1개일 때는 `front == rear` 분기로 반복이 없다. 합은 3번이며, $n = 4$이면 $(4-1)(4-2)/2 = 3$이므로 공식과 맞는다.

   </details>
