output "alb_dns_name" {
  value       = aws_lb.app.dns_name
  description = "Hit this URL to reach the solver API"
}
