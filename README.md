# CppUtils_ContainerInterfaces

## Summary
This header-only library provides a zero-cost, compile-time abstraction layer for containers, eliminating the need to depend on concrete types.

Each operation is expressed as a static interface that resolves entirely at compile time to the appropriate container-specific implementation via template specialization. This allows generic code to operate on a wide variety of container types while keeping static type safety and zero runtime overhead.

Interfaces define a consistent and predictable user-facing API, and container-specific implementations conform to these interfaces via operation specializations. Given this structure, it is straightforward to add support for new container types and operations beyond those provided.

## Abstraction Without Cost
The abstraction layer has no observable side effects and is therefore fully eliminated under the standard C++ "as-if" rule. The resulting performance is equivalent to direct, container-specific calls. The identical generated assembly below demonstrates this equivalence (try it out on [Godbolt](https://godbolt.org/z/KcbYYvhY9)).

<img width="1920" height="1080" alt="CompilerExplorerDemo" src="https://github.com/user-attachments/assets/cb284334-b889-4d03-8c4a-61926f9211b5" />

## Example Usage
```cpp
// Where `container` is a generic container type.
const bool isContainerEmpty = CppUtils::ContainerOps::IsEmpty(container).Do();
```
