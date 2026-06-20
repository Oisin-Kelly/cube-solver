variable "image_tag" {
  description = "Docker image tag to deploy (git SHA from CI)"
  type        = string
  default     = "latest"
}

locals {
  root_domain = trimspace(file("${path.module}/../CNAME"))
  cube_domain = "cube.${local.root_domain}"
}
