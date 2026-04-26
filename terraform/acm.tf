resource "aws_acm_certificate" "cert" {
  domain_name       = "api.oisinkelly.dev"
  validation_method = "DNS"

  lifecycle {
    create_before_destroy = true
  }
}

output "acm_validation_cname_name" {
  value       = one(aws_acm_certificate.cert.domain_validation_options).resource_record_name
  description = "CNAME record name"
}

output "acm_validation_cname_value" {
  value       = one(aws_acm_certificate.cert.domain_validation_options).resource_record_value
  description = "CNAME record value"
}