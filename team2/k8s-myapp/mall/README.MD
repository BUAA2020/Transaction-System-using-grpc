# AppX 服务

### 服务说明
1. golang服务编译与运行
2. 容器运行
3. K8S部署

### 服务编译与运行方法
1. 进入src目录
2. 编译 `go build`
3. 运行 `./AppX`
4. [k8s/appx-deployment.yaml](./k8s/appx-deployment.yaml) , [k8s/appx-pod.yaml](./k8s/appx-pod.yaml), [k8s/appx-service.yaml](./k8s/appx-service.yaml) 仅做参考

### 容器镜像构建与推送
1. `AppX`目录下执行编译指定，并按需为镜像打上tag `docker build -t yinli2020-docker.pkg.coding.net/beijing-backend/k8s-example/appx:1.0.0 .`
2. [可选] 验证
   - 本地后台运行容器镜像 `docker run -d yinli2020-docker.pkg.coding.net/beijing-backend/k8s-example/appx:1.0.0`
   - 查看容器运行日志，确认容器正常运行 `docker logs $(docker ps | grep 'yinli2020-docker.pkg.coding.net/beijing-backend/k8s-example/appx:1.0.0' | awk '{print $1;}')`
3. 推送镜像至dockerhub
    - 需注册账号
    - `docker push gkkwang/appx:1.0.0`

### 部署至K8S并提供集群内服务
2. 执行k8s配置文件 `kubectl apply -f k8s/appx.yaml`，预期执行结果如下
```
deployment.apps/appx-deployment created
service/appx-service created
```
3. 确认服务运行正常 `kubectl get service/appx-service  --namespace=example`，执行结果预期如下，其中CLUSTER-IP与AGE会有改变
```
NAME           TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)    AGE
appx-service   ClusterIP   10.97.139.164   <none>        8080/TCP   53s
```
