#idef, #ifdef, #endif use
Their purpose is to prevent a header file from being included more than once within the same single .cpp file.
This problem happens indirectly, not directly like in your example.

  => The Problem They Solve (Diamond Dependency)

Imagine this file structure:
- main.cpp includes student.h and course.h.
- Both student.h and course.h need to include a base file, school_defs.h.
Without include guards, the text of school_defs.h would be copy-pasted into main.cpp twice, causing a redefinition error.
  
school_defs.h (WITH guards): 
#ifndef SCHOOL_DEFS_H // "if SCHOOL_DEFS_H is not defined..."
#define SCHOOL_DEFS_H // "...then define it..."

struct SchoolID { int id; };

#endif // "...end of conditional block."

How it works:
1. When main.cpp includes student.h, it pulls in school_defs.h for the first time.
2. SCHOOL_DEFS_H is not defined, so the code is included and SCHOOL_DEFS_H is now defined.
3. Later, when main.cpp includes course.h, it tries to pull in school_defs.h for the second time.
4. This time, SCHOOL_DEFS_H is defined, so the preprocessor skips everything until #endif.
In short: They ensure that even if you #include a header 10 times through different paths, its content only gets pasted into the final .cpp file once.


 
Question: What happens if I include a header file that has include guards (#pragma once or #ifndef...) multiple times in the same .cpp file?
Answer:
Nothing bad happens; your code will compile correctly. The include guards ensure the header's content is processed only once. The first #include works, 
and all subsequent ones in that file are ignored.

Question: What happens if I include a header file that does not have include guards multiple times in the same .cpp file?
Answer:
You will get a "redefinition" compiler error. Without guards, the preprocessor copy-pastes the header's contents every time it is included, causing 
the compiler to see duplicate definitions of the same classes or structs.



=> What is #pragma once?
 - It's a modern, simpler alternative to #ifndef guards.
 - Both do the exact same thing: prevent a header from being included more than once in the same .cpp file.
  
#pragma once
- Pros: One line, cleaner, and no risk of typos.
- Cons: Not officially part of the C++ standard, but supported by virtually all modern compilers.

#ifndef guards
- Pros: The traditional, standard-guaranteed way to do it.
- Cons: More typing and you must ensure the guard name (SUMIT_H) is unique.

You only need one of them, and #pragma once is generally preferred today for its simplicity.

=> What is pragma?
- #pragma is a generic command to give special instructions directly to the compiler. These instructions are not part of the C++ language itself.
- Think of it as a way to tell the compiler: "Hey, do this specific, non-standard thing for me." #pragma once is just one of many such commands.
