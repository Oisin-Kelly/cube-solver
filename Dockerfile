FROM ubuntu:24.04 AS builder

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    git \
    curl \
    zip \
    unzip \
    tar \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 https://github.com/microsoft/vcpkg.git /vcpkg && \
    /vcpkg/bootstrap-vcpkg.sh -disableMetrics

WORKDIR /app

COPY vcpkg.json CMakeLists.txt ./
COPY src/ src/

RUN cmake -B build -S . \
    -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DVCPKG_TARGET_TRIPLET=x64-linux-static \
    -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --target CubeSolverServer

FROM ubuntu:24.04

COPY --from=builder /app/build/CubeSolverServer /usr/local/bin/CubeSolverServer

EXPOSE 8080

CMD ["CubeSolverServer"]
