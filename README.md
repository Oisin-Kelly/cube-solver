# Cube Solver

A Rubik's cube solver using the beginner's method.

- CLI
- HTTP server

## Prerequisites

- CMake 3.10+
- [vcpkg](https://github.com/microsoft/vcpkg)

## Build

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build -- -j$(nproc)
```

## CLI

```bash
./build/CubeSolver -f example_cube.txt
./build/CubeSolver -f example_cube.txt -v   # verbose output
```

## HTTP Server

```bash
./build/CubeSolverServer
# Listening on http://0.0.0.0:8080
```

### POST /solve

Example request:

```bash
curl -X POST http://localhost:8080/solve \
  -H "Content-Type: application/json" \
  -d '{"state":"GWYRWBRWRWOWRGWBBYGROGRGRGWBRYYBOGYGRGBBOYYYOWWBOYOOBO"}'
```

Example response:

```json
{
  "solution": ["R", "U", "R'", "U'"],
  "moveCount": 4,
  "computeTimeUs": 87000
}
```

## Cube input format

Provide 54 characters - 6 faces of 9 stickers each, in this order:

```
UP (9) → FRONT (9) → RIGHT (9) → BACK (9) → LEFT (9) → DOWN (9)
```

Read each face left-to-right, top-to-bottom. Use any single character per colour. The middle sticker of each face determines the color-face mapping automatically, so any orientation works.

When reading the UP face, ensure FRONT is facing south and BACK is facing north.
When reading the DOWN face, ensure FRONT is now facing north and BACK is facing south.

See [example_cube.txt](example_cube.txt):

```
G W Y
R B B
R W R
W O W
R O W
B B Y
G R O
G W G
R G W
B R Y
Y R O
G Y G
R G B
B Y Y
Y Y O
W W B
O G O
O B O
```

## Tests

```bash
ctest --test-dir build --output-on-failure
```

## Deploy

Infrastructure is managed with Terraform (ECS Fargate + ALB, eu-west-1).

```bash
# Bootstrap state backend (once)
aws s3api create-bucket --bucket cube-solver-tfstate --region eu-west-1 --create-bucket-configuration LocationConstraint=eu-west-1
aws s3api put-bucket-versioning --bucket cube-solver-tfstate --versioning-configuration Status=Enabled
aws dynamodb create-table --table-name cube-solver-tfstate-lock --attribute-definitions AttributeName=LockID,AttributeType=S --key-schema AttributeName=LockID,KeyType=HASH --billing-mode PAY_PER_REQUEST --region eu-west-1

cd terraform
terraform init
terraform apply
```

CI/CD deploys automatically on every push to `main` after tests pass, using GitHub Actions with OIDC auth. Set `AWS_ROLE_ARN` as a secret.
