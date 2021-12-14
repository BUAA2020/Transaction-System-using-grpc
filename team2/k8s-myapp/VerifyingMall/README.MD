# 验证appx

### 说明
1. [K8S Job](https://kubernetes.io/docs/concepts/workloads/controllers/job/)  任务
2. 验证 appx-service 功能正常

### 容器镜像构建与推送
1. `VerifyingAppX` 目录下构建镜像 `docker build -t yinli2020-docker.pkg.coding.net/beijing-backend/k8s-example/verifying-appx:1.0.0 .`
2. 推送镜像 `docker push yinli2020-docker.pkg.coding.net/beijing-backend/k8s-example/verifying-appx:1.0.0`

### 在K8S中执行Job
1. 执行Job任务 `kubectl apply -f k8s/verifying-appx.yaml`，预期执行结果如下
```
job.batch/verifying-appx-job created
```
2. 查看Job执行状态 `kubectl get job/verifying-appx-job --namespace=example`，预期执行结果如下，COMPLETIONS信息为"1/1"，则说明执行成功
```
NAME                 COMPLETIONS   DURATION   AGE
verifying-appx-job   1/1           2s         34s
```
3. 查看Job执行日志 `kubectl logs job/verifying-appx-job --namespace=example`出现`response success!`则说明请求成功
