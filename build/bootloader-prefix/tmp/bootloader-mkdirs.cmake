# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/ufi/programming/esp-idf/components/bootloader/subproject"
  "/home/ufi/programming/The-One-Ring/build/bootloader"
  "/home/ufi/programming/The-One-Ring/build/bootloader-prefix"
  "/home/ufi/programming/The-One-Ring/build/bootloader-prefix/tmp"
  "/home/ufi/programming/The-One-Ring/build/bootloader-prefix/src/bootloader-stamp"
  "/home/ufi/programming/The-One-Ring/build/bootloader-prefix/src"
  "/home/ufi/programming/The-One-Ring/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/ufi/programming/The-One-Ring/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/ufi/programming/The-One-Ring/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
