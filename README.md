# Calculator

## Dependencies
- `Boost 1.74` (Boost.Spirit, Boost.Test)

## Как я билдил
  ```
  conan install ..
  cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release
  ninja
  ```
Should work with any C++17 compatible compiler

## Run tests
```
ninja test
```
