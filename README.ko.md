# [2025학년도 봄학기] 자료구조

![Last Commit](https://img.shields.io/github/last-commit/Choroning/25Spring_Data-Structures)
![Languages](https://img.shields.io/github/languages/top/Choroning/25Spring_Data-Structures)

이 레포지토리는 자료구조 과목의 이중 언어 강의 노트와 수업 결과물을 정리한 아카이브입니다.

*작성자: 박철원 (고려대학교(세종), 컴퓨터소프트웨어학과) - 2025년 기준 2학년*
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

이 레포지토리에는 성능 분석과 시간 복잡도를 중심으로 핵심 자료구조를 다루는 대학 수준의 자료구조 과목의 강의 노트, 연습 문제, C++ 코드가 담겨 있습니다.

- `Lecture-Notes/`에는 단원마다 자료구조와 알고리즘을 종합적으로 정리한 강의 노트(`Concepts_Lecture`), 복습 문제를 모은 연습 문제(`Exercises`), 그 풀이(`Solutions`)가 있습니다. 교수자가 제공한 슬라이드의 번호(L1\~L10)를 따라 단원을 `Lec01`\~`Lec10`으로 나눴습니다.
- 모든 강의 노트, 연습 문제, 풀이는 영어 파일(`.md`)과 한국어 파일(`.ko.md`)이 같은 구성으로 짝을 이룹니다.
- `Coursework/`에는 강의 시연 코드를 단원마다 정리한 C++ 실습 코드(`Lab01`\~`Lab10`), 두 프로그래밍 과제(`HW01`, `HW02`), 2개의 텀 프로젝트가 있습니다.
- 개선된 C++ 코드 파일에는 목적, 사용법, 구조를 문서화한 **Doxygen 스타일 헤더**가 있습니다.
- 2개의 **텀 프로젝트**(Database Index Engine, Huffman Coding)는 해외 CS 명문 대학의 커리큘럼을 참고하여 설계했습니다. 기능, 빌드 방법, 복잡도는 각 프로젝트 폴더의 `README.md`에 정리되어 있습니다.
- 모든 실습, 과제, 프로젝트 코드는 C++17 컴파일러로 빌드하고 실행하여 확인했습니다.

> **🤖 AI 에이전트 활용**
> 강의 노트의 정리와 번역, 과제 해설 작성, 레포지토리 구조 정리에 [Claude Code](https://claude.ai/download)를 활용했으며, 과제의 테스트용 드라이버(`Test-Driver.cpp`)도 Claude Code로 작성했습니다.

<br><a name="course-information"></a>
## 📚 강의 정보

- **학기:** 2025학년도 봄학기 (3월 - 6월)
- **소속:** 고려대학교(세종)

|학수번호      |강의명    |이수구분|교수자|개설학과|
|:----------:|:-------|:----:|:------:|:----------------|
|`DCCS201-02`|자료구조|전공필수|조민호 교수|컴퓨터소프트웨어학과|

### 과목 개요

자료구조와 자료구조를 다루는 알고리즘을 공부하는 전공필수 과목으로, 영어로 진행된다. 교수자가 제공한 슬라이드(L1~L10)를 따라 프로그램의 성능 분석과 시간 복잡도 이론을 먼저 배운 뒤 배열, 연결 리스트, 행렬, 스택, 큐, 스킵 리스트, 해싱, 트리, 힙, 좌편향 트리, 이진 탐색 트리 등 핵심 자료구조를 다루며, 성능 분석과 시간 복잡도에 중점을 둔다. 강의계획서는 이와 함께 기초적인 그래프 알고리즘과 이산 변환 알고리즘, "long-life" 소프트웨어를 위한 좋은 프로그래밍 습관 같은 소프트웨어 공학의 기본 원리도 소개한다고 밝혔다. 교수자와 조교, 수업 일정과 형식, 평가, 수업 운영 규정, 주차별 계획 및 진도, 참고 자료는 [강의 정보 문서](Course-Information.ko.md)에 정리했다.

<br><a name="prerequisites"></a>
## ✅ 사전 요구사항

- Python, Java, C/C++ 같은 프로그래밍 언어를 다룰 수 있어야 합니다.
- 시간 복잡도와 Big-O 표기법 같은 기본적인 알고리즘 개념을 알고 있어야 합니다.
- Python, Java, C/C++ 중 하나의 개발 환경이 설치되어 있어야 합니다. 이 레포지토리의 코드를 빌드하려면 C++17을 지원하는 컴파일러가 필요합니다.

- **💻 개발 환경**

| 도구 | 회사 |  운영체제  | 비고 |
|:-----|:-------:|:----:|:------|
|Xcode|Apple Inc.|macOS|가장 많이 사용한 IDE|
|Visual Studio Code|Microsoft|macOS|    |

<br><a name="repository-structure"></a>
## 🗂 레포지토리 구조

```plaintext
25Spring_Data-Structures
├── Lecture-Notes               강의별 강의 노트, 연습 문제, 풀이
├── Coursework                  강의별 C++ 실습 코드, 과제, 텀 프로젝트
├── images                      과제 해설의 그림
├── Course-Information.ko.md    수업 운영 정보
├── Course-Information.md
├── LICENSE                     문서 라이선스 (CC BY-NC-SA 4.0)
├── LICENSE-CODE                코드 라이선스 (PolyForm Noncommercial 1.0.0)
├── README.ko.md
└── README.md
```

단원 목록은 [`Lecture-Notes` 색인](Lecture-Notes/README.ko.md)에, 실습 코드, 과제, 텀 프로젝트는 [`Coursework` 색인](Coursework/README.ko.md)에 있습니다.

<br><a name="license"></a>
## 🤝 라이선스

이 레포지토리의 문서(강의 노트, 해설, 요약지)는 [CC BY-NC-SA 4.0](LICENSE), 코드는 [PolyForm Noncommercial 1.0.0](LICENSE-CODE)에 따라 배포됩니다. 강의자료와 교재에서 가져온 그림과 예제 코드, 강의가 배포한 과제 원본과 템플릿 코드는 원저작자에게 권리가 있으며 이 라이선스의 대상이 아닙니다.

---
