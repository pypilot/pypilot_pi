#!/usr/bin/env bash

# Git add template files
git add .circleci ci cmake build-deps buildosx mingw msvc
git add .gitignore .clang-format .editorconfig .cmake-format.yaml .travis.yml appveyor.yml

git status
