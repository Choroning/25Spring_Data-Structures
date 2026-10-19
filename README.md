# [Spring 2025] Data Structures

![Last Commit](https://img.shields.io/github/last-commit/Choroning/25Spring_Data-Structures)
![Languages](https://img.shields.io/github/languages/top/Choroning/25Spring_Data-Structures)

This repository archives bilingual lecture notes and coursework for the Data Structures course.

*Author: Cheolwon Park (Korea University Sejong, CSE) - Year 2 (Sophomore) as of 2025*
<br><br>

## 📑 Table of Contents

- [About This Repository](#about-this-repository)
- [Course Information](#course-information)
- [Prerequisites](#prerequisites)
- [Repository Structure](#repository-structure)
- [License](#license)

---


<br><a name="about-this-repository"></a>
## 📝 About This Repository

This repository contains the lecture notes, exercises, and C++ code of a university-level Data Structures course that covers fundamental data structures with an emphasis on performance analysis and time complexity.

- `Lecture-Notes/` holds, for each unit, lecture notes with comprehensive explanations of data structures and algorithms (`Concepts_Lecture`), exercises with review questions (`Exercises`), and their solutions (`Solutions`). The units follow the numbers of the instructor's slides (L1-L10) and are numbered `Lec01`-`Lec10`.
- Every lecture note, exercise set, and solution set comes as an English file (`.md`) and a Korean file (`.ko.md`) with the same structure.
- `Coursework/` holds C++ lab code (`Lab01`-`Lab10`) that organizes the lecture demonstration code by unit, two programming homework assignments (`HW01` and `HW02`), and two term projects.
- The improved C++ code files carry **Doxygen-style headers** that document their purpose, usage, and structure.
- The two **term projects** (Database Index Engine and Huffman Coding) were designed with reference to the curricula of leading overseas CS universities. Their features, build instructions, and complexity are described in the `README.md` of each project folder.
- All lab, homework, and project code was built and run with a C++17 compiler.

> **🤖 AI Agent Usage**
> [Claude Code](https://claude.ai/download) was used to organize and translate the lecture notes, write the homework explanations, and restructure the repository, and it also wrote the test drivers (`Test-Driver.cpp`) for the homework.

<br><a name="course-information"></a>
## 📚 Course Information

- **Semester:** Spring 2025 (March - June)
- **Affiliation:** Korea University Sejong

| Course&nbsp;Code| Course            | Type          | Instructor      | Department                              |
|:----------:|:------------------|:-------------:|:---------------:|:----------------------------------------|
|`DCCS201-02`|DATA STRUCTURES|Major Required|Prof. Minho&nbsp;Jo|Department of Computer Science and Software Engineering|

### Course Overview

A required major course, taught in English, on data structures and the algorithms that manipulate them. Following the instructor's slides (L1-L10), it first covers program performance analysis and time complexity theory and then fundamental data structures such as arrays, linked lists, matrices, stacks, queues, skip lists, hashing, trees, heaps, leftist trees, and binary search trees, with an emphasis on performance analysis and time complexity. The syllabus states that the course also introduces some basic graph and discrete transform algorithms and basic principles of software engineering such as good programming practice for "long-life" software. The instructor and teaching assistant, schedule and class format, assessment, course policies, weekly plan and progress, and references are in the [course information document](Course-Information.md).

<br><a name="prerequisites"></a>
## ✅ Prerequisites

- Programming language skills such as Python, Java, or C/C++ are required.
- Familiarity with basic algorithm concepts such as time complexity and Big-O notation is required.
- A Python, Java, or C/C++ development environment must be installed. Building the code in this repository requires a compiler that supports C++17.

- **💻 Development Environment**

| Tool | Company |  OS  | Notes |
|:-----|:-------:|:----:|:------|
|Xcode|Apple Inc.|macOS|Most used IDE|
|Visual Studio Code|Microsoft|macOS|    |

<br><a name="repository-structure"></a>
## 🗂 Repository Structure

```plaintext
25Spring_Data-Structures
├── Lecture-Notes               Lecture notes, exercises, and solutions by lecture
├── Coursework                  C++ lab code by lecture, homework, and term projects
├── images                      Figures for the homework explanations
├── Course-Information.ko.md    Course operations
├── Course-Information.md
├── LICENSE                     Documentation license (CC BY-NC-SA 4.0)
├── LICENSE-CODE                Code license (PolyForm Noncommercial 1.0.0)
├── README.ko.md
└── README.md
```

The units are listed in the [`Lecture-Notes` index](Lecture-Notes/README.md), and the lab code, homework, and term projects in the [`Coursework` index](Coursework/README.md).

<br><a name="license"></a>
## 🤝 License

The documents in this repository (lecture notes, explanations, and summary sheets) are licensed under [CC BY-NC-SA 4.0](LICENSE), and the code under [PolyForm Noncommercial 1.0.0](LICENSE-CODE). Figures and example code taken from lecture slides and textbooks, as well as assignment handouts and template code distributed by the course, belong to their original authors and are not covered by these licenses.

---
