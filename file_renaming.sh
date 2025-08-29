#!/bin/bash

# Script to rename mediapipe to mediapipe_custom for namespace isolation

set -e  # Exit on any error

echo "=== MediaPipe to MediaPipe Custom Renaming Script ==="

if [ -d "mediapipe" ]; then
    echo "Renaming mediapipe directory to mediapipe_custom..."
    mv mediapipe mediapipe_custom
else
    echo "Warning: mediapipe directory not found!"
fi

echo "Updating Python import statements..."
find . -name "*.py" -type f -exec sed -i.bak \
    -e 's/^from mediapipe\b/from mediapipe_custom/g' \
    -e 's/^import mediapipe\b/import mediapipe_custom/g' \
    -e 's/\bfrom mediapipe\./from mediapipe_custom./g' \
    -e 's/\bimport mediapipe\./import mediapipe_custom./g' \
    -e 's/\bmediapipe\./mediapipe_custom./g' \
    {} \;

echo "Updating Bazel BUILD files..."
find . \( -name "BUILD" -o -name "BUILD.bazel" \) -type f -exec sed -i.bak \
    -e 's|//mediapipe|//mediapipe_custom|g' \
    -e 's|"mediapipe/|"mediapipe_custom/|g' \
    {} \;

if [ -f "WORKSPACE" ]; then
    echo "Updating WORKSPACE file..."
    sed -i.bak 's|mediapipe|mediapipe_custom|g' WORKSPACE
fi

echo "Updating .bzl files..."
find . -name "*.bzl" -type f -exec sed -i.bak \
    -e 's|//mediapipe|//mediapipe_custom|g' \
    -e 's|"mediapipe/|"mediapipe_custom/|g' \
    {} \;

echo "Updating C++ header includes..."
find . \( -name "*.cc" -o -name "*.h" -o -name "*.hpp" \) -type f -exec sed -i.bak \
    -e 's|#include "mediapipe/|#include "mediapipe_custom/|g' \
    -e 's|#include <mediapipe/|#include <mediapipe_custom/|g' \
    {} \;

echo "Updating .proto files..."
find . -name "*.proto" -type f -exec sed -i.bak \
    -e 's|import "mediapipe/|import "mediapipe_custom/|g' \
    -e 's|package mediapipe\.|package mediapipe_custom.|g' \
    {} \;

# update any configuration or text files that might reference paths
echo "Updating configuration files..."
find . \( -name "*.txt" -o -name "*.cfg" -o -name "*.conf" -o -name "*.json" \) -type f -exec sed -i.bak \
    -e 's|mediapipe/|mediapipe_custom/|g' \
    {} \;

# clean up backup files
echo "Cleaning up backup files..."
find . -name "*.bak" -type f -delete

# special handling for any hardcoded namespace references in C++
echo "Updating C++ namespace references..."
find . \( -name "*.cc" -o -name "*.h" -o -name "*.hpp" \) -type f -exec sed -i \
    -e 's|namespace mediapipe|namespace mediapipe_custom|g' \
    -e 's|mediapipe::|mediapipe_custom::|g' \
    {} \;