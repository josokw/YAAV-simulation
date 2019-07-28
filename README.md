# YAAV simulator

Yet Another Autonomous Vehicle simulator. Started the development in 2009 (lecacy code C++03), but is still under construction!
Not based on any external 3D game engine. All physics (translations, rotations and collision detection) in XY-plane for Z == 0.

Challenge: refactor legacy code to Modern C++ and use [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

## Compiling and running application

QtCreator **YAAVsimulator.pro** file is available. Select this file and press run for **app** or **tests**

If **qmake** is available without QtCreator:

    qmake
    make -j5

The excutables can be found in the **build** directory.

## Dependencies

Used versions:
- Qt Creator v4.9.2
- Qt 5.12.4
- C++17 compliant compiler
- Boost C++ libs v1.65.1
- Unit test C++ framework Catch v2.9.1 [Catch2 assertions](https://github.com/catchorg/Catch2/blob/master/docs/assertions.md)
