# STL Remakes

A lightweight playground for exploring how pieces of the C++ Standard Library and C
Runtime (CRT) can be rebuilt from scratch. The project provides header-only
implementations of common containers, utilities, and threading primitives that
avoid the system CRT/STL while keeping the APIs familiar for experimentation and
learning.

## Project Highlights

- Self-contained reimplementations of high-impact STL headers such as
  `std::string`, `std::vector`, `std::optional`, `std::thread`, and more.
- A minimal CRT layer that supplies the basic allocation and runtime hooks needed
  by the custom containers and utilities.
- Sample `main.cpp` that exercises each component through simple feature toggles,
  making it easy to verify behaviour or benchmark alternatives.

## Status Overview

| Area | Status | Notes |
| --- | --- | --- |
| CRT support shim (`crt_remakes/`) | ✅ Implemented | Header-only interface that exposes allocation helpers shared by the STL remakes. |
| Core containers (`string`, `vector`, `array`, `pair`, `tuple`) | ✅ Implemented | Provide fundamental container semantics with simplified memory management. |
| Utility types (`optional`, `initializer_list`, `common_type`, `ratio`) | ✅ Implemented | Lightweight counterparts for common STL utility headers. |
| Algorithms & functional utilities | ✅ Implemented | Includes a subset of `<algorithm>` and callable helpers used by the containers. |
| Concurrency primitives (`thread`, `mutex`, `unique_lock`, `chrono`) | ✅ Prototype | POSIX `pthread`-based threading with basic synchronisation primitives. |
| Smart/resource pointers (`unique_ptr`) | ✅ Prototype | Minimal unique-ownership pointer for experimentation. |
| Extensive tests & CI automation | ❌ Not yet | Manual feature toggles in `main.cpp` are currently used for validation. |
| Expanded STL coverage (iterators, allocators, exceptions) | ❌ Not yet | Roadmap items for future exploration. |

## Repository Layout

```
.
├── main.cpp            # Feature toggles that exercise each remake
├── remakes/            # Header-only STL reimplementations
└── crt_remakes/        # CRT compatibility shims shared across remakes
```

## Building & Running

```bash
g++ -std=c++20 -pthread main.cpp -o stl_remakes_demo
./stl_remakes_demo
```

By default, only the threading demo runs. To experiment with other components,
flip any of the `*_TEST` macros at the top of `main.cpp` from `0` to `1`.

## Contributing

1. Fork the repository and create a feature branch.
2. Add or adjust headers alongside the lightweight CRT helper functions.
3. Update `main.cpp` with a focused demo so others can see the change in action.
4. Submit a pull request describing what was added or improved.

Bug fixes, new remade headers, and documentation improvements are all welcome!
