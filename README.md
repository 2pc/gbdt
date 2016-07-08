```
cd lib_gbdt
make all
cd output/test
./gbdt-train -r 0.8 -t 100 -s 0.03 -n 30 -d 5 -m test.model -f ../../train
./gbdt-test ./test.model ../../train
```
