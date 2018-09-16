### Kubectl Cheatsheet

https://kubernetes.io/docs/reference/kubectl/cheatsheet/

## App Dev

Run app:
node server.js

Test app:
curl localhost:8080
> Hello CloudStack!  wlp4s0 :: 192.168.1.110 tun0 :: 172.31.100.2

Dockerize and push:
docker build -t bhaisaab/hello-k8s:v1 .
docker push bhaisaab/hello-k8s:v1 (URL: https://hub.docker.com/r/bhaisaab/hello-k8s/)

Test docker container:
docker run -it -p 8080:8080  bhaisaab/hello-k8s:v1
curl localhost:8080
> Hello CloudStack!  eth0 :: 172.17.0.2

## Infra and Ops

Deploy k8s cluster, check access:

kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true get pods --all-namespaces

    NAMESPACE     NAME                                                  READY     STATUS    RESTARTS   AGE
    kube-system   coredns-78fcdf6894-2m2l8                              1/1       Running   0          27m
    kube-system   coredns-78fcdf6894-4qv5x                              1/1       Running   0          27m
    kube-system   etcd-kubekluster-demo-k8s-master                      1/1       Running   0          27m
    kube-system   kube-apiserver-kubekluster-demo-k8s-master            1/1       Running   0          27m
    kube-system   kube-controller-manager-kubekluster-demo-k8s-master   1/1       Running   0          27m
    kube-system   kube-flannel-ds-8jfb9                                 1/1       Running   0          27m
    kube-system   kube-flannel-ds-sdspv                                 1/1       Running   0          27m
    kube-system   kube-flannel-ds-wzt79                                 1/1       Running   0          27m
    kube-system   kube-proxy-2lxhv                                      1/1       Running   0          27m
    kube-system   kube-proxy-9jq48                                      1/1       Running   0          27m
    kube-system   kube-proxy-sqhxj                                      1/1       Running   0          27m
    kube-system   kube-scheduler-kubekluster-demo-k8s-master            1/1       Running   0          27m
    kube-system   kubernetes-dashboard-767dc7d4d-n4p88                  1/1       Running   0          27m

Create deployment:
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true run hello-k8s --image=bhaisaab/hello-k8s:v1 --port=8080
> deployment.apps/hello-k8s created

View deployment:
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true get deployments

    NAME          DESIRED   CURRENT   UP-TO-DATE   AVAILABLE   AGE
    hello-k8s     1         1         1            0           28s

View pod:
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true get pods
NAME                        READY     STATUS              RESTARTS   AGE
hello-k8s-59666d997-glt55   0/1       ContainerCreating   0          28s

View cluster events:
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true get events

View config:
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true config view

Pod is only inter-cluster, create service to expose that to public IP (like ACS lb port:IP):
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true expose deployment hello-k8s --port=8080 --target-port=8080 --type=LoadBalancer
> service/hello-k8s exposed

Find node-port for the service by:
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true get services
NAME         TYPE           CLUSTER-IP    EXTERNAL-IP   PORT(S)          AGE
hello-k8s    LoadBalancer   10.99.3.229   <pending>     8080:32720/TCP   1m
kubernetes   ClusterIP      10.96.0.1     <none>        443/TCP          2h

In ACS -> enable LB on port 8080 for public IP across container cluster node VMs on private port 32720. Allow firewall for port 8080.

Test prod app:
curl 10.1.36.23:8080
> Hello CloudStack!  eth0 :: 10.244.2.5

Tail logs on the fly for the pod:
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true logs -f hello-k8s-59666d997-glt55 
> logs will show up as you make curl/http requests

## Dev Iteration

Change code, git commit. Build new image and push:

docker build -t bhaisaab/hello-k8s:v2 .
docker push bhaisaab/hello-k8s:v2

## Infra/Ops Iteration

Set the new image for the pod/deployment:
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true set image deployment/hello-k8s hello-k8s=bhaisaab/hello-k8s:v2

Check status of pod, new pod will be deployed with v2, old will be terminated:
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true get pods

    NAME                         READY     STATUS        RESTARTS   AGE
    hello-k8s-59666d997-glt55    1/1       Terminating   0          2h
    hello-k8s-7ffcc7dc5d-c48kh   1/1       Running       0          1m

kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true get pods
NAME                         READY     STATUS              RESTARTS   AGE
hello-k8s-59666d997-glt55    1/1       Running             0          2h
hello-k8s-7ffcc7dc5d-c48kh   0/1       ContainerCreating   0          33s

The app v2 change will be reflected shortly:
curl 10.1.36.23:8080/testing
> Hello CloudStack World! internal info:  eth0 :: 10.244.1.5

Remove any old replicaset:
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true delete replicaset hello-k8s-59666d997
> replicaset.extensions "hello-k8s-59666d997" deleted

List replicate set:
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true get replicasets
NAME                   DESIRED   CURRENT   READY     AGE
hello-k8s-7ffcc7dc5d   1         1         1         3m

Scale up the app, have multiple replicas over nodes:
kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true scale --replicas=2 deployment/hello-k8s
> deployment.extensions/hello-k8s scaled

kubectl -s https://admin:diia799q91qoorlt5lb68pbedf@10.1.36.23:6443/ --insecure-skip-tls-verify=true get deployments
NAME        DESIRED   CURRENT   UP-TO-DATE   AVAILABLE   AGE
hello-k8s   2         2         2            1           2h


## Cleanup env

Remove the service and the deployment.
