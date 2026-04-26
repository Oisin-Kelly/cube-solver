resource "aws_security_group" "alb" {
  name   = "cube-alb-sg"
  vpc_id = aws_vpc.vpc.id

  ingress {
    from_port   = 80
    to_port     = 80
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  ingress {
    from_port   = 443
    to_port     = 443
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

resource "aws_lb" "app" {
  name               = "main-alb"
  load_balancer_type = "application"
  subnets            = [aws_subnet.public_a.id, aws_subnet.public_b.id]
  security_groups    = [aws_security_group.alb.id]
}

resource "aws_lb_target_group" "cube" {
  name        = "cube-tg"
  port        = 8080
  protocol    = "HTTP"
  target_type = "ip"
  vpc_id      = aws_vpc.vpc.id

  health_check {
    path    = "/health"
    matcher = "200"
  }
}

# HTTP → HTTPS redirect
resource "aws_lb_listener" "http" {
  load_balancer_arn = aws_lb.app.arn
  port              = 80
  protocol          = "HTTP"

  default_action {
    type = "redirect"
    redirect {
      port        = "443"
      protocol    = "HTTPS"
      status_code = "HTTP_301"
    }
  }
}

# HTTPS listener — default 404, routes defined per project
resource "aws_lb_listener" "https" {
  load_balancer_arn = aws_lb.app.arn
  port              = 443
  protocol          = "HTTPS"
  certificate_arn   = aws_acm_certificate.cert.arn

  default_action {
    type = "fixed-response"
    fixed_response {
      content_type = "application/json"
      message_body = "{\"error\": \"not found\"}"
      status_code  = "404"
    }
  }
}

# Route /cube/* to cube solver
resource "aws_lb_listener_rule" "cube" {
  listener_arn = aws_lb_listener.https.arn
  priority     = 100

  condition {
    path_pattern {
      values = ["/cube/*"]
    }
  }

  action {
    type             = "forward"
    target_group_arn = aws_lb_target_group.cube.arn
  }
}

output "alb_dns_name" {
  value       = aws_lb.app.dns_name
  description = "Add a CNAME record in Namecheap: api.oisinkelly.dev → this value"
}
