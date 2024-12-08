cmake_minimum_required(VERSION 3.28)
project(SyncThru)

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set cmake standards
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add executables
add_executable(SyncThru ./src/server/main.c)
