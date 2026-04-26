resource "aws_ecr_repository" "solver" {
  name = "cube-solver"
}

resource "aws_ecr_lifecycle_policy" "solver" {
  repository = aws_ecr_repository.solver.name

  policy = jsonencode({
    rules = [{
      rulePriority = 1
      description  = "Keep only the 5 most recent images"
      selection = {
        tagStatus   = "any"
        countType   = "imageCountMoreThan"
        countNumber = 5
      }
      action = { type = "expire" }
    }]
  })
}
