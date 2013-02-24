project(codeexecutor)

Set(ASMJIT_SOURCES
  AsmJit/AssemblerX86X64.cpp
  AsmJit/CodeGenerator.cpp
  AsmJit/Compiler.cpp
  AsmJit/CompilerX86X64.cpp
  AsmJit/CpuInfo.cpp
  AsmJit/Defs.cpp
  AsmJit/DefsX86X64.cpp
  AsmJit/Logger.cpp
  AsmJit/MemoryManager.cpp
  AsmJit/MemoryMarker.cpp
  AsmJit/OperandX86X64.cpp
  AsmJit/Platform.cpp
  AsmJit/Util.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(codeexecutor ${ASMJIT_SOURCES} codeblock.cpp
                            Executor.cpp executor-stack_variables.cpp
                            ExecutableCommand.cpp commands.cpp
                            ExecutionPlatform.cpp  JitCompiler.cpp
                            JitPlatform.cpp CodeGeneratorBackend.cpp 
                            InstructionEmitter.cpp ByteData.cpp main.cpp)

