terraform {
  backend "s3" {
    bucket         = "cube-solver-tfstate"
    key            = "cube-solver/terraform.tfstate"
    region         = "eu-west-1"
    dynamodb_table = "cube-solver-tfstate-lock"
    encrypt        = true
  }
}
