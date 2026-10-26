# Course Information

[Repository Guide](README.md) | [English](Course-Information.md) | [한국어](Course-Information.ko.md)

> **Last Updated:** 2026-10-26

## Table of Contents

- [1. Instructor, Teaching Assistant, and Research Lab](#1-instructor-teaching-assistant-and-research-lab)
- [2. Schedule and Class Format](#2-schedule-and-class-format)
- [3. Assessment](#3-assessment)
- [4. Course Policies](#4-course-policies)
- [5. Weekly Plan and Progress](#5-weekly-plan-and-progress)
- [6. References](#6-references)

---

<br>

## 1. Instructor, Teaching Assistant, and Research Lab

- **Instructor:** Prof. Minho Jo, Department of Computer Science and Software Engineering
- **Research Lab:** IoT & AI Lab
- **Office Hours:** Monday 16:00 ~ 18:00, Wednesday 15:00 ~ 16:00, Thursday 14:00 ~ 15:00
- **Teaching Assistant:** Kyungmin Lim (임경민), who prepared the explanation material for Programming Homework #2.

---

<br>

## 2. Schedule and Class Format

- **Credits (Hours):** 3 (3)
- **Intended For:** Second-, third-, and fourth-year students
- **Language of Instruction:** English. The course name in the syllabus is "Data Structures (SEMO Class, 영강. Taught in English)".
- **Class Times:** Monday 10:00 ~ 10:50 and 11:00 ~ 11:50, Wednesday 10:00 ~ 10:50
- **Classroom:** Room 7-310 (Mon)
- **Class Format:** Lectures, practice, and Q&A, with lectures and homework as the key teaching methods of the course.
  - In the classes on concepts and theories, students study the theoretical content of data structures and algorithms.
  - In the homework assignments, students solve practical problems and program their own solutions in their own programming language, such as C/C++, Java, or Python.
- **Attendance:** Attendance is checked in every class hour.
- **Exam Supervision:** Exams are not held unsupervised.
- **Class Description:** The course focuses on data structures and the algorithms for manipulating them. It covers data structures for storing information in tables, lists, trees, queues, and stacks, and data structures are crucial for software programming. Some basic graph and discrete transform algorithms are also taught, and basic principles of software engineering, such as good programming practice for "long-life" software, are introduced.
- **Study Objectives:**
  1. Understanding the time and space complexity of data structures and algorithms.
  2. Understanding the concepts of data structures and algorithms.
  3. Being exposed to current cutting-edge data structures.
  4. Learning important and popular data structures and algorithms.
  5. Learning how to design data structures for problem solving.
- **Course and Departmental Objectives:** The core competence of the course is understanding how to design data structures and how to apply the algorithms that manipulate them. One of the departmental objectives is to make students ready to develop software on their own and with their own creativity, and the key objective of the course is to teach and train students who are confident in designing data structures that store and retrieve data efficiently in space and time for their software.
- **Core Competencies:** The syllabus marks Frontier Spirit and Pragmatic Practice as very highly correlated and Creative Convergence and Global Leadership as highly correlated.
- **Major Competencies:** Of the department's major competencies (Ethics & Leadership, Think & Technology, Network & Application), the course corresponds to Think & Technology and Network & Application.
- **Prerequisites:** Programming language skills such as Python, Java, or C/C++ are required.

---

<br>

## 3. Assessment

| Item | Weight |
|:-----|-----:|
| Quizzes | 60% |
| Online Discussion (Online Q&A) | 10% |
| Offline Discussion (Off-line Q&A) | 5% |
| Attendance | 5% |
| Programming Homework | 20% |

- Grading is absolute, and feedback on the evaluation is provided.
- The syllabus states that homework is given after each chapter is finished. Homework is important for understanding the course content completely.
- A quiz was given on the LMS for each chapter, titled from "Quiz for Chapter 1" to "Quiz for Chapter 10".
- **Programming Homework #1:** Program operations of a Circular Linked List with Head Node. The solution and explanation are in [`HW01_Circular-Linked-List-with-Head-Node`](Coursework/HW01_Circular-Linked-List-with-Head-Node/).
  - `InsertFront` operation (20 points): make the link of the new node point to the original first node (10 points) and make the new node the new first node (10 points).
  - `InsertRear` operation (50 points): store the first node in the `cur` pointer (10 points), find the last node with a while loop and store it in `cur` (20 points), insert the new node after the last node (10 points), and make the last node always point to the head node (10 points).
  - Run the program with the completed code and capture screenshots of the results (20 points).
  - Answer questions about the head node (10 points): (1) the advantages of using a head node for a circular linked list and (2) the difference between putting the head node at the front and putting it at the rear.
- **Programming Homework #2:** Program the push and pop operations of a linked queue (Linked Queue Pop and Push Operation). The solution and explanation are in [`HW02_Linked-Queue-Push-and-Pop`](Coursework/HW02_Linked-Queue-Push-and-Pop/).
  - `push` operation of the `Queue` class (30 points): implement push for type 1 (20 points) and type 2 (10 points).
  - `pop` operation (50 points): implement pop for type 1 (20 points) and type 2 (30 points).
  - Run the program with the completed code and capture screenshots of the results (20 points).
  - The teaching assistant distributed material that illustrates the two representations of a linked queue (type 1 and type 2) and their push and pop procedures (Linked Queue: pushing and popping operation).

---

<br>

## 4. Course Policies

- All homework and other information is announced on the Blackboard bulletin board (BBS) of the university portal system, and homework submissions must be uploaded to the Blackboard assignment menu by the deadlines.
- Participation is important, so students are advised not to be absent from class.
- **Support for Students with Disabilities:** Students with disabilities who have any difficulty attending class may ask the instructor for assistance at any time.
- **Learning Ethics:** Students have the following general obligations in all processes of completing the curriculum, including attending lectures, preparing and submitting assignments, and taking exams.
  1. Participate actively in all learning with honesty and a passionate attitude based on the purpose and educational philosophy of the university.
  2. Be aware of their position as students receiving higher education and devote themselves to creative learning based on moral sensitivity.
  3. Faithfully carry out what they have promised faculty members or fellow students in connection with educational activities.
  4. Respect the character of faculty members and other students and observe basic manners.
- Credits found to have been obtained through dishonest behavior such as plagiarism, duplicate use of assignments from other classes, or exam misconduct, or through any other unfair method, are canceled even after they have been granted, and disciplinary action such as suspension, withdrawal, or expulsion may follow, taking the circumstances of the act into account.
- The university operates a plagiarism detection system (Blackboard) to raise awareness of learning ethics and encourage creativity, and students must check in advance whether their work counts as plagiarism when submitting assignments.

---

<br>

## 5. Weekly Plan and Progress

| Week | Class Dates (Mon, Wed) | Planned Topic | Lecture Decks Covered |
|:-----|:-----|:-----|:-----|
| W01 | 3/3, 3/5 | Introduction and program performance measurement | - |
| W02 | 3/10, 3/12 | Program Performance measurement | L1 Program Performance Analysis and Measurement<br>L2 Time Complexity Theory for Performance Measurement |
| W03 | 3/17, 3/19 | Time complexity theory | - |
| W04 | 3/24, 3/26 | Array-based linear list and linked-based linear list | L3 Array and Link |
| W05 | 3/31, 4/2 | Array and matrices | L4 Arrays and Matrices |
| W06 | 4/7, 4/9 | Stacks | L5 Stacks |
| W07 | 4/14, 4/16 | Queues | L6 Queues |
| W08 | 4/21, 4/23 | Mid-term Exam | No class |
| W09 | 4/28, 4/30 | Skip lists and hashing | - |
| W10 | 5/5, 5/7 | Binary and other trees | No class, replaced by homework<br>Programming Homework #1 |
| W11 | 5/12, 5/14 | Priority queues, heap, leftist trees | No class, replaced by homework<br>Programming Homework #2 |
| W12 | 5/19, 5/21 | Priority queues, heap, leftist trees | L7 Skip List and Hashing |
| W13 | 5/26, 5/28 | Tournament trees and bin packing | L8 Binary and Other Trees |
| W14 | 6/2, 6/4 | Binary search trees | L9 Priority Queues, Heaps, Leftist Trees |
| W15 | 6/9, 6/11 | Binary search trees | L10 Binary Search Trees<br>End of term |
| W16 | 6/16, 6/18 | Final Exam | - |

- The planned topics follow the weekly schedule of the syllabus, which planned PPT slides as the material for every week except the exam weeks.
- L2 Time Complexity Theory for Performance Measurement was covered over weeks 2 and 3.
- There was no class in week 8, the classes in weeks 10 and 11 were replaced by homework, and the term ended in week 15. The assessment items include no exams.
- The actual progress followed the plan through week 7, and from L7 on it ran three weeks behind the plan, starting in week 12. No lecture deck covers Tournament trees and bin packing, which was planned for week 13.
- The deck numbers L1-L10 and the numbers in the LMS quiz titles "Quiz for Chapter N" correspond to `Lec01`-`Lec10` in this repository. The units are listed in the [`Lecture-Notes` index](Lecture-Notes/README.md).

---

<br>

## 6. References

| Type | Contents |
|:-----|:-----|
| Lecture Slides | PPT slides (L1-L10) and handwritten notes provided by the instructor. L1-L5 also come with annotated copies, and L1-L3 with translated copies. |
| Lecture Videos | Lecture videos for L1-L10. The videos for L1 and L9 are split into two parts. |
| Reference | F. M. Carrano and T. M. Henry, *Data Structures and Abstractions with Java*, 4th ed. Boston, MA, USA: Pearson, 2015. |

- According to the syllabus, no textbook is required and the instructor provides lecture notes in PPTs, with the book by Carrano and Henry above as the reference textbook.
