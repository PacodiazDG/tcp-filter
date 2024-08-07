 ## BUILD
```
sudo apt-get install libssl-dev
sudo apt-get install libpcap-dev
sudo apt install libnetfilter-queue-dev
mkdir build
cd build
cmake ..
make
```

 ## Example Config iptables
 ```
sudo iptables -I INPUT  -p tcp  --dport 8000  -j NFQUEUE --queue-num 0
```