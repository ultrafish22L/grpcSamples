# Docker Containerized Deployment Guide

## Overview
Package octaneWebR as a Docker container for easy deployment across any platform.

---

## Prerequisites
- Docker installed ([Get Docker](https://docs.docker.com/get-docker/))
- Docker Compose (usually included with Docker Desktop)
- Octane Render running on host machine with LiveLink enabled

---

## Quick Start

### Build and Run
```bash
# Build Docker image
docker-compose build

# Start container
docker-compose up -d

# View logs
docker-compose logs -f

# Stop container
docker-compose down
```

**Access**: Open **http://localhost:43930** in browser

---

## Manual Docker Commands

### Build Image
```bash
docker build -t octanewebr:latest .
```

### Run Container
```bash
docker run -d \
  --name octanewebr \
  -p 43930:43930 \
  --add-host host.docker.internal:host-gateway \
  octanewebr:latest
```

### View Logs
```bash
docker logs -f octanewebr
```

### Stop Container
```bash
docker stop octanewebr
docker rm octanewebr
```

---

## Distribution Methods

### Option 1: Docker Hub (Public/Private Registry)

**Push to Docker Hub:**
```bash
# Login
docker login

# Tag image
docker tag octanewebr:latest yourusername/octanewebr:latest
docker tag octanewebr:latest yourusername/octanewebr:1.0.0

# Push
docker push yourusername/octanewebr:latest
docker push yourusername/octanewebr:1.0.0
```

**Users can pull and run:**
```bash
docker pull yourusername/octanewebr:latest
docker run -d -p 43930:43930 --add-host host.docker.internal:host-gateway yourusername/octanewebr:latest
```

---

### Option 2: Save as TAR Archive (Offline Distribution)

**Create archive:**
```bash
docker save octanewebr:latest | gzip > octanewebr-docker.tar.gz
```

**Users load and run:**
```bash
# Load image
docker load < octanewebr-docker.tar.gz

# Run container
docker run -d -p 43930:43930 --add-host host.docker.internal:host-gateway octanewebr:latest
```

---

### Option 3: Private Registry (Enterprise)

**Setup private registry:**
```bash
# Run local registry
docker run -d -p 5000:5000 --name registry registry:2

# Tag and push
docker tag octanewebr:latest localhost:5000/octanewebr:latest
docker push localhost:5000/octanewebr:latest
```

**Users pull from private registry:**
```bash
docker pull your-registry.com/octanewebr:latest
docker run -d -p 43930:43930 --add-host host.docker.internal:host-gateway your-registry.com/octanewebr:latest
```

---

## Configuration

### Custom Port
Edit `docker-compose.yml`:
```yaml
ports:
  - "8080:43930"  # Map host port 8080 to container port 43930
```

Or with docker run:
```bash
docker run -d -p 8080:43930 octanewebr:latest
```

### Environment Variables
```bash
docker run -d \
  -p 43930:43930 \
  -e NODE_ENV=production \
  -e OCTANE_HOST=localhost \
  -e OCTANE_PORT=51022 \
  octanewebr:latest
```

---

## Troubleshooting

### Cannot Connect to Octane
**Problem**: Container can't reach Octane on host machine

**Solution**: Ensure `--add-host host.docker.internal:host-gateway` is set

**Verify**:
```bash
# Enter container
docker exec -it octanewebr sh

# Try to connect to host
nc -zv host.docker.internal 51022
```

### Port Already in Use
**Problem**: Port 43930 already in use

**Solution**: Change host port mapping
```bash
docker run -d -p 8080:43930 octanewebr:latest
# Access at http://localhost:8080
```

### Container Won't Start
**Problem**: Container exits immediately

**Solution**: Check logs
```bash
docker logs octanewebr
```

### Image Too Large
**Problem**: Docker image is large (~500MB+)

**Solution**: Image uses multi-stage build and alpine base (~150MB actual)
- Stage 1: Build (node:18-alpine + dependencies)
- Stage 2: Production (nginx:alpine + built files only)

---

## Production Deployment

### With Docker Compose (Recommended)
```yaml
# docker-compose.production.yml
version: '3.8'

services:
  octanewebr:
    image: yourusername/octanewebr:latest
    container_name: octanewebr-prod
    ports:
      - "80:43930"  # Use port 80 for production
    restart: always
    environment:
      - NODE_ENV=production
    extra_hosts:
      - "host.docker.internal:host-gateway"
    healthcheck:
      test: ["CMD", "wget", "-q", "--spider", "http://localhost:43930"]
      interval: 30s
      timeout: 10s
      retries: 3
```

**Deploy:**
```bash
docker-compose -f docker-compose.production.yml up -d
```

### With Kubernetes
```yaml
# octanewebr-deployment.yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: octanewebr
spec:
  replicas: 1
  selector:
    matchLabels:
      app: octanewebr
  template:
    metadata:
      labels:
        app: octanewebr
    spec:
      containers:
      - name: octanewebr
        image: yourusername/octanewebr:latest
        ports:
        - containerPort: 43930
---
apiVersion: v1
kind: Service
metadata:
  name: octanewebr-service
spec:
  selector:
    app: octanewebr
  ports:
  - protocol: TCP
    port: 80
    targetPort: 43930
  type: LoadBalancer
```

**Deploy:**
```bash
kubectl apply -f octanewebr-deployment.yaml
```

---

## Advantages of Docker Distribution

✅ **Platform Independent**: Runs anywhere Docker runs (Windows, Mac, Linux, Cloud)
✅ **Consistent Environment**: Same runtime on all systems
✅ **Easy Updates**: Pull new image and restart
✅ **Isolation**: No conflicts with host system
✅ **Scalability**: Easy to deploy multiple instances
✅ **Cloud Ready**: Deploy to AWS, Azure, GCP with one command

## Disadvantages

❌ **Requires Docker**: Users must have Docker installed
❌ **Container Overhead**: Slight performance overhead (minimal with alpine)
❌ **Network Complexity**: Container-to-host networking required for Octane
❌ **Image Size**: ~150MB download (smaller than Electron but larger than static files)

---

## File Sizes

| Method | Size | Notes |
|--------|------|-------|
| Docker Image (compressed) | ~60-80 MB | gzipped tar export |
| Docker Image (uncompressed) | ~150-200 MB | Full image on disk |
| Docker Hub Pull | ~60-80 MB | Compressed download |

---

## Best Practices

### Tagging Strategy
```bash
# Use semantic versioning
docker tag octanewebr:latest octanewebr:1.0.0
docker tag octanewebr:latest octanewebr:1.0
docker tag octanewebr:latest octanewebr:1
docker tag octanewebr:latest octanewebr:latest
```

### Security
```bash
# Scan image for vulnerabilities
docker scan octanewebr:latest

# Run with limited privileges
docker run --user 1000:1000 --read-only octanewebr:latest
```

### Monitoring
```bash
# View resource usage
docker stats octanewebr

# View container health
docker inspect octanewebr | grep -A 5 Health
```

---

## Quick Reference Card

```bash
# BUILD
docker build -t octanewebr .
docker-compose build

# RUN
docker run -d -p 43930:43930 --add-host host.docker.internal:host-gateway octanewebr
docker-compose up -d

# MANAGE
docker logs -f octanewebr              # View logs
docker exec -it octanewebr sh          # Enter container
docker restart octanewebr              # Restart
docker stop octanewebr                 # Stop
docker rm octanewebr                   # Remove

# DISTRIBUTE
docker save octanewebr | gzip > octanewebr-docker.tar.gz  # Export
docker load < octanewebr-docker.tar.gz                     # Import
docker push yourusername/octanewebr:latest                 # Publish
```

---

## Support

For issues with Docker deployment:
1. Check container logs: `docker logs octanewebr`
2. Verify Octane LiveLink is enabled
3. Test network connectivity: `docker exec -it octanewebr nc -zv host.docker.internal 51022`
4. Try on host first: `npm run dev` to ensure app works outside Docker

---

**Last Updated**: 2025-01-21  
**Docker Version Tested**: 24.0+  
**Recommended For**: Cloud deployments, multi-user environments, CI/CD pipelines
