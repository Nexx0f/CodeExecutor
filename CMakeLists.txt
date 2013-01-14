project(codeexecutor)

add_executable(codeexecutor codeblock.cpp Executor.cpp executor-stack_variables.cpp
               ExecutableCommand.cpp commands.cpp ExecutionPlatform.cpp main.cpp)

