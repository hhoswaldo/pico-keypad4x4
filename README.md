# Keypad 4x4 
C library for Raspberry Pico 4x4 matrix keypad

Add the following to the CMakeLists File
```
# Add third party libraries
add_library(keypad_4x4 STATIC <PATH to keypad_4x4.c>)

# Link required libraries to keypad_4x4
target_link_libraries(keypad_4x4
    pico_stdlib
    hardware_timer
    )

# Link required libraries to main
target_link_libraries(main
    keypad_4x4
)
```
