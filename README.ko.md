# [2025학년도 봄학기] 자료구조

![Last Commit](https://img.shields.io/github/last-commit/Choroning/25Spring_Data-Structures)
![Languages](https://img.shields.io/github/languages/top/Choroning/25Spring_Data-Structures)

이 레포지토리는 대학 강의 및 과제를 위해 작성된 자료구조 구현 코드를 체계적으로 정리하고 보관합니다.

*작성자: 박철원 (고려대학교(세종), 컴퓨터융합소프트웨어학과) - 2025년 기준 2학년*
<br><br>

## 📑 목차

- [레포지토리 소개](#about-this-repository)
- [강의 정보](#course-information)
- [사전 요구사항](#prerequisites)
- [레포지토리 구조](#repository-structure)
- [라이선스](#license)

---


<br><a name="about-this-repository"></a>
## 📝 레포지토리 소개

이 레포지토리에는 대학 수준의 자료구조 과목을 위해 작성된 코드가 포함되어 있습니다:

- 각 챕터별 자료구조 및 알고리즘을 종합적으로 정리한 **Concepts.md** 파일
- 각 챕터별 복습 문제 및 풀이를 담은 **Quiz.md** 파일
- 목적, 사용법, 구조를 문서화한 **Doxygen 스타일 헤더**가 포함된 개선된 C++ 코드 파일
- 강의 시연 코드 및 과제 솔루션
- 해외 CS 명문 대학 커리큘럼을 참고하여 설계한 2개의 **텀 프로젝트** (Database Index Engine, Huffman Coding)

본 과목은 배열, 연결 리스트, 스택, 큐, 스킵 리스트, 해싱, 트리, 힙, 이진 탐색 트리 등 핵심 자료구조를 다루며, 성능 분석과 시간 복잡도에 중점을 둡니다.

<br><a name="course-information"></a>
## 📚 강의 정보

- **학기:** 2025학년도 봄학기 (3월 - 6월)
- **소속:** 고려대학교(세종)

|학수번호      |강의명    |이수구분|교수자|개설학과|
|:----------:|:-------|:----:|:------:|:----------------|
|`DCCS201-02`|자료구조|전공필수|조민호 교수|컴퓨터융합소프트웨어학과|

- **📖 참고 자료**

| 유형 | 내용 |
|:----:|:---------|
|강의자료|교수자 제공 PPT 슬라이드 및 필기 노트|
|참고도서|"Data Structures and Abstractions with Java, 4th Edition" by F.M. Carrano and T.M. Henry (Pearson)|

<br><a name="prerequisites"></a>
## ✅ 사전 요구사항

- 프로그래밍 언어 능력 (Python, Java, 또는 C/C++)
- 기본적인 알고리즘 개념 숙지 (시간 복잡도, Big-O 표기법)
- Python, Java, 또는 C/C++ 개발 환경 설치

- **💻 개발 환경**

| 도구 | 회사 |  운영체제  | 비고 |
|:-----|:-------:|:----:|:------|
|Xcode|Apple Inc.|macOS|주 사용 IDE|
|Visual Studio Code|Microsoft|macOS|    |

<br><a name="repository-structure"></a>
## 🗂 레포지토리 구조

```plaintext
25Spring_Data-Structures
├── Chapter01_Performance-Analysis
│   ├── Concepts.md
│   ├── PerformanceMeasurement.cpp
│   └── Quiz.md
├── Chapter02_Time-Complexity
│   ├── ComplexityExamples.cpp
│   ├── Concepts.md
│   └── Quiz.md
├── Chapter03_Arrays-and-Linked-Lists
│   ├── ArrayList.cpp
│   ├── Concepts.md
│   ├── LinkedList.cpp
│   └── Quiz.md
├── Chapter04_Matrices
│   ├── Concepts.md
│   ├── Quiz.md
│   └── SparseMatrix.cpp
├── Chapter05_Stacks
│   ├── ArrayStack.cpp
│   ├── Concepts.md
│   ├── LinkedStack.cpp
│   └── Quiz.md
├── Chapter06_Queues
│   ├── ArrayQueue.cpp
│   ├── Concepts.md
│   └── Quiz.md
├── Chapter07_Skip-Lists-and-Hashing
│   ├── Concepts.md
│   ├── HashTable.cpp
│   ├── Quiz.md
│   └── SkipList.cpp
├── Chapter08_Binary-Trees
│   ├── BinaryTree.cpp
│   ├── Concepts.md
│   └── Quiz.md
├── Chapter09_Priority-Queues-and-Heaps
│   ├── Concepts.md
│   ├── LeftistTree.cpp
│   ├── MaxHeap.cpp
│   └── Quiz.md
├── Chapter10_Binary-Search-Trees
│   ├── BinarySearchTree.cpp
│   ├── Concepts.md
│   └── Quiz.md
├── Project_Database-Index-Engine
│   ├── BPlusTree.cpp
│   ├── BPlusTree.h
│   ├── main.cpp
│   └── README.md
├── Project_Huffman-Coding
│   ├── BitStream.cpp
│   ├── BitStream.h
│   ├── HuffmanTree.cpp
│   ├── HuffmanTree.h
│   ├── main.cpp
│   ├── PriorityQueue.cpp
│   ├── PriorityQueue.h
│   └── README.md
├── LICENSE
├── README.ko.md
└── README.md

12개의 디렉토리, 48개의 파일
```

<br><a name="license"></a>
## 🤝 라이선스

이 레포지토리는 [Apache License 2.0](LICENSE) 하에 배포됩니다.

---
