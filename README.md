# Slice (C implementation)

A simple implementation of a dynamic array inspired by Go slices.

This project demonstrates how slices can be built in C using:
- raw memory allocation (`malloc`, `realloc`)
- pointer arithmetic
- generic storage (`void*`)
- manual memory management

It is **not production-ready**, but meant for learning and experimentation.

---

## Features

- dynamic resizing (`append`)
- slicing (`sub`)
- element access (`get`, `set`)
- copying (`copy`)
- manual memory control (`delete`)
- generic type support via `elem_size`
- basic error handling / logging system

---

## Core idea

Each slice is represented as:

```c
typedef struct {
    void *ptr;
    size_t len;
    size_t cap;
    size_t elem_size;
    bool is_owner;
} Slice;
```

---

### 🛠️ API Macros

#### 📦 Creation & Destruction
* `#define make(type, len, cap)` `slice_make(sizeof(type), len, cap)` — Create a slice.
* `#define delete(s)` `slice_free(&(s))` — Free a slice.

#### 📊 Metrics
* `#define len(s)` `slice_len(s)` — Get slice length.
* `#define cap(s)` `slice_cap(s)` — Get slice capacity.

#### 🔄 Access & Modification
* `#define get(s, index)` `slice_get(s, index)` — Get element by index.
* `#define set(s, index, elem)` `slice_set(s, index, &(elem))` — Set element value.
* `#define append(s, elem)` `slice_append(s, &(elem))` — Append element to end.

#### ✂️ Copy & Subsets
* `#define copy(dst, src)` `slice_copy(dst, src)` — Copy slice data.
* `#define sub(s, start, end)` `slice_sub(s, start, end)` — Create a sub-slice.

---

### 🚀 Build & Run

Run the example program using the following command:

```bash
make example-run
```