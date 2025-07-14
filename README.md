# Brief

A simple demonstration of a C++ Plugin-System for Windows using a pure-virtual Interface instanciated via C-Interface for better ABI compatibility and to avoid name-mangling.

```mermaid
graph LR
  subgraph User
    direction LR
    A[Pointer to Pure-Abstract C++ Interface Class]<-->B[C-Interface]
  end
  subgraph Plugin
    direction LR
    C[C-Interface]<-->D[Implementation of Pure-Abstract C++ Interface Class]
  end
  B <--> C
```

# Reference

This small sample project is based on [this](https://cplusplus.com/articles/48TbqMoL/) article.
