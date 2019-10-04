#!/bin/bash
hss_pid=$(pidof oai_hss)
mme_pid=$(pidof mme)
spgw_pid=$(pidof spgw)

#sudo tcpdump -v  -i enp3s0  -c 1 dst port 2152

./cpu_ticks $hss_pid hss_cpu_ticks.txt &
./cpu_ticks $mme_pid mme_cpu_ticks.txt &
./cpu_ticks $spgw_pid spgw_cpu_ticks.txt &
