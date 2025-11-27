# ====== Stage 1: Build ======
FROM ubuntu:22.04 AS build

# Install tools needed to compile C++/CMake projects
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy all project files
COPY . .

# Configure and build
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build --config Release

# ====== Stage 2: Runtime ======
FROM ubuntu:22.04

WORKDIR /app

# Copy only the compiled binary
COPY --from=build /app/build/bin/Batalha_de_Laponia .

CMD ["./Batalha_de_Laponia"]