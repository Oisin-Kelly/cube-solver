variable "image_tag" {
  description = "Docker image tag to deploy (git SHA from CI)"
  type        = string
  default     = "latest"
}
