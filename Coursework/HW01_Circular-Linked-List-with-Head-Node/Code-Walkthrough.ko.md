# HW1 코드 총정리 — 헤드 노드가 있는 원형 연결 리스트

[레포지토리 안내](../../README.ko.md) | [English](Code-Walkthrough.md) | [한국어](Code-Walkthrough.ko.md)

> **최종 수정일:** 2026-10-26

> **학습 목표:**
> 1. `InsertFront`와 `InsertRear`의 각 문장이 바꾸는 링크를 설명할 수 있다
> 2. 테스트용 드라이버의 `CircularList<T>`가 헤드 노드를 만들고 노드를 해제하는 과정을 설명할 수 있다
> 3. 클래스 정의 안의 `#include`가 제출한 함수를 멤버 함수로 만드는 방법을 설명할 수 있다
> 4. 실행 순서에 따라 리스트의 상태와 출력을 추적할 수 있다

---

## 목차

- [1. 파일 구성](#1-파일-구성)
- [2. InsertFront](#2-insertfront)
- [3. InsertRear](#3-insertrear)
- [4. 드라이버의 헤더와 ChainNode](#4-드라이버의-헤더와-chainnode)
- [5. 생성자와 소멸자](#5-생성자와-소멸자)
- [6. 제출한 함수의 포함과 Print](#6-제출한-함수의-포함과-print)
- [7. Search](#7-search)
- [8. main](#8-main)
- [9. 실행 추적](#9-실행-추적)
- [10. 복잡도](#10-복잡도)
- [요약](#요약)
- [점검 문제](#점검-문제)

---

<br>

## 1. 파일 구성

짝이 되는 문서 [HW1 과제 해설](Assignment-Explanation.ko.md)은 요구사항, 설계, 테스트, 서술형 답을 정리한다. 이 문서는 `Solution`의 두 파일을 처음부터 끝까지 읽는다. 줄 번호는 모두 각 파일 기준이다. `InsertFront-and-InsertRear.cpp`(38줄)는 제출한 두 함수이고, `Test-Driver.cpp`(133줄)는 두 함수를 실행하기 위한 테스트용 드라이버이다.

| 파일 | 줄 | 부분 | 구분 |
|:-----|:-----|:-----|:-----|
| `InsertFront-and-InsertRear.cpp` | 1~10 | Doxygen 헤더 | 제출한 코드 밖의 주석 |
| `InsertFront-and-InsertRear.cpp` | 12~20 | `InsertFront` | 제출한 코드 |
| `InsertFront-and-InsertRear.cpp` | 22~38 | `InsertRear` | 제출한 코드 |
| `Test-Driver.cpp` | 1~19 | 헤더 주석, `#include`, 전방 선언 | 테스트용 드라이버 |
| `Test-Driver.cpp` | 21~36 | `ChainNode<T>` | 테스트용 드라이버 |
| `Test-Driver.cpp` | 38~96 | `CircularList<T>` (68번 줄에서 제출한 함수를 포함) | 테스트용 드라이버 |
| `Test-Driver.cpp` | 98~133 | `main` | 테스트용 드라이버 |

*표 1. 두 파일의 구성*

---

<br>

## 2. InsertFront

```cpp
void InsertFront(const T& item) {
    ChainNode<T>* newNode = new ChainNode<T>(item);

    // (1-1) The Link of newNode points out the original first node.
    newNode->link = head->link;

    // (1-2) The newNode will be a new first node.
    head->link = newNode;
}
```

13번 줄은 `item`을 데이터로 갖는 새 노드를 동적으로 할당한다. `ChainNode<T>`의 생성자는 링크를 `nullptr`로 두지만 곧바로 덮어쓰므로 그 값은 쓰이지 않는다. 16번 줄은 새 노드의 링크에 헤드 노드의 링크, 곧 원래의 첫 노드 주소를 복사하고, 19번 줄은 헤드 노드의 링크를 새 노드로 바꾼다. 16번 줄이 먼저 원래의 첫 노드 주소를 새 노드에 옮겨 두므로 19번 줄이 `head->link`를 덮어써도 리스트를 잃지 않는다. 주석 (1-1)과 (1-2)는 안내문의 뼈대 코드에 있던 주석에서 배점만 뺀 것이다.

---

<br>

## 3. InsertRear

```cpp
void InsertRear(const T& item) {
    ChainNode<T>* newNode = new ChainNode<T>(item);

    // (2-1) The first node is stored at the *cur pointer.
    ChainNode<T>* cur = head->link;

    // (2-2) We will find the last node through the while loop, and the last node is stored at the *cur pointer.
    while (cur->link != head) {
        cur = cur->link;
    }

    // (2-3) The newNode will be inserted after the last node.
    cur->link = newNode;

    // (2-4) The last node should always point out the head node.
    newNode->link = head;
}
```

23번 줄이 새 노드를 할당한 뒤, 26번 줄은 `cur`를 첫 노드(`head->link`)로 초기화한다. 안내문의 뼈대 코드는 `ChainNode<T>* cur;`로 선언만 해 두었고, 제출한 코드는 선언과 (2-1)의 대입을 한 줄로 합쳤다. 29~31번 줄의 반복은 `cur`의 다음 노드가 헤드 노드가 아닌 동안 한 칸씩 나아가므로, 반복이 끝나면 `cur`는 링크가 헤드 노드인 노드, 곧 마지막 노드를 가리킨다. 빈 리스트에서는 `cur`가 헤드 노드 자신이고 반복은 실행되지 않는다. 34번 줄은 마지막 노드 뒤에 새 노드를 잇고, 37번 줄은 새 노드의 링크를 헤드 노드로 정하여 원을 닫는다.

---

<br>

## 4. 드라이버의 헤더와 ChainNode

`Test-Driver.cpp`의 1~14번 줄은 Doxygen 헤더이며, 테스트용으로 작성한 파일이라는 사실과 빌드 방법을 적는다. 16번 줄의 `<initializer_list>`는 `main`의 `for (int x : {1, 2, 3})`처럼 중괄호 목록을 범위 기반 for 문에 쓰기 위한 헤더이고, 17번 줄의 `<iostream>`은 입출력을 위한 헤더이다. 19번 줄은 `CircularList`의 전방 선언이다. 27번 줄의 `friend` 선언이 아직 정의되지 않은 `CircularList<T>`를 가리키기 때문에 필요하다.

```cpp
template <class T>
class ChainNode {
    friend class CircularList<T>;

public:
    ChainNode(const T& data = T(), ChainNode<T>* link = nullptr)
        : data(data), link(link) {}

private:
    T data;
    ChainNode<T>* link;
};
```

25~36번 줄의 `ChainNode<T>`는 3강 4.3절의 노드와 같은 두 필드를 갖는다. 필드는 `private`이고 `CircularList<T>`를 `friend`로 선언하였으므로, 리스트 클래스의 멤버 함수(제출한 두 함수 포함)만 `data`와 `link`에 접근할 수 있다. 생성자의 두 매개변수에 기본값이 있어 `new ChainNode<T>(item)`처럼 데이터만 주거나, 헤드 노드처럼 인자 없이 만들 수 있다.

---

<br>

## 5. 생성자와 소멸자

```cpp
CircularList() {
    head = new ChainNode<T>();
    head->link = head;              // empty list: the head node points to itself
}
```

49~52번 줄의 생성자는 헤드 노드를 할당하고 그 링크가 자기 자신을 가리키게 하여 빈 리스트를 만든다([과제 해설](Assignment-Explanation.ko.md)의 그림 2).

```cpp
~CircularList() {
    ChainNode<T>* del = head->link; // node to delete
    while (del != head) {
        head->link = del->link;     // the next node becomes the first node
        std::cout << "Node<" << del->data << "> is deleted\n";
        delete del;
        del = head->link;
    }
    delete head;
    std::cout << "\nDestructor is executed successfully!\n" << std::endl;
}
```

55~65번 줄의 소멸자는 3강 6.4절의 소멸자에 삭제 메시지 출력과 헤드 노드 해제를 더한 것이다. `del`이 첫 노드를 가리키게 한 뒤, 헤드 노드의 링크를 `del`의 다음 노드로 옮기고 `del`을 삭제하는 일을 `del`이 헤드 노드가 될 때까지 반복한다. 노드를 삭제하기 전에 다음 노드를 `head->link`에 옮겨 두므로 해제한 노드의 링크를 읽지 않는다. 데이터 노드가 모두 지워지면 헤드 노드의 링크가 자기 자신이 되어 반복이 끝나고, 63번 줄이 헤드 노드를 해제한다. 삭제는 첫 노드부터 차례로 일어나므로 출력 순서가 리스트의 순서와 같다.

---

<br>

## 6. 제출한 함수의 포함과 Print

67~68번 줄은 클래스 정의 안에서 `InsertFront-and-InsertRear.cpp`를 `#include`한다. 전처리기는 이 줄을 파일의 내용으로 바꾸므로, 제출한 두 함수는 클래스 안에서 정의한 멤버 함수가 되고 함수 안의 `T`, `ChainNode<T>`, `head`는 각각 클래스 템플릿의 매개변수, 노드 클래스, 멤버 변수를 가리킨다. 이 방법으로 제출한 코드를 한 글자도 고치지 않고 컴파일한다. 대신 `InsertFront-and-InsertRear.cpp`는 혼자서는 컴파일되지 않으며, `Test-Driver.cpp`만 컴파일한다.

```cpp
void Print() const {
    for (ChainNode<T>* cur = head->link; cur != head; cur = cur->link) {
        std::cout << cur->data;
        if (cur->link != head) std::cout << "->";
    }
    std::cout << '\n';
}
```

71~77번 줄의 `Print`는 첫 노드부터 헤드 노드로 돌아오기 직전까지 순회하며 데이터를 출력한다. 다음 노드가 헤드 노드가 아닐 때만 `->`를 붙이므로 마지막 원소 뒤에는 화살표가 없다. 빈 리스트에서는 반복이 실행되지 않고 빈 줄만 출력한다. 반복의 종료 조건이 `NULL`이 아니라 `head`와의 비교라는 점이 원형 리스트의 순회 방식이다.

---

<br>

## 7. Search

```cpp
int Search(const T& x) const {
    ChainNode<T>* cur = head->link;
    int index = 1;                  // position of cur
    head->data = x;                 // the loop stops at the head node at the latest
    while (cur->data != x) {
        cur = cur->link;
        index++;
    }
    return (cur == head) ? 0 : index;
}
```

83~92번 줄의 `Search`는 3강 6.6절의 `CircularList<T>::Search`와 같은 감시값 검색이다. 86번 줄이 찾는 값을 헤드 노드의 `data`에 넣어 두므로, 값이 리스트에 없어도 반복은 늦어도 헤드 노드에서 멈춘다. 그래서 반복마다 `cur->data != x` 하나만 검사한다. 멈춘 곳이 헤드 노드이면 값이 없다는 뜻이므로 0을, 아니면 1부터 센 위치를 돌려준다. 함수가 `const`인데도 86번 줄이 허용되는 것은, `const` 멤버 함수에서 상수가 되는 것은 포인터 `head` 자체이고 그것이 가리키는 헤드 노드는 아니기 때문이다.

---

<br>

## 8. main

99번 줄에서 지역 변수 `list`를 만들면 생성자가 빈 리스트를 준비한다. 101\~106번 줄은 `InsertFront`로 1, 2, 3을, 108\~113번 줄은 `InsertRear`로 2, 4, 6을 삽입하며 매번 리스트를 출력하고, 115\~117번 줄은 완성된 리스트를 다시 출력한다. 각 출력 뒤의 줄바꿈 수는 제출한 실행 화면의 빈 줄 수와 같게 맞추었다. 119\~124번 줄은 검색할 값을 입력받으며, 정수가 아닌 입력이면 메시지를 출력하고 1을 반환한다. 126\~130번 줄은 `Search`의 결과가 0이 아니면 위치를, 0이면 값이 없다는 메시지를 출력한다. 132번 줄에서 `main`이 끝나면 `list`의 소멸자가 실행되어 노드 삭제 메시지와 완료 메시지를 출력한다.

---

<br>

## 9. 실행 추적

[과제 해설](Assignment-Explanation.ko.md) 4.1절의 실행(검색할 값 2)을 단계별로 추적하면 다음과 같다.

| 단계 | 호출 | 호출 뒤의 리스트 또는 결과 | `InsertRear`의 반복 횟수 |
|:-----|:-----|:-----|-----:|
| 1 | `InsertFront(1)` | `1` | - |
| 2 | `InsertFront(2)` | `2->1` | - |
| 3 | `InsertFront(3)` | `3->2->1` | - |
| 4 | `InsertRear(2)` | `3->2->1->2` | 2 |
| 5 | `InsertRear(4)` | `3->2->1->2->4` | 3 |
| 6 | `InsertRear(6)` | `3->2->1->2->4->6` | 4 |
| 7 | `Search(2)` | 노드 3, 2와 비교하고 2에서 멈추어 위치 2 | - |
| 8 | 소멸자 | 3, 2, 1, 2, 4, 6의 순서로 삭제한 뒤 헤드 노드 해제 | - |

*표 2. 2를 검색하는 실행의 단계별 상태*

9를 검색하면 7단계에서 데이터 노드 6개와 모두 다르므로 `cur`가 헤드 노드까지 가서 감시값과 같아지고, `Search`는 0을 돌려준다.

---

<br>

## 10. 복잡도

데이터 노드의 수를 $n$이라 하면 각 함수의 시간 복잡도는 다음과 같다.

| 함수 | 시간 복잡도 | 근거 |
|:-----|:-----|:-----|
| `InsertFront` | $O(1)$ | 링크 두 개만 바꾼다 |
| `InsertRear` | $O(n)$ | 마지막 노드를 찾기 위해 $n - 1$번 이동한다 |
| `Print` | $O(n)$ | 데이터 노드를 한 번씩 방문한다 |
| `Search` | $O(n)$ | 값이 없으면 데이터 노드 $n$개와 헤드 노드까지 $n + 1$번 비교한다 |
| 소멸자 | $O(n)$ | 데이터 노드를 한 번씩 해제한다 |

*표 3. 각 함수의 시간 복잡도*

---

<br>

## 요약

| 개념 | 핵심 요약 |
|:-----|:-----|
| 파일 구성 | `InsertFront-and-InsertRear.cpp`는 제출한 두 함수이고, `Test-Driver.cpp`는 이를 실행하기 위해 작성한 테스트용 드라이버이다. |
| `InsertFront` | 원래의 첫 노드 주소를 새 노드에 먼저 옮긴 뒤 헤드 노드의 링크를 새 노드로 바꾼다. |
| `InsertRear` | `cur`를 첫 노드에서 출발시켜 링크가 헤드 노드인 노드까지 옮기고, 그 뒤에 새 노드를 이어 원을 닫는다. |
| 클래스 안의 `#include` | 제출한 함수의 본문을 클래스 정의에 그대로 붙여 넣어 고치지 않고 멤버 함수로 컴파일한다. |
| 생성자와 소멸자 | 생성자는 자기 자신을 가리키는 헤드 노드를 만들고, 소멸자는 첫 노드부터 차례로 삭제한 뒤 헤드 노드를 해제한다. |
| `Search` | 헤드 노드에 찾는 값을 넣는 감시값 검색으로, 위치를 1부터 세고 찾지 못하면 0을 돌려준다. |

---

<br>

## 점검 문제

1. **생성자 매개변수의 기본값:** `ChainNode<T>`의 생성자에서 `data`의 기본값 `T()`가 없으면 드라이버의 어느 줄이 컴파일되지 않는가?

   <details>
   <summary>정답</summary>

   생성자의 50번 줄 `head = new ChainNode<T>();`이다. 헤드 노드는 데이터 없이 만들어야 하는데, 기본값이 없으면 인자 없이 호출할 수 있는 생성자가 없다. `new ChainNode<T>(item)`처럼 인자를 주는 제출한 함수의 줄은 그대로 컴파일된다.

   </details>

2. **소멸자의 순서:** 소멸자의 반복에서 `delete del;`을 `head->link = del->link;`보다 먼저 실행하면 어떤 문제가 생기는가?

   <details>
   <summary>정답</summary>

   이미 해제한 노드의 `link`를 읽게 된다(해제 후 사용). 정의되지 않은 동작이므로 다음 노드 주소가 깨져 일부 노드가 해제되지 않거나 프로그램이 비정상 종료될 수 있다. 다음 노드를 먼저 `head->link`에 옮겨 두어야 한다.

   </details>

3. **Print의 화살표:** `Print`가 `if (cur->link != head)` 검사 없이 매번 `->`를 출력하면 출력은 어떻게 바뀌는가?

   <details>
   <summary>정답</summary>

   마지막 원소 뒤에도 화살표가 붙어 `3->2->1->`처럼 출력된다. 마지막 노드의 다음이 헤드 노드라는 원형 구조의 성질을 이용해 마지막 원소에서만 화살표를 생략한다.

   </details>

4. **감시값 없이 검색하기:** 86번 줄을 지우면 `Search`는 리스트에 있는 값과 없는 값에 대해 각각 어떻게 동작하는가?

   <details>
   <summary>정답</summary>

   리스트에 있는 값은 그 노드에서 멈추므로 결과가 같다. 리스트에 없는 값은 헤드 노드의 `data`(생성자가 넣은 `T()`, 곧 0)와도 다르면 반복이 헤드 노드를 지나 계속 돌아 끝나지 않는다. 찾는 값이 0이면 헤드 노드에서 멈추어 0을 돌려주므로 우연히 올바르다. 감시값이 없으면 `cur != head` 검사를 반복 조건에 더해야 한다.

   </details>
